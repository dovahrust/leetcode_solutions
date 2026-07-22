typedef struct {
    uint8_t state;
    pthread_mutex_t mtx;
    pthread_cond_t cv;
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate()
{
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    obj->state = 0;
    pthread_mutex_init(&obj->mtx, NULL);
    pthread_cond_init(&obj->cv, NULL);
    return obj;
}

void hydrogen(H2O* obj)
{
    pthread_mutex_lock(&obj->mtx);
    while (obj->state == 0) {
        pthread_cond_wait(&obj->cv, &obj->mtx);
    }
    releaseHydrogen();
    obj->state = (obj->state + 1) % 3;
    pthread_mutex_unlock(&obj->mtx);
    pthread_cond_broadcast(&obj->cv);
}

void oxygen(H2O* obj)
{
    pthread_mutex_lock(&obj->mtx);
    while (obj->state != 0) {
        pthread_cond_wait(&obj->cv, &obj->mtx);
    }
    releaseOxygen();
    obj->state = 1;
    pthread_mutex_unlock(&obj->mtx);
    pthread_cond_broadcast(&obj->cv);
}

void h2oFree(H2O* obj)
{
    pthread_mutex_destroy(&obj->mtx);
    pthread_cond_destroy(&obj->cv);
    free(obj);
}
