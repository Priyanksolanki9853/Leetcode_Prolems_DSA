class Solution {
public:
    int digitSum(int x) {
        int s = 0;
        while (x) {
            s += x % 10;
            x /= 10;
        }
        return s;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++) arr[i] = {digitSum(nums[i]), nums[i]};
        sort(arr.begin(), arr.end());
        unordered_map<int, int> target;
        for (int i = 0; i < n; i++) target[arr[i].second] = i;

        vector<bool> visited(n, false);
        int ans = n; 

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            ans--;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = target[nums[j]];
            }
        }

        return ans;
    }
};