#include "gc.h"

void find_register_roots(gc_state_t state) {
    gc_node_t node = (gc_node_t)long_table_find(state->pointers, (long) 5);
    if (node != NULL) {
        add_root(state, node);
    }
}
