#define STATES_CNT 3

typedef struct {
    // User defined data may be declared here.
    sem_t states[STATES_CNT];
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    // Initialize user defined data here.
    sem_init(&obj->states[0], 0, 1);
    for (int i = 1; i < STATES_CNT; i += 1) {
        sem_init(&obj->states[i], 0, 0);
    }
    return obj;
}

void first(Foo* obj) {
    sem_wait(&obj->states[0]);
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    sem_post(&obj->states[1]);
}

void second(Foo* obj) {
    sem_wait(&obj->states[1]);
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    sem_post(&obj->states[2]);
}

void third(Foo* obj) {
    sem_wait(&obj->states[2]);
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
    sem_post(&obj->states[0]);
}

void fooFree(Foo* obj) {
    // User defined data may be cleaned up here.
    free(obj);
}
