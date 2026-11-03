class Solution {
public:
    int minMoves(vector<int>& nums) {
        long long sum = 0;
        int mx = INT_MIN;

        for (int x : nums) {
            sum += x;
            mx = max(mx, x);
        }

        return (int)((long long)nums.size() * mx - sum);
    }
};