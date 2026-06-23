class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        int max_cost = 0;
        for (int cost : costs) {
            if (cost > max_cost) {
                max_cost = cost;
            }
        }
        
        vector<int> frequency(max_cost + 1, 0);
        for (int cost : costs) {
            frequency[cost]++;
        }
        
        int count = 0;
        for (int price = 1; price <= max_cost; ++price) {
            if (frequency[price] == 0) {
                continue;
            }
            
            if (coins < price) {
                break;
            }
            
            long long total_available = frequency[price];
            long long affordable = coins / price;
            long long buy = min(total_available, affordable);
            
            count += buy;
            coins -= buy * price;
            
            if (coins < price) {
                break;
            }
        }
        
        return count;
    }
};