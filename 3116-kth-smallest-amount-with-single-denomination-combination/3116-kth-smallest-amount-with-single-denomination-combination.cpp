class Solution {
public:
    long long findKthSmallest(std::vector<int>& coins, int k) {
        // Step 1: Filter out redundant coins (multiples of smaller coins)
        std::sort(coins.begin(), coins.end());
        std::vector<int> filtered;
        for (int c : coins) {
            bool redundant = false;
            for (int f : filtered) {
                if (c % f == 0) {
                    redundant = true;
                    break;
                }
            }
            if (!redundant) {
                filtered.push_back(c);
            }
        }

        int n = filtered.size();

        // Step 2: Precompute (LCM, sign) for all non-empty subsets (PIE)
        struct Subset {
            long long lcm_val;
            int sign;
        };
        std::vector<Subset> subsets;
        subsets.reserve((1 << n) - 1);

        for (int mask = 1; mask < (1 << n); ++mask) {
            int bits = __builtin_popcount(mask);
            int sign = (bits % 2 == 1) ? 1 : -1;
            long long cur_lcm = 1;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    cur_lcm = std::lcm(cur_lcm, static_cast<long long>(filtered[i]));
                }
            }
            subsets.push_back({cur_lcm, sign});
        }

        // Helper lambda to count distinct multiples <= mid
        auto countMultiples = [&](long long mid) -> long long {
            long long total = 0;
            for (const auto& [lcm_val, sign] : subsets) {
                total += sign * (mid / lcm_val);
            }
            return total;
        };

        // Step 3: Binary search for the smallest amount where count >= k
        long long left = 1;
        long long right = 1LL * filtered[0] * k;
        long long ans = right;

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (countMultiples(mid) >= k) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return ans;
    }
};