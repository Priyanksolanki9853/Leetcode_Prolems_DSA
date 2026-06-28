class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> counts;
        for (int num : nums) {
            counts[num]++;
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
        
        for (auto& pair : counts) {
            min_heap.push({pair.second, pair.first});
            if (min_heap.size() > k) {
                min_heap.pop();
            }
        }
        
        vector<int> result;
        while (!min_heap.empty()) {
            result.push_back(min_heap.top().second);
            min_heap.pop();
        }
        
        return result;
    }
};