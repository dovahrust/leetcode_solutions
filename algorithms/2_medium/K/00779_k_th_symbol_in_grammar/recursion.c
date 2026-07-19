static int helper(const int n, const int k)
{
    if (n == 1) {
        if (k != 1) {
            fprintf(stderr, "unreachable! invalid k");
            exit(1);
        }
        return 0;
    }
    const int parent_pos = (k + 1) / 2;
    const int parent_val = helper(n - 1, parent_pos);

    return ((k & 1) == 0) ? (1 - parent_val) : (parent_val);
}

int kthGrammar(const int n, const int k)
{
    assert(n > 0 && n <= 30 && k > 0);
    return helper(n, k);
}
