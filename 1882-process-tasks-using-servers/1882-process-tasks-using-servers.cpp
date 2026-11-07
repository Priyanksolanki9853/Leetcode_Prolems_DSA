class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size(), m = tasks.size();

        using Free = pair<int, int>;
        using Busy = tuple<long long, int, int>;

        priority_queue<Free, vector<Free>, greater<>> freeServers;
        priority_queue<Busy, vector<Busy>, greater<>> busyServers;

        for (int i = 0; i < n; i++) freeServers.push({servers[i], i});

        vector<int> ans(m);
        long long t = 0;

        for (int j = 0; j < m; j++) {
            t = max(t, (long long)j);

            while (!busyServers.empty() && get<0>(busyServers.top()) <= t) {
                auto [fin, w, idx] = busyServers.top();
                busyServers.pop();
                freeServers.push({w, idx});
            }

            if (freeServers.empty()) {
                t = get<0>(busyServers.top());
                while (!busyServers.empty() && get<0>(busyServers.top()) <= t) {
                    auto [fin, w, idx] = busyServers.top();
                    busyServers.pop();
                    freeServers.push({w, idx});
                }
            }

            auto [w, idx] = freeServers.top();
            freeServers.pop();
            ans[j] = idx;
            busyServers.push({t + tasks[j], w, idx});
        }

        return ans;
    }
};