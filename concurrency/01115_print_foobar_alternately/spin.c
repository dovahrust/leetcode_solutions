#include <stdatomic.h>
#include <inttypes.h>
#include <sched.h>

typedef struct {
    int n;
    atomic_int_least8_t state;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    atomic_init(&obj->state, 0);
    obj->n = n;
    return obj;
}

void foo(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        while (atomic_load_explicit(&obj->state, memory_order_acquire) != 0) {
            sched_yield();
        }
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        atomic_store_explicit(&obj->state, 1, memory_order_release);
    }
}

void bar(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        while (atomic_load_explicit(&obj->state, memory_order_acquire) != 1) {
            sched_yield();
        }
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        atomic_store_explicit(&obj->state, 0, memory_order_release);
    }
}

void fooBarFree(FooBar* obj) {
    free(obj);
}
