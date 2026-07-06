typedef ptrdiff_t isize;

class Solution {
public:
    static string breakPalindrome(string palindrome) {
        const isize len = std::ssize(palindrome);
        assert(len > 0);
        // If len is 1, there is no way to break the palindrome.
        if (len == 1) { return string(); }

        // If the length is odd, we must ignore the middle character.
        // Changing the middle character would still result in a palindrome.
        const isize half = len / 2;

        for (isize i = 0; i < half; i += 1) {
            if (palindrome[i] != 'a') {
                palindrome[i] = 'a';
                return palindrome;
            }
        }

        // If we reach here, the string consists only of 'a's.
        palindrome[len - 1] = 'b';
        return palindrome;
    }
};
