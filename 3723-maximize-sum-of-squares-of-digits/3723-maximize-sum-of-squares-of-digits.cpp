class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if ((long long)num * 9 < sum) return "";

        int nines = sum / 9;
        int rem = sum % 9;

        string res(nines, '9');
        if (rem > 0) res += char('0' + rem);
        res.append(num - res.size(), '0'); 

        return res;
    }
};