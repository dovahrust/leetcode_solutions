void printNumber(int x);

struct custom_sem {
    uint8_t state;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
};

struct custom_sem custom_sem_init(const uint8_t val)
{
    struct custom_sem init;
    init.state = val;
    pthread_mutex_init(&init.mtx, NULL);
    pthread_cond_init(&init.cv, NULL);
    return init;
}

static uint8_t custom_sem_wait(struct custom_sem* sem)
{
    pthread_mutex_lock(&sem->mtx);
    while (sem->state == 0) {
        pthread_cond_wait(&sem->cv, &sem->mtx);
    }
    const uint8_t res = sem->state;
    sem->state = 0;
    pthread_mutex_unlock(&sem->mtx);
    return res;
}

static void custom_sem_post(struct custom_sem* sem, const uint8_t state)
{
    pthread_mutex_lock(&sem->mtx);
    sem->state = state;
    pthread_cond_signal(&sem->cv);
    pthread_mutex_unlock(&sem->mtx);
}

typedef struct {
    int n;
    struct custom_sem states[3];
} ZeroEvenOdd;

ZeroEvenOdd* zeroEvenOddCreate(int n)
{
    ZeroEvenOdd* obj = (ZeroEvenOdd*) malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    obj->states[0] = custom_sem_init(1);
    obj->states[1] = custom_sem_init(0);
    obj->states[2] = custom_sem_init(0);
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.

void zero(ZeroEvenOdd* obj)
{
    const int n = obj->n;
    for (int i = 0; i < n; i += 1) {
        const uint8_t child = custom_sem_wait(&obj->states[0]);
        printNumber(0);
        custom_sem_post(&obj->states[child], 1);
    }
}

void odd(ZeroEvenOdd* obj)
{
    const int n = obj->n;
    for (int i = 1; i <= n; i += 2) {
        custom_sem_wait(&obj->states[1]);
        printNumber(i);
        custom_sem_post(&obj->states[0], 2);
    }
}

void even(ZeroEvenOdd* obj)
{
    const int n = obj->n;
    for (int i = 2; i <= n; i += 2) {
        custom_sem_wait(&obj->states[2]);
        printNumber(i);
        custom_sem_post(&obj->states[0], 1);
    }
}

void zeroEvenOddFree(ZeroEvenOdd* obj)
{
    pthread_mutex_destroy(&obj->states[0].mtx);
    pthread_mutex_destroy(&obj->states[1].mtx);
    pthread_mutex_destroy(&obj->states[2].mtx);
    pthread_cond_destroy(&obj->states[0].cv);
    pthread_cond_destroy(&obj->states[1].cv);
    pthread_cond_destroy(&obj->states[2].cv);
    free(obj);
}
