static inline int gcd(int a, int b)
{
    while (b != 0) {
        const int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int gcdOfOddEvenSums(int n)
{
    assert(n <= 1000 && n >= 1);
    const int sum_n_odd_n_even = (n * 2) * (n * 2 + 1) / 2;
    const int sum_half_n_odd_half_n_even = (n * (n + 1)) / 2;
    const int sum_n_even = 2 * sum_half_n_odd_half_n_even;
    const int sum_n_odd = sum_n_odd_n_even - sum_n_even;
    return gcd(sum_n_even, sum_n_odd);
}
