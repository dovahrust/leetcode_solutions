static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int a = *(int*)a_ptr;
    const int b = *(int*)b_ptr;
    return (a < b) - (a > b);
}

int maxSatisfaction(int* satisfaction, int len)
{
    assert(len >= 1 && len <= 500);
    qsort(satisfaction, (size_t)len, sizeof(*satisfaction), cmp);

    int res = 0;
    int curr_sum = 0;

    for (int i = 0; i < len; i += 1) {
        const int s = satisfaction[i];
        assert(-1000 <= s && s <= 1000);
        curr_sum += s;
        const int new_res = res + curr_sum;

        if (new_res < res) {
            break;
        }

        res = new_res;
    }

    return res;
}
