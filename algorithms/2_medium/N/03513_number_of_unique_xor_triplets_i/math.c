int uniqueXorTriplets(const int* nums, const int n) {
    assert(n >= 1 && n <= (INT_MAX / 2));
    if (n <= 2) {
        return n;
    }
    int res = 1;
    while (n >= res) {
        res = res << 1;
    }
    return res;
}
