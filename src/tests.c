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

    // Currently breaks if these print statements dont happen - literally thats it.
    // Either one can happen and it works.
    // Perhaps due to placement of pointers in registers vs stack? register
    // checking code may not properly work.
// #ifdef DEBUG
    fprintf(stdout, "d1 is %p (%p)\n", &d1, d1);
// #endif
    long_table_t d2 = register_gc_data(state, long_table_new(),
                                       sizeof(struct LongTable), long_table_free,
                                       NULL);
    long_table_add(d2, 2, (void *)2);

// #ifdef DEBUG
    fprintf(stdout, "d2 is %p (%p)\n", &d2, d2);
// #endif

    find_roots(state);
#ifdef DEBUG
    print_roots(state);
#endif
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
#ifdef DEBUG
    printf("roots size: %d\n", state->roots_size);
#endif
    assert(state->roots_size == 0);
    state->roots_size = 0;

    collect_garbage(state);
#ifdef DEBUG
    print_present_pointers(state);
#endif

    free_gc_state(state);
}
