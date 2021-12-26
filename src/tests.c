#include "gc.h"
#include "long_table.h"
#include <stdio.h>

void __test1(gc_state_t state);
void test1();

int main(void) {
    test1();
}

void __test1(gc_state_t state) {
    long_table_t d1 = register_gc_data(state, long_table_new(),
                                       sizeof(struct LongTable), long_table_free,
                                       NULL);
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

    __test1(state);

    find_roots(state);
    assert(state->roots_size == 0);
    state->roots_size = 0;

    free_gc_state(state);
}
