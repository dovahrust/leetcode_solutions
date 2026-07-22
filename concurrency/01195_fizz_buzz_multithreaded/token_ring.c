enum state {
    NUM,
    FIZZ,
    BUZZ,
    FIZZ_BUZZ,
    DONE,
};

typedef struct {
    int curr;
    int n;
    enum state state;
    pthread_mutex_t mtx;
    pthread_cond_t cv_num;
    pthread_cond_t cv_fizz;
    pthread_cond_t cv_buzz;
    pthread_cond_t cv_fizz_buzz;
} FizzBuzz;

FizzBuzz* fizzBuzzCreate(int n)
{
    FizzBuzz* obj = (FizzBuzz*) malloc(sizeof(FizzBuzz));
    obj->n = n;
    obj->curr = 1;
    obj->state = NUM;
    pthread_mutex_init(&obj->mtx, NULL);
    pthread_cond_init(&obj->cv_num, NULL);
    pthread_cond_init(&obj->cv_fizz, NULL);
    pthread_cond_init(&obj->cv_buzz, NULL);
    pthread_cond_init(&obj->cv_fizz_buzz, NULL);
    return obj;
}

static void update_obj(FizzBuzz* obj)
{
    if (obj->curr < obj-> n) {
        obj->curr += 1;
    } else {
        pthread_cond_signal(&obj->cv_fizz_buzz);
        pthread_cond_signal(&obj->cv_fizz);
        pthread_cond_signal(&obj->cv_buzz);
        pthread_cond_signal(&obj->cv_num);
        obj->state = DONE;
        return;
    }
    const int curr = obj->curr;
    const int mod_by_3 = curr % 3;
    const int mod_by_5 = curr % 5;
    if (mod_by_3 == 0 && mod_by_5 == 0) {
        obj->state = FIZZ_BUZZ;
        pthread_cond_signal(&obj->cv_fizz_buzz);
    } else if (mod_by_3 == 0) {
        obj->state = FIZZ;
        pthread_cond_signal(&obj->cv_fizz);
    } else if (mod_by_5 == 0) {
        obj->state = BUZZ;
        pthread_cond_signal(&obj->cv_buzz);
    } else {
        obj->state = NUM;
        pthread_cond_signal(&obj->cv_num);
    }
}

// Don't change the following declarations
void printNumber(int a);
void printFizz();
void printBuzz();
void printFizzBuzz();

// printFizz() outputs "fizz".
void fizz(FizzBuzz* obj)
{
    while (obj->state != DONE) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != FIZZ && obj->state != DONE) {
            pthread_cond_wait(&obj->cv_fizz, &obj->mtx);
        }
        if (obj->state != DONE) { printFizz(); }
        update_obj(obj);
        pthread_mutex_unlock(&obj->mtx);
    }
}

// printBuzz() outputs "buzz".
void buzz(FizzBuzz* obj)
{
    while (obj->state != DONE) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != BUZZ && obj->state != DONE) {
            pthread_cond_wait(&obj->cv_buzz, &obj->mtx);
        }
        if (obj->state != DONE) { printBuzz(); }
        update_obj(obj);
        pthread_mutex_unlock(&obj->mtx);
    }
}

// printFizzBuzz() outputs "fizzbuzz".
void fizzbuzz(FizzBuzz* obj)
{
    while (obj->state != DONE) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != FIZZ_BUZZ && obj->state != DONE) {
            pthread_cond_wait(&obj->cv_fizz_buzz, &obj->mtx);
        }
        if (obj->state != DONE) { printFizzBuzz(); }
        update_obj(obj);
        pthread_mutex_unlock(&obj->mtx);
    }
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.
void number(FizzBuzz* obj)
{
    while (obj->state != DONE) {
        pthread_mutex_lock(&obj->mtx);
        while (obj->state != NUM && obj->state != DONE) {
            pthread_cond_wait(&obj->cv_num, &obj->mtx);
        }
        if (obj->state != DONE) { printNumber(obj->curr); }
        update_obj(obj);
        pthread_mutex_unlock(&obj->mtx);
    }
}

void fizzBuzzFree(FizzBuzz* obj)
{
    pthread_mutex_destroy(&obj->mtx);
    pthread_cond_destroy(&obj->cv_fizz);
    pthread_cond_destroy(&obj->cv_buzz);
    pthread_cond_destroy(&obj->cv_fizz_buzz);
    pthread_cond_destroy(&obj->cv_num);
    free(obj);
}
