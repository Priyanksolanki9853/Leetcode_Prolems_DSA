class Solution {
public:
    long long countCommas(int n) {
        long long total = 0;
        long long lo = 1000;
        int d = 4;
        while (lo <= n) {
            long long hi = min((long long)n, lo * 10 - 1);
            long long count = hi - lo + 1;
            long long commas = (d - 1) / 3;
            total += count * commas;
            lo *= 10;
            d++;
        }
        return total;
    }
};