constexpr char valid_bytes[3] = {'a', 'b', 'c'};

class Solution {
    static void dfs(string& temp, const int i, int& cnt, const int target) {
        if (cnt == target) {
            return;
        }

        if (i == temp.size()) {
            cnt += 1;
            return;
        }

        for (const auto ch : valid_bytes) {
            if (i == 0 || temp[i - 1] != ch) {
                temp[i] = ch;
                dfs(temp, i + 1, cnt, target);
            }

            if (cnt == target) {
                return;
            }
        }

    }

public:
    static string getHappyString(const int n, const int k) {
        int cnt = 0;
        auto temp = string(n, ' ');
        dfs(temp, 0, cnt, k);
        if (cnt == k) {
            return temp;
        }
        return string();
    }
};
