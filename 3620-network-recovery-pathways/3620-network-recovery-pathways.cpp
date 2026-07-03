#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        // Derive 'n' directly from the online array size
        int n = online.size();
        
        // Step 1: Build adjacency list and in-degree array for Topological Sort
        vector<vector<pair<int, int>>> adj(n);
        vector<int> in_degree(n, 0);
        int max_cost = 0;
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            adj[u].push_back({v, cost});
            in_degree[v]++;
            max_cost = max(max_cost, cost);
        }
        
        // Step 2: Compute Global Topological Sort (Kahn's Algorithm)
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> topo_order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);
            
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                if (--in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        // Step 3: Binary Search for the maximum bottleneck score
        int low = 0, high = max_cost;
        int ans = -1;
        const long long INF = 1e18;
        
        auto check = [&](int mid_score) {
            vector<long long> dist(n, INF);
            dist[0] = 0;
            
            for (int u : topo_order) {
                if (dist[u] == INF) continue;
                if (u != 0 && u != n - 1 && !online[u]) continue;
                
                for (const auto& edge : adj[u]) {
                    int v = edge.first;
                    int cost = edge.second;
                    
                    if (cost >= mid_score) {
                        if (dist[u] + cost < dist[v]) {
                            dist[v] = dist[u] + cost;
                        }
                    }
                }
            }
            return dist[n - 1] <= k;
        };
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return ans;
    }
};