#define VALID_CHARS_LEN 3

const static int valid_chars[VALID_CHARS_LEN] = {'a', 'b', 'c'};

static void dfs(char* temp, const int i, const int n, int* cnt, const int target)
{
    if (*cnt == target) {
        return;
    }

    if (i == n) {
        *cnt += 1;
        return;
    }

    for (int idx = 0; idx < VALID_CHARS_LEN; idx += 1) {
        if (i == 0 || temp[i - 1] != valid_chars[idx]) {
            temp[i] = valid_chars[idx];
            dfs(temp, i + 1, n, cnt, target);
        }

        if (*cnt == target) {
            return;
        }
    }

}

char* getHappyString(int n, int k)
{
    assert(n >= 1 && k >= 1 && n <= 10 && k <= 100);
    int cnt = 0;
    char* temp = malloc((size_t)(n + 1) * sizeof(*temp));
    assert(temp != NULL);
    dfs(temp, 0, n, &cnt, k);
    if (cnt == k) {
        temp[n] = '\0';
        return temp;
    }
    temp[0] = '\0';
    return temp;
}
