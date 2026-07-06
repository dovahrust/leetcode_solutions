#define INF (INT16_MAX / 2)

static inline int calc_diff(const char* s1, const char* s2, const int len)
{
    int diff = 0;
    for (int i = 0; i < len; i += 1) {
        if (s1[i] != s2[i]) {
            diff += 1;
        }
    }
    return diff;
}

int ladderLength(char* begin_word, char* end_word, char** word_list, int word_list_len)
{
    const int width = (int)strlen(begin_word);
    assert(word_list_len <= 5000 && begin_word != NULL && end_word != NULL && word_list_len > 0);
    assert(calc_diff(begin_word, end_word, width) > 0);
    bool end_word_exist = false;
    for (int i = 0; i < word_list_len; i += 1) {
        if (calc_diff(word_list[i], end_word, width) == 0) {
            end_word_exist = true;
            break;
        }
    }
    if (!end_word_exist) { return 0; }

    int16_t* buff = malloc((size_t)(3 * word_list_len) * sizeof(*buff));
    assert(buff != NULL);

    int16_t* avaiables = &buff[0];
    int hi = word_list_len;
    int lo = 0;

    int16_t* costs = &buff[word_list_len];

    int16_t* q = &buff[2 * word_list_len];
    int head = 0;
    int tail = 0;

    for (int i = 0; i < word_list_len; i += 1) {
        avaiables[i] = (int16_t)i;
        costs[i] = INF;
    }

    while (lo < hi) {
        const int diff = calc_diff(begin_word, word_list[avaiables[lo]], width);
        if (diff == 1) {
            costs[avaiables[lo]] = 2;
            q[tail] = avaiables[lo];
            tail += 1;
            hi -= 1;
            avaiables[lo] = avaiables[hi];
        } else if (diff == 0) {
            costs[avaiables[lo]] = 0;
            hi -= 1;
            avaiables[lo] = avaiables[hi];
        } else {
            lo += 1;
        }
    }

    while (head < tail) {
        const int i = q[head];
        head += 1;
        const int curr_cost = costs[i];
        int lo = 0;
        while (lo < hi) {
            const int diff = calc_diff(word_list[i], word_list[avaiables[lo]], width);
            if (diff == 1) {
                costs[avaiables[lo]] = curr_cost + 1;
                q[tail] = avaiables[lo];
                tail += 1;
                hi -= 1;
                avaiables[lo] = avaiables[hi];
            } else {
                lo += 1;
            }
        }
    }

    int res = 0;
    for (int i = 0; i < word_list_len; i += 1) {
        if (calc_diff(end_word, word_list[i], width) == 0) {
            if (costs[i] == INF) {
                res = 0;
            } else {
                res = costs[i];
            }
            break;
        }
    }

/* cleanup: */
    free(buff);
    return res;
}
