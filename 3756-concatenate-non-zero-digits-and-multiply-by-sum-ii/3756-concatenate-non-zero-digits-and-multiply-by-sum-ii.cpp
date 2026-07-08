class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int m = s.length();
        long long MOD = 1e9 + 7;

        vector<int> cnt(m + 1, 0);
        vector<long long> p_sum(m + 1, 0);
        vector<long long> p_x(m + 1, 0);
        vector<long long> pow10(m + 1, 1);

        for (int i = 1; i <= m; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        for (int i = 0; i < m; i++) {
            int digit = s[i] - '0';
            if (digit != 0) {
                cnt[i + 1] = cnt[i] + 1;
                p_sum[i + 1] = p_sum[i] + digit;
                p_x[i + 1] = (p_x[i] * 10 + digit) % MOD;
            } else {
                cnt[i + 1] = cnt[i];
                p_sum[i + 1] = p_sum[i];
                p_x[i + 1] = p_x[i];
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            
            int digits_in_range = cnt[r + 1] - cnt[l];
            
            if (digits_in_range == 0) {
                answer.push_back(0);
                continue;
            }

            long long current_sum = p_sum[r + 1] - p_sum[l];

            long long x = p_x[r + 1] - (p_x[l] * pow10[digits_in_range]) % MOD;
            if (x < 0) x += MOD;

            long long ans = (x * current_sum) % MOD;
            answer.push_back(ans);
        }

        return answer;
    }
};