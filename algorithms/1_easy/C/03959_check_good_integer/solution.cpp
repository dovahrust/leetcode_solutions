class Solution {
public:
    bool checkGoodInteger(int n) {
        int sum_square_dig = 0;
        int sum_dig = 0;

        while (n > 0) {
            const int dig = n % 10;
            n /= 10;
            sum_square_dig += dig * dig;
            sum_dig += dig;

            if (sum_square_dig - sum_dig >= 50) {
                return true;
            }
        }

        return false;
    }
};
