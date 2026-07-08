static int cmp(const void* a_ptr, const void* b_ptr)
{
    const int* a = *(int**)a_ptr;
    const int* b = *(int**)b_ptr;
    const int diff_a = a[0] - a[1];
    const int diff_b = b[0] - b[1];
    return (diff_a > diff_b) - (diff_a < diff_b);
}

int minimumEffort(int** tasks, int tasks_len, int* tasks_col_len)
{
    qsort(tasks, (size_t)tasks_len, sizeof(*tasks), cmp);

    int total_energy = 0;
    int remain = 0;

    for (int i = 0; i < tasks_len; i += 1) {
        const int actual = tasks[i][0];
        const int minimum = tasks[i][1];
        assert(actual <= minimum);
        if (minimum > remain) {
            total_energy += minimum - remain;
            remain = minimum;
        }
        remain -= actual;
    }

    return total_energy;
}
