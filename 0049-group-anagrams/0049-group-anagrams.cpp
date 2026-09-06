class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> mp;
        for(auto s: strs){
            string originalstring = s;
            sort(s.begin(), s.end());
            mp[s].push_back(originalstring);
        }
        vector<vector<string>> anagrams;
        for(auto[key, vectorOfStrings]:mp){
            anagrams.push_back(vectorOfStrings);
        }
        return anagrams;
    }
};