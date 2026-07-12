static void push_num_into_vec(char* vec, int* vec_len, int num)
{
    assert(num >= 2 && num <= 1000);
    const int start_idx = *vec_len;
    while (num > 0) {
        vec[*vec_len] = (num % 10) + '0';
        *vec_len += 1;
        num /= 10;
    }
    int lo = start_idx;
    int hi = *vec_len - 1;
    while (lo < hi) {
        const int temp = vec[lo];
        vec[lo] = vec[hi];
        vec[hi] = temp;

        lo += 1;
        hi -= 1;
    }
}

char* optimalDivision(int* nums, const int len)
{
    assert(len > 0 && len <= 10 && nums != NULL);
    char* res = malloc(60 * sizeof(*res));
    assert(res != NULL);
    int res_len = 0;

    switch (len) {
        case 1:
            push_num_into_vec(res, &res_len, nums[0]);
            break;
        case 2:
            push_num_into_vec(res, &res_len, nums[0]);
            res[res_len] = '/';
            res_len += 1;
            push_num_into_vec(res, &res_len, nums[1]);
            break;
        default:
            push_num_into_vec(res, &res_len, nums[0]);
            res[res_len] = '/';
            res_len += 1;
            res[res_len] = '(';
            res_len += 1;
            push_num_into_vec(res, &res_len, nums[1]);
            for (int i = 2; i < len; i +=1) {
                res[res_len] = '/';
                res_len += 1;
                push_num_into_vec(res, &res_len, nums[i]);
            }
            res[res_len] = ')';
            res_len += 1;
    }

    res[res_len] = '\0';
    return res;
}
