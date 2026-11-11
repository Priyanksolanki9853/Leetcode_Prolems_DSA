class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long shared = min(need1, need2);
        long long total = shared * min(costBoth, cost1 + cost2);

        if (need1 > need2) {
            total += (long long)(need1 - need2) * min(costBoth, cost1);
        } else if (need2 > need1) {
            total += (long long)(need2 - need1) * min(costBoth, cost2);
        }

        return total;
    }
};