class Solution {
public:
    int minimumSum(int num) {
        vector<int> digits;
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
        sort(digits.begin(),digits.end());
        long long num1=0;
        long long num2=0;
        for(int i=0;i<digits.size();i++){
            if(i%2==0){
                num1=num1*10+digits[i];
            }
            else{
                num2 = num2 * 10 + digits[i];
            }
        }
        return num1+num2;
}
};