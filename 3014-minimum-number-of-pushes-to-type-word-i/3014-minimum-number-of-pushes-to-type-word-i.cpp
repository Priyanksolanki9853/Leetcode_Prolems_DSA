class Solution {
public:
    int minimumPushes(string word) {
        int p=0;
        int n=word.length();
        for (int i = 0; i < n; i++){
            p += (i / 8) + 1;
        }
        return p;
    }
};