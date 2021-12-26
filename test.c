#include <stdlib.h>
#include <stdio.h>

register void **stack asm("rsp");
void **stack_top;

void test() {
    int a = 1;
    char *s = "abcdefg";
    unsigned long x = 0x152;
    char c = 5;
    int *pa = &a;
    (void)c; (void)x; (void)s;
    printf("Pa has val %p\n", pa);
    
    for (void **cp = stack; cp < stack_top; cp++) {
        fprintf(stderr, "Searching %p (%p) - ", cp, *cp);
        fprintf(stderr, "is %s8 byte aligned\n",
                (unsigned long)cp % 8 == 0 ? "" : "not ");
        printf("%p has value %p\n", cp, *cp);
    }
}

int main(void) {
    stack_top = stack;
    printf("Stack: %p, Stack top: %p\n", stack, stack_top);
    test();
}
