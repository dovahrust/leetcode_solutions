static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int a = *(int*)a_ptr;
    const int b = *(int*)b_ptr;
    return (a > b) - (a < b);
}

static inline int abs_int(const int a)
{
    return a < 0 ? -a : a;
}

static inline int max_int(const int a, const int b)
{
    return a > b ? a : b;
}

static inline bool dist_to_next_heater_is_eq_or_is_less(const int house, const int* heaters,
                                                        const int heaters_len, const int heaters_idx)
{
    if (heaters_idx + 1 == heaters_len) {
        return false;
    }
    return abs_int(house - heaters[heaters_idx]) >= abs_int(house - heaters[heaters_idx + 1]);
}

int findRadius(int* houses, const int houses_len, int* heaters, const int heaters_len)
{
    assert(heaters_len > 0 && houses_len > 0 && houses != NULL && heaters != NULL);
    qsort(houses, (size_t)houses_len, sizeof(*houses), cmp);
    qsort(heaters, (size_t)heaters_len, sizeof(*heaters), cmp);

    int heaters_idx = 0;
    int res = 0;

    for (int i = 0; i < houses_len; i += 1) {
        while (dist_to_next_heater_is_eq_or_is_less(houses[i], heaters, heaters_len, heaters_idx)) {
            heaters_idx += 1;
        }
        res = max_int(res, abs_int(houses[i] - heaters[heaters_idx]));
    }

    return res;
}
