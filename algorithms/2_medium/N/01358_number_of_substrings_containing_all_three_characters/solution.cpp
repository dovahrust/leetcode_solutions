class Solution {
public:
    int numberOfSubstrings(const string& s) {
        assert(std::ssize(s) <= numeric_limits<int>::max());
        const int len = std::ssize(s);
        int last_seen[3] = { -1, -1, -1};
        int cnt = 0;

        for (int i = 0; i < len; i += 1) {
            const char ch = s[i];
            assert(ch >= 'a' && ch <= 'c');
            last_seen[ch - 'a'] = i;
            cnt += 1 + *min_element(last_seen, last_seen + 3);
        }

        return cnt;
    }
};
