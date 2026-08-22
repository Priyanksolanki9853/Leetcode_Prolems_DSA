class Solution {
public:
    bool checkDivisibility(int n) {
        int temp = n;
        int digitSum = 0;
        int digitProduct = 1;
        while (temp > 0) {
            int digit = temp % 10;
            digitSum += digit;
            digitProduct *= digit;
            temp /= 10;
        }
        int totalSum = digitSum + digitProduct;
        return n % totalSum == 0;
    }
};