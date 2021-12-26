#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "long_table.h"

#define RESET_COLOUR(flag) ((flag) & ~3)
#define DEFAULT_BYTES_LIMIT 256

register void **stack asm("rsp");
void **stack_top;

enum GC_COLOURS {
    NOT_SEEN = 1,
    CHILDREN_UNSEEN = 1 << 1,
    SEEN = 1 << 2,
};

// Structure to store each garbage collected object - linked list
typedef struct GcNode {
    // Currently only uses GC_COLOURS but may want more flags later.
    int flags;
    int num_bytes;
    // Function used to mark children as not being garbage.
    void (*trace)(void *);
    // Function used to free the void *val
    // return value - number of bytes freed (for stats purposes)
    // SHOULD NOT FREE GARBAGE COLLECTED CHILDREN
    void (*free)(void *);
    void *val;
} *gc_node_t;

typedef struct GcState {
    // Linked list of nodes in existence
    long_table_t pointers;
    // Array of root values (on the stack)
    gc_node_t *roots;
    int _roots_cap;
    int roots_size;
    int bytes_allocated;
    int bytes_limit;
} *gc_state_t;

// The 'trace' function passed into register should
// recursively call the below function on all children
// that are garbage collected.
void trace(gc_state_t state, void *val) {
    gc_node_t node = (gc_node_t)long_table_find(state->pointers,
                                                (long)val);
    if (node && (node->flags & NOT_SEEN)) {
        node->flags = RESET_COLOUR(node->flags);
        node->flags |= CHILDREN_UNSEEN;

        if (node->trace)
            node->trace(node->val); 

        node->flags = RESET_COLOUR(node->flags);
        node->flags |= SEEN;
    }
}

void find_roots(gc_state_t state);

void collect_garbage(gc_state_t state) {
    if (state->bytes_allocated < state->bytes_limit)
        return;

    // Find roots
    find_roots(state);

    for (int i = 0; i < state->roots_size; i++) {
        trace(state, state->roots[i]->val);     
    }

    int freed_bytes = 0;
    long_table_t table = state->pointers;
    kvl_pair_t box;
    for (int i = 0; i < table->capacity; i++) {
        if ((box = table->boxes[i])) {
            gc_node_t n = box->val;
            if (n->flags & NOT_SEEN) {
                // Free the node and remove from linked list
                if (n->free) {
                    freed_bytes += n->num_bytes;
                    n->free(n->val);
                }
                free(n);
                long_table_remove(table, box->key);
            } else {
                // Mark as not seen for next sweep
                n->flags = RESET_COLOUR(n->flags);
                n->flags |= NOT_SEEN;
            }
        }
    }

    // Not free enough bytes -> increase threshold
    if (freed_bytes < 0.2 * state->bytes_allocated) {
        state->bytes_limit += freed_bytes * 2;
    }
    state->bytes_allocated -= freed_bytes;
    state->roots_size = 0;
}

void free_gc_state(gc_state_t state) {
    long_table_t table = state->pointers;
    for (int i = 0; i < table->capacity; i++) {
        kvl_pair_t box = table->boxes[i];
        if (box) {
            gc_node_t n = box->val;
            if (n->free)
                n->free(n->val);
            free(n);
            free(box);
        }
    }
    free(table->boxes);
    free(table);
    free(state->roots);
    free(state);
}

gc_state_t new_gc_state() {
    gc_state_t res = malloc(sizeof *res);
    stack_top = stack;
    res->bytes_allocated = 0;
    res->bytes_limit = DEFAULT_BYTES_LIMIT;
    res->pointers = long_table_new();
    res->roots = malloc(sizeof(*res->roots) * 10);
    res->roots_size = 0;
    res->_roots_cap = 10;
    return res;
}

gc_node_t new_node(void *val, int num_bytes, void (*fre)(void *), void (*trac)(void *)) {
    gc_node_t res = malloc(sizeof *res);
    res->flags = NOT_SEEN;
    res->num_bytes = num_bytes;
    res->free = fre;
    res->trace = trac;
    res->val = val;
    return res;
}

void add_root(gc_state_t state, gc_node_t node) {
    if (state->roots_size == state->_roots_cap) {
        state->_roots_cap *= 2;
        state->roots = realloc(state->roots, sizeof *state->roots * state->_roots_cap);
    }
    state->roots[state->roots_size++] = node;
}

// This is like all of the work
void find_roots(gc_state_t state) {
    {
        fprintf(stdout, "Pointers present\n");
        for (int i = 0; i < state->pointers->capacity; i++) {
            if (state->pointers->boxes[i]) {
                gc_node_t node = state->pointers->boxes[i]->val;
                fprintf(stdout, "%p\n", node->val);
            }
        }
    }
    fprintf(stdout, "Stack: %p, Top: %p\n", stack, stack_top);
    for (void **cp = stack; cp <= stack_top; cp++) {
        gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) *cp);
        if (node) {
            fprintf(stdout, "Found %p (%p)\n", cp, *cp);
            add_root(state, node);
        } else {
            fprintf(stdout, "Failed %p (%p)\n", cp, *cp);
        }
    }
}

void print_roots(gc_state_t state) {
    find_roots(state);
    printf("num roots: %d\n", state->roots_size);
    for (int i = 0; i < state->roots_size; i++) {
        printf("%p\n", state->roots[i]->val);
    }
    state->roots_size = 0;
}

void test(int c) {
    int a, b, p;
    (void)a, (void)b, (void)p;
    printf("%p\n", stack);
}

void *register_gc_data(gc_state_t state, void *data, int num_bytes,
                      void (*fre)(void *), void (*trac)(void *)) {
    gc_node_t node = new_node(data, num_bytes, fre, trac);
    long_table_add(state->pointers, (long)data, node);
    state->bytes_allocated += num_bytes;
    return data;
}

void func1(gc_state_t state) {
    long_table_t d1 = register_gc_data(state, long_table_new(),
                                       sizeof(struct LongTable), long_table_free,
                                       NULL);
    fprintf(stdout, "Stack top is %p\n", stack_top);
    long_table_add(d1, 1, (void *)1);

    fprintf(stdout, "d1 is %p (%p) - ", &d1, d1);
    fprintf(stdout, "is %s8 byte aligned\n",
            (unsigned long)&d1 % 8 == 0 ? "" : "not ");

    long_table_t d2 = register_gc_data(state, long_table_new(),
                                       sizeof(struct LongTable), long_table_free,
                                       NULL);
    long_table_add(d2, 2, (void *)2);

    fprintf(stdout, "d2 is %p (%p) - ", &d2, d2);
    fprintf(stdout, "is %s8 byte aligned\n",
            (unsigned long)&d2 % 8 == 0 ? "" : "not ");

    find_roots(state);
    assert(state->roots_size == 2);
    state->roots_size = 0;

    collect_garbage(state);
}

void test1() {
    gc_state_t state = new_gc_state();
    int test = 0;
    (void)test;
    fprintf(stdout, "Location of tests is %p\n", &test);
    fprintf(stdout, "Stack top is %p\n", stack_top);

    func1(state);

    find_roots(state);
    assert(state->roots_size == 0);
    state->roots_size = 0;

    free_gc_state(state);
}

int main(void) {
    test1();
}
