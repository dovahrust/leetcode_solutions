class Solution:
    def checkGoodInteger(self, n: int) -> bool:
        sum_square_dig = 0
        sum_dig = 0

        while n > 0:
            dig = n % 10
            n //= 10
            sum_square_dig += dig * dig
            sum_dig += dig

            if sum_square_dig - sum_dig >= 50:
                return True

        return False
