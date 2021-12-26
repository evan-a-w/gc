#include "gc.h"
#include "long_table.h"
#include <stdio.h>

void __test1(gc_state_t state);
void test1();

int main(void) {
    test1();
}

void test1__(gc_state_t state) {
    long_table_t d1 = register_gc_data(state, long_table_new(),
                                       sizeof(struct LongTable), long_table_free,
                                       NULL);
    long_table_add(d1, 1, (void *)1);

    gc_node_t node = long_table_find(state->pointers, (unsigned long)d1);
    print_node(node);

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
    printf("roots size: %d\n", state->roots_size);
    assert(state->roots_size == 2);
    state->roots_size = 0;

    collect_garbage(state);
}

// Only works in unoptimized builds - inlines the stuff otherwise i think
void test1() {
    gc_state_t state = new_gc_state();
    int test = 0;
    (void)test;

    test1__(state);

    find_roots(state);
    printf("roots size: %d\n", state->roots_size);
    assert(state->roots_size == 0);
    state->roots_size = 0;

    collect_garbage(state);
    print_present_pointers(state);

    free_gc_state(state);
}
