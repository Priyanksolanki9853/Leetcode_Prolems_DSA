struct Node {
    int full[5];
    int cnt[5][5];  // int is plenty here — max count is n ≤ 1e5
};

class Solution {
public:
    int k, n;
    vector<Node> tree;
    vector<int> arr;

    Node makeLeaf(int v) {
        Node res;
        int vv = v % k;
        for (int i = 0; i < k; i++) {
            int j = (i * vv) % k;
            res.full[i] = j;
            for (int t = 0; t < k; t++) res.cnt[i][t] = (t == j) ? 1 : 0;
        }
        return res;
    }

    Node merge(const Node& L, const Node& R) {
        Node res;
        for (int i = 0; i < k; i++) res.full[i] = R.full[L.full[i]];
        for (int i = 0; i < k; i++) {
            int mid = L.full[i];
            for (int j = 0; j < k; j++)
                res.cnt[i][j] = L.cnt[i][j] + R.cnt[mid][j];
        }
        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) { tree[node] = makeLeaf(arr[l]); return; }
        int mid = (l + r) / 2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    void update(int node, int l, int r, int pos, int val) {
        if (l == r) { tree[node] = makeLeaf(val); return; }
        int mid = (l + r) / 2;
        if (pos <= mid) update(2*node, l, mid, pos, val);
        else update(2*node+1, mid+1, r, pos, val);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        if (qr <= mid) return query(2*node, l, mid, ql, qr);
        if (ql > mid) return query(2*node+1, mid+1, r, ql, qr);
        return merge(query(2*node, l, mid, ql, qr), query(2*node+1, mid+1, r, ql, qr));
    }

    vector<int> resultArray(vector<int>& nums, int k_, vector<vector<int>>& queries) {
        k = k_;
        n = nums.size();
        arr = nums;
        tree.resize(4 * n);
        build(1, 0, n - 1);

        vector<int> result;
        for (auto& q : queries) {
            int index = q[0], value = q[1], start = q[2], x = q[3];
            arr[index] = value;
            update(1, 0, n - 1, index, value);
            Node res = query(1, 0, n - 1, start, n - 1);
            result.push_back(res.cnt[1 % k][x]);
        }
        return result;
    }
};