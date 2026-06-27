class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int current_score = 0;
        
        for (int i = 0; i < k; ++i) {
            current_score += cardPoints[i];
        }
        
        int max_score = current_score;
        
        for (int i = 0; i < k; ++i) {
            current_score -= cardPoints[k - 1 - i];
            current_score += cardPoints[n - 1 - i];
            max_score = max(max_score, current_score);
        }
        
        return max_score;
    }
};