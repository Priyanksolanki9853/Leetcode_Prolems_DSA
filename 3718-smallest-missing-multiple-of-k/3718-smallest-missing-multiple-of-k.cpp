class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> s(nums.begin(), nums.end());
        int i = 1;
        while (true) {
            int x = k * i;
            if (s.find(x) == s.end()) return x;
            i++;
        }
    }
};