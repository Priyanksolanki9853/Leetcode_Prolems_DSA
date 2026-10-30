class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back({e[1], e[2]});
        }

        const long long INF = LLONG_MAX / 4;
        // dist[node][run], run in [1, k]
        vector<vector<long long>> dist(n, vector<long long>(k + 1, INF));

        // min-heap of (distance, node, run)
        priority_queue<tuple<long long, int, int>,
                       vector<tuple<long long, int, int>>,
                       greater<>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, run] = pq.top();
            pq.pop();

            if (d > dist[u][run]) continue; // stale entry
            if (u == n - 1) return (int)d;  // first time reaching the target is optimal

            for (auto [v, w] : g[u]) {
                int nextRun = (labels[v] == labels[u]) ? run + 1 : 1;
                if (nextRun > k) continue;

                long long nd = d + w;
                if (nd < dist[v][nextRun]) {
                    dist[v][nextRun] = nd;
                    pq.push({nd, v, nextRun});
                }
            }
        }

        return -1;
    }
};