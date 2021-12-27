#ifndef GC_H
#define GC_H

// #define DEBUG

#include <stdlib.h>
#include "long_table.h"

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

extern void find_register_roots(gc_state_t state);

void trace(gc_state_t state, void *val);

void find_roots(gc_state_t state);

void collect_garbage(gc_state_t state);

void free_gc_state(gc_state_t state);

gc_state_t new_gc_state();

gc_node_t new_node(void *val, int num_bytes, void (*fre)(void *), void (*trac)(void *));

void add_root(gc_state_t state, gc_node_t node);

void find_roots(gc_state_t state);

void print_roots(gc_state_t state);

void print_node(gc_node_t node);

void *register_gc_data(gc_state_t state, void *data, int num_bytes,
                      void (*fre)(void *), void (*trac)(void *));

void print_present_pointers(gc_state_t state);

#endif
