class Solution {
public:
    int smallestNumber(int n, int t) {
        int current = n;
        while(true){
            int product=1;
            int temp=current;
            while(temp>0){
                product*=(temp%10);
                temp/=10;
            }
            if (product % t == 0) {
                return current;
            }
            current++;
        }
    }
};