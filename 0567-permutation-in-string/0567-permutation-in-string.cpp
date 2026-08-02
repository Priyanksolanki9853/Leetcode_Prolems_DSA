class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.length();
        int n2 = s2.length();
        if(n1>n2) return false;
        vector<int> s1count(26,0);
        vector<int> s2count(26,0);
        for(int i=0; i<n1; i++){
            s1count[s1[i]-'a']++;
            s2count[s2[i]-'a']++;
        }
        for(int i=0; i<n2-n1; i++){
            if(s1count == s2count){
                return true;
            }
            s2count[s2[i+n1]-'a']++;
            s2count[s2[i]-'a']--;
        }
        return s1count==s2count;
    }
};