typedef struct {
    // User defined data may be declared here.
    int8_t state;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    // Initialize user defined data here.
 
    pthread_cond_init(&obj->cv, NULL);
    pthread_mutex_init(&obj->mtx, NULL);
    obj->state = 0;
    return obj;
}

void first(Foo* obj) {
    pthread_mutex_lock(&obj->mtx);
    while (obj->state != 0) {
        pthread_cond_wait(&obj->cv, &obj->mtx);
    }
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    obj->state = 1;
    pthread_cond_broadcast(&obj->cv);
    pthread_mutex_unlock(&obj->mtx);
}

void second(Foo* obj) {
    pthread_mutex_lock(&obj->mtx);
    while (obj->state != 1) {
        pthread_cond_wait(&obj->cv, &obj->mtx);
    }
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    obj->state = 2;
    pthread_cond_broadcast(&obj->cv);
    pthread_mutex_unlock(&obj->mtx);
}

void third(Foo* obj) {
    pthread_mutex_lock(&obj->mtx);
    while (obj->state != 2) {
        pthread_cond_wait(&obj->cv, &obj->mtx);
    }
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
    obj->state = 0;
    pthread_cond_broadcast(&obj->cv);
    pthread_mutex_unlock(&obj->mtx);
}

void fooFree(Foo* obj) {
    // User defined data may be cleaned up here.
    pthread_cond_destroy(&obj->cv);
    pthread_mutex_destroy(&obj->mtx);
    free(obj);
}
