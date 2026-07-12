#define EXACT_GENE_LEN 8
#define MAX_BANK_LEN 10

typedef ptrdiff_t isize;

static inline int calc_diff(const char* a, const char* b)
{
    int cnt = 0;
    for (isize i = 0; i < EXACT_GENE_LEN; i += 1) {
        cnt += (a[i] == b[i] ? 0 : 1);
    }
    return cnt;
}

int minMutation(const char* start_gene, const char* target, char** bank, const int bank_len)
{
    assert(bank_len <= MAX_BANK_LEN);
    bool any = false;
    for (int i = 0; i < bank_len; i += 1) {
        if (strcmp(target, bank[i]) == 0) {
            any = true;
            break;
        }
    }
    if (!any) {
        return -1;
    }

    const char** bank_datas = malloc((size_t)bank_len * sizeof(bank_datas));
    for (int i = 0; i < bank_len; i += 1) { bank_datas[i] = bank[i]; }
    int bank_datas_len = bank_len;
    const char** q = malloc((size_t)(bank_datas_len + 1) * sizeof(q));
    q[0] = start_gene;
    isize head = 0;
    isize tail = 1;

    int level = 0;
    while (head != tail) {
        const isize q_len = tail - head;

        for (isize steps = 0; steps < q_len; steps += 1) {
            const char* curr = q[head];
            head += 1;
            if (calc_diff(curr, target) == 0) {
                return level;
            }
            int i = 0;
            while (i < bank_datas_len) {
                if (calc_diff(curr, bank_datas[i]) == 1) {
                    q[tail] = bank_datas[i];
                    tail += 1;
                    bank_datas[i] = bank_datas[bank_datas_len - 1];
                    bank_datas_len -= 1;
                } else {
                    i += 1;
                }
            }
        }

        level += 1;
    }

    return -1;
}
