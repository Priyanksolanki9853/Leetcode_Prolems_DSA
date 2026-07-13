class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> result;
        string digits = "123456789";
        
        for (int length = 2; length <= 9; ++length) {
            for (int startIdx = 0; startIdx <= digits.length() - length; ++startIdx) {
                string sub = digits.substr(startIdx, length);
                int num = stoi(sub);
                
                if (num >= low && num <= high) {
                    result.push_back(num);
                }
            }
        }
        
        return result;
    }
};