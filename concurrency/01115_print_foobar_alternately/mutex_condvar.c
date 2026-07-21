typedef struct {
    int n;
    int8_t state;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
} FooBar;

// Function declarations. Do not change or remove this line
void printFoo();
void printBar();

FooBar* fooBarCreate(int n) {
    FooBar* obj = (FooBar*) malloc(sizeof(FooBar));
    pthread_mutex_init(&obj->mtx, NULL);
    pthread_cond_init(&obj->cv, NULL);
    obj->state = 0;
    obj->n = n;
    return obj;
}

void foo(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != 0) {
            pthread_cond_wait(&obj->cv, &obj->mtx);
        }
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        obj->state = 1;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->mtx);
    }
}

void bar(FooBar* obj) {
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != 1) {
            pthread_cond_wait(&obj->cv, &obj->mtx);
        }
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        obj->state = 0;
        pthread_cond_broadcast(&obj->cv);
        pthread_mutex_unlock(&obj->mtx);
    }
}

void fooBarFree(FooBar* obj) {
    pthread_mutex_destroy(&obj->mtx);
    pthread_cond_destroy(&obj->cv);
    free(obj);
}
