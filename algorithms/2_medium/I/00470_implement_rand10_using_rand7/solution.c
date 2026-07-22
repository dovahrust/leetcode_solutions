// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

int rand10() {
    while(true) {
        const int rows = rand7() - 1;
        const int cols = rand7() - 1;
        const int res = rows * 7 + cols;
        if (res < 40) {
            return (res / 4) + 1;
        }
    }
}
