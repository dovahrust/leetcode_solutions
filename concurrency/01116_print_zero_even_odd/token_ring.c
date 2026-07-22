void printNumber(int x);

typedef struct {
    int n;
    uint8_t state;
    pthread_mutex_t mtx;
    pthread_cond_t cv_zero;
    pthread_cond_t cv_odd;
    pthread_cond_t cv_even;
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n)
{
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->state = 0;
    pthread_mutex_init(&obj->mtx, NULL);
    pthread_cond_init(&obj->cv_zero, NULL);
    pthread_cond_init(&obj->cv_odd, NULL);
    pthread_cond_init(&obj->cv_even, NULL);
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.

void zero(ZeroEvenOdd* obj)
{
    const int n = obj->n;
    for (int i = 0; i < n; i += 1) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != 0 && obj->state != 2) {
            pthread_cond_wait(&obj->cv_zero, &obj->mtx);
        }
        printNumber(0);
        obj->state += 1;
        if (obj->state == 1) {
            pthread_cond_signal(&obj->cv_odd);
        } else {
            pthread_cond_signal(&obj->cv_even);
        }
        pthread_mutex_unlock(&obj->mtx);
    }
}

void odd(ZeroEvenOdd* obj)
{
    const int n = obj->n;
    for (int i = 1; i <= n; i += 2) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != 1) {
            pthread_cond_wait(&obj->cv_odd, &obj->mtx);
        }
        printNumber(i);
        obj->state += 1;
        pthread_cond_signal(&obj->cv_zero);
        pthread_mutex_unlock(&obj->mtx);
    }
}

void even(ZeroEvenOdd* obj)
{
    const int n = obj->n;
    for (int i = 2; i <= n; i += 2) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != 3) {
            pthread_cond_wait(&obj->cv_even, &obj->mtx);
        }
        printNumber(i);
        obj->state = 0;
        pthread_cond_signal(&obj->cv_zero);
        pthread_mutex_unlock(&obj->mtx);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj)
{
    pthread_mutex_destroy(&obj->mtx);
    pthread_cond_destroy(&obj->cv_zero);
    pthread_cond_destroy(&obj->cv_odd);
    pthread_cond_destroy(&obj->cv_even);
    free(obj);
}
