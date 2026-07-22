typedef struct {
    uint8_t o_cnt;
    uint8_t h_cnt;
    pthread_mutex_t mtx;
    pthread_cond_t o_cv;
    pthread_cond_t h_cv;
} H2O;

void releaseHydrogen();

void releaseOxygen();

H2O* h2oCreate()
{
    H2O* obj = (H2O*) malloc(sizeof(H2O));
    obj->o_cnt = 0;
    obj->h_cnt = 0;
    pthread_mutex_init(&obj->mtx, NULL);
    pthread_cond_init(&obj->o_cv, NULL);
    pthread_cond_init(&obj->h_cv, NULL);
    return obj;
}

void hydrogen(H2O* obj)
{
    pthread_mutex_lock(&obj->mtx);
    while (obj->h_cnt == 2) {
        pthread_cond_wait(&obj->h_cv, &obj->mtx);
    }
    releaseHydrogen();
    obj->h_cnt += 1;
    if (obj->h_cnt == 2 && obj->o_cnt == 1) {
        obj->h_cnt = 0;
        obj->o_cnt = 0;
        pthread_cond_signal(&obj->o_cv);
        pthread_cond_signal(&obj->h_cv);
    } else {
        pthread_cond_signal(&obj->h_cv);
    }
    pthread_mutex_unlock(&obj->mtx);
}

void oxygen(H2O* obj)
{
    pthread_mutex_lock(&obj->mtx);
    while (obj->o_cnt == 1) {
        pthread_cond_wait(&obj->o_cv, &obj->mtx);
    }
    releaseOxygen();
    obj->o_cnt = 1;
    if (obj->h_cnt == 2) {
        obj->h_cnt = 0;
        obj->o_cnt = 0;
        pthread_cond_signal(&obj->o_cv);
        pthread_cond_signal(&obj->h_cv);
    } else {
        pthread_cond_signal(&obj->h_cv);
    }
    pthread_mutex_unlock(&obj->mtx);
}

void h2oFree(H2O* obj)
{
    pthread_mutex_destroy(&obj->mtx);
    pthread_cond_destroy(&obj->o_cv);
    pthread_cond_destroy(&obj->h_cv);
    free(obj);
}
