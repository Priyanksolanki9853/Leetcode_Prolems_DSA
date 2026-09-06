class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freqMap;
        for(int n:nums){
            freqMap[n]++;
        }
        vector<pair<int,int>> freqVec(freqMap.begin(), freqMap.end());
        sort(freqVec.begin(),freqVec.end(),[](pair<int,int> &a, pair<int,int> &b){
            return a.second>b.second;
        });
        vector<int> results;
        for(int i=0;i<k;i++){
            results.push_back(freqVec[i].first);
        }
        return results;
    }
};