class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = 0;
        for (int num : nums) {
            if (num > max_val) max_val = num;
        }

        vector<int> cnt(max_val + 1, 0);
        for (int num : nums) {
            cnt[num]++;
        }

        vector<long long> multiples(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            for (int j = i; j <= max_val; j += i) {
                multiples[i] += cnt[j];
            }
        }

        vector<long long> exact_gcd(max_val + 1, 0);
        for (int i = max_val; i >= 1; --i) {
            long long total_pairs = multiples[i] * (multiples[i] - 1) / 2;
            for (int j = 2 * i; j <= max_val; j += i) {
                total_pairs -= exact_gcd[j];
            }
            exact_gcd[i] = total_pairs;
        }

        vector<long long> pref(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            pref[i] = pref[i - 1] + exact_gcd[i];
        }

        vector<int> ans;
        ans.reserve(queries.size());
        for (long long q : queries) {
            auto it = upper_bound(pref.begin(), pref.end(), q);
            ans.push_back(static_cast<int>(distance(pref.begin(), it)));
        }

        return ans;
    }
};