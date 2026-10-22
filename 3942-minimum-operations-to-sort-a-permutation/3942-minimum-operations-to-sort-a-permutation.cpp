#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        int pos0 = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) {
                pos0 = i;
                break;
            }
        }

        bool is_normal = true;
        for (int i = 1; i < n; ++i) {
            if (nums[(pos0 + i) % n] != i) {
                is_normal = false;
                break;
            }
        }

        bool is_reversed = true;
        for (int i = 1; i < n; ++i) {
            if (nums[(pos0 + i) % n] != n - i) {
                is_reversed = false;
                break;
            }
        }

        if (!is_normal && !is_reversed) return -1;

        vector<vector<int>> dist(2, vector<int>(n, -1));
        queue<pair<int, int>> q;
        
        dist[0][0] = 0;
        q.push({0, 0});

        while (!q.empty()) {
            auto [type, pos] = q.front();
            q.pop();

            int p1 = (pos + 1) % n;
            if (dist[type][p1] == -1) {
                dist[type][p1] = dist[type][pos] + 1;
                q.push({type, p1});
            }

            int p2 = (n - 1 - pos) % n;
            if (dist[1 - type][p2] == -1) {
                dist[1 - type][p2] = dist[type][pos] + 1;
                q.push({1 - type, p2});
            }
        }

        int ans = 1e9;
        if (is_normal && dist[0][pos0] != -1) {
            ans = min(ans, dist[0][pos0]);
        }
        if (is_reversed && dist[1][pos0] != -1) {
            ans = min(ans, dist[1][pos0]);
        }

        return ans == 1e9 ? -1 : ans;
    }
};