struct thread_data {
    const int* nums;
    int len;
    bool res;
};

static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

static inline int min_int(const int a, const int b)
{
    return a < b ? a : b;
}

static void* forward_thread(void* arg) {
    struct thread_data* data = (struct thread_data*)arg;
    const int* nums = data->nums;
    const int len = data->len;
    int cnt = 0;
    int max = INT_MIN;
    for (int i = 0; i < len; i += 1) {
        max = max_int(max, nums[i]);
        if (nums[i] < max) {
            cnt += 1;
            if (cnt >= 2) {
                return false;
            }
        }
    }
    data->res = true;
    return NULL;
}

static void* backward_thread(void* arg) {
    struct thread_data* data = (struct thread_data*)arg;
    const int* nums = data->nums;
    const int len = data->len;
    int cnt = 0;
    int min = INT_MAX;
    for (int i = len - 1; i >= 0; i -= 1) {
        min = min_int(min, nums[i]);
        if (nums[i] > min) {
            cnt += 1;
            if (cnt >= 2) {
                return false;
            }
        }
    }
    data->res = true;
    return NULL;
}

bool checkPossibility(const int* nums, const int len)
{
    pthread_t t1, t2;

    struct thread_data data1 = { .nums = nums, .len = len, .res = false };
    struct thread_data data2 = { .nums = nums, .len = len, .res = false };

    pthread_create(&t1, NULL, forward_thread, &data1);
    pthread_create(&t2, NULL, backward_thread, &data2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return data1.res || data2.res;
}
