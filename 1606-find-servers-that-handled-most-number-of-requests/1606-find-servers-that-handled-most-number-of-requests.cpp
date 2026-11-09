class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> freeServers;
        for (int i = 0; i < k; i++) freeServers.insert(i);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> busy;
        vector<int> count(k, 0);

        for (int i = 0; i < (int)arrival.size(); i++) {
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                freeServers.insert(busy.top().second);
                busy.pop();
            }

            if (freeServers.empty()) continue;

            auto it = freeServers.lower_bound(i % k);
            if (it == freeServers.end()) it = freeServers.begin();

            int server = *it;
            freeServers.erase(it);
            count[server]++;
            busy.push({arrival[i] + load[i], server});
        }

        int mx = *max_element(count.begin(), count.end());
        vector<int> ans;
        for (int i = 0; i < k; i++) {
            if (count[i] == mx) ans.push_back(i);
        }
        return ans;
    }
};