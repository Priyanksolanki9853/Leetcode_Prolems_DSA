class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";

        int m = num1.size(), n = num2.size();
        vector<int> pos(m + n, 0);

        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + pos[i + j + 1];

                pos[i + j + 1] = sum % 10;
                pos[i + j] += sum / 10;
            }
        }

        string result;
        for (int p : pos) {
            if (!(result.empty() && p == 0)) {
                result.push_back('0' + p);
            }
        }

        return result;
    }
};