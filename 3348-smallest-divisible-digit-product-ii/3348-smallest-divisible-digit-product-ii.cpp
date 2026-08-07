class Solution {
    int dp[60][60];

    void get_digit_factors(int d, int& d2, int& d3, int& d5, int& d7) {
        d2 = d3 = d5 = d7 = 0;
        if (d == 2) d2 = 1;
        else if (d == 3) d3 = 1;
        else if (d == 4) d2 = 2;
        else if (d == 5) d5 = 1;
        else if (d == 6) { d2 = 1; d3 = 1; }
        else if (d == 7) d7 = 1;
        else if (d == 8) d2 = 3;
        else if (d == 9) d3 = 2;
    }

    bool check(int r2, int r3, int r5, int r7, int k) {
        if (r2 >= 60 || r3 >= 60) return false;
        return r5 + r7 + dp[r2][r3] <= k;
    }

    string fill_remaining(int r2, int r3, int r5, int r7, int k) {
        string res = "";
        int rem_k = k;
        while (rem_k > 0) {
            for (int d = 1; d <= 9; ++d) {
                int d2, d3, d5, d7;
                get_digit_factors(d, d2, d3, d5, d7);
                int nr2 = max(0, r2 - d2);
                int nr3 = max(0, r3 - d3);
                int nr5 = max(0, r5 - d5);
                int nr7 = max(0, r7 - d7);
                
                if (check(nr2, nr3, nr5, nr7, rem_k - 1)) {
                    res += to_string(d);
                    r2 = nr2; r3 = nr3; r5 = nr5; r7 = nr7;
                    break;
                }
            }
            rem_k--;
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        long long temp = t;
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
        
        // Step 1: Factorize t
        while (temp % 2 == 0) { c2++; temp /= 2; }
        while (temp % 3 == 0) { c3++; temp /= 3; }
        while (temp % 5 == 0) { c5++; temp /= 5; }
        while (temp % 7 == 0) { c7++; temp /= 7; }

        // If t has prime factors > 7, it's impossible to achieve with digits 1-9
        if (temp > 1) return "-1";

        // Step 2: Precompute DP
        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 60; ++j) {
                dp[i][j] = 1e9;
            }
        }
        dp[0][0] = 0;
        
        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 60; ++j) {
                if (i == 0 && j == 0) continue;
                int res = 1e9;
                int pi, pj;

                // Try placing digits 2, 3, 4, 6, 8, 9
                pi = max(0, i - 1); pj = j;
                if (pi != i || pj != j) res = min(res, 1 + dp[pi][pj]);

                pi = i; pj = max(0, j - 1);
                if (pi != i || pj != j) res = min(res, 1 + dp[pi][pj]);

                pi = max(0, i - 2); pj = j;
                if (pi != i || pj != j) res = min(res, 1 + dp[pi][pj]);

                pi = max(0, i - 1); pj = max(0, j - 1);
                if (pi != i || pj != j) res = min(res, 1 + dp[pi][pj]);

                pi = max(0, i - 3); pj = j;
                if (pi != i || pj != j) res = min(res, 1 + dp[pi][pj]);

                pi = i; pj = max(0, j - 2);
                if (pi != i || pj != j) res = min(res, 1 + dp[pi][pj]);

                dp[i][j] = res;
            }
        }

        int n = num.length();
        vector<int> p2(n + 1, 0), p3(n + 1, 0), p5(n + 1, 0), p7(n + 1, 0);
        bool has_zero = false;
        int zero_idx = n;

        // Step 3: Parse 'num', stopping progression at the first '0'
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                if (!has_zero) {
                    has_zero = true;
                    zero_idx = i;
                }
                p2[i+1] = p2[i]; p3[i+1] = p3[i]; p5[i+1] = p5[i]; p7[i+1] = p7[i];
            } else {
                int d2, d3, d5, d7;
                get_digit_factors(num[i] - '0', d2, d3, d5, d7);
                p2[i+1] = p2[i] + d2;
                p3[i+1] = p3[i] + d3;
                p5[i+1] = p5[i] + d5;
                p7[i+1] = p7[i] + d7;
            }
        }

        if (!has_zero) {
            if (p2[n] >= c2 && p3[n] >= c3 && p5[n] >= c5 && p7[n] >= c7) {
                return num;
            }
        }

        // Step 4: Seek optimal divergence point
        int max_i = (zero_idx < n) ? zero_idx : n - 1;
        for (int i = max_i; i >= 0; --i) {
            int start_d = max(1, (num[i] - '0') + 1);
            for (int d = start_d; d <= 9; ++d) {
                int d2, d3, d5, d7;
                get_digit_factors(d, d2, d3, d5, d7);
                int r2 = max(0, c2 - p2[i] - d2);
                int r3 = max(0, c3 - p3[i] - d3);
                int r5 = max(0, c5 - p5[i] - d5);
                int r7 = max(0, c7 - p7[i] - d7);
                int k = n - 1 - i;

                if (check(r2, r3, r5, r7, k)) {
                    string ans = num.substr(0, i) + to_string(d) + fill_remaining(r2, r3, r5, r7, k);
                    return ans;
                }
            }
        }

        // Step 5: If no valid combination maps to `n` length, increment character length
        int req = c5 + c7 + dp[c2][c3];
        int L = max(n + 1, req);
        return fill_remaining(c2, c3, c5, c7, L);
    }
};