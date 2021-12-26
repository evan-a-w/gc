#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "long_table.h"
#include "gc.h"

#define RESET_COLOUR(flag) ((flag) & ~3)
#define DEFAULT_BYTES_LIMIT 256
#define DEBUG

register void **stack asm("rsp");
void **stack_top;

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

void collect_garbage(gc_state_t state) {
//#ifndef DEBUG
    if (state->bytes_allocated < state->bytes_limit)
        return;
//#endif

    find_roots(state);

#ifdef DEBUG
    print_roots(state);
#endif


    for (int i = 0; i < state->roots_size; i++) {
#ifdef DEBUG
        fprintf(stderr, "Tracing root %p\n", state->roots[i]->val);
#endif
        trace(state, state->roots[i]->val);     
    }

    int freed_bytes = 0;
    long_table_t table = state->pointers;
    kvl_pair_t box;
    for (int i = 0; i < table->capacity; i++) {
        if ((box = table->boxes[i])) {
            gc_node_t n = box->val;
            if (n->flags & NOT_SEEN) {
#ifdef DEBUG
                fprintf(stderr, "Freeing %p\n", n->val);
#endif
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

void print_node(gc_node_t node) {
    fprintf(stderr, "val: %p, num_bytes: %d\n", node->val, node->num_bytes);
}

gc_node_t new_node(void *val, int num_bytes, void (*fre)(void *), void (*trac)(void *)) {
    gc_node_t res = malloc(sizeof *res);

    res->val = val;
    res->num_bytes = num_bytes;
    res->free = fre;
    res->trace = trac;

    res->flags = NOT_SEEN;
#ifdef DEBUG
    fprintf(stderr, "Allocated node: ");
    print_node(res);
#endif
    return res;
}

void add_root(gc_state_t state, gc_node_t node) {
    if (state->roots_size == state->_roots_cap) {
        state->_roots_cap *= 2;
        state->roots = realloc(state->roots, sizeof(*state->roots) * state->_roots_cap);
    }
    state->roots[state->roots_size++] = node;
}

void print_present_pointers(gc_state_t state) {
    fprintf(stdout, "Pointers present\n");
    for (int i = 0; i < state->pointers->capacity; i++) {
        if (state->pointers->boxes[i]) {
            gc_node_t node = state->pointers->boxes[i]->val;
            fprintf(stdout, "%p\n", node->val);
        }
    }
}

// This is like all of the work
void find_roots(gc_state_t state) {
    find_register_roots(state);
#ifdef DEBUG
    print_present_pointers(state);
    fprintf(stdout, "Stack: %p, Top: %p\n", stack, stack_top);
#endif
    for (void **cp = stack; cp <= stack_top; cp++) {
        gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) *cp);
        if (node) {
#ifdef DEBUG
            fprintf(stdout, "Found %p (%p)\n", cp, *cp);
            print_node(node);
#endif
            add_root(state, node);
        }
#ifdef DEBUG
        else {
            fprintf(stdout, "Failed %p (%p)\n", cp, *cp);
        }
#endif
    }
}

void print_roots(gc_state_t state) {
    printf("num roots: %d\n", state->roots_size);
    for (int i = 0; i < state->roots_size; i++) {
        printf("%p\n", state->roots[i]->val);
    }
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
    collect_garbage(state);
    return data;
}
