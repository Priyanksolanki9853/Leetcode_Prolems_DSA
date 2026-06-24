class Solution {
    const int MOD = 1e9 + 7;

    vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B, int size) {
        vector<vector<long long>> C(size, vector<long long>(size, 0));
        for (int i = 0; i < size; ++i) {
            for (int k = 0; k < size; ++k) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < size; ++j) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    vector<vector<long long>> power(vector<vector<long long>> A, long long p, int size) {
        vector<vector<long long>> res(size, vector<long long>(size, 0));
        for (int i = 0; i < size; ++i) res[i][i] = 1;
        while (p > 0) {
            if (p & 1) res = multiply(res, A, size);
            A = multiply(A, A, size);
            p >>= 1;
        }
        return res;
    }

public:
    int zigZagArrays(long long n, int l, int r) {
        int m = r - l + 1;
        int size = 2 * m;

        vector<long long> initial(size, 0);
        for (int v = 0; v < m; ++v) {
            initial[v] = m - 1 - v;
            initial[m + v] = v;
        }

        vector<vector<long long>> T(size, vector<long long>(size, 0));
        for (int v = 0; v < m; ++v) {
            for (int u = v + 1; u < m; ++u) {
                T[m + u][v] = 1;
            }
            for (int u = 0; u < v; ++u) {
                T[u][m + v] = 1;
            }
        }

        T = power(T, n - 2, size);

        long long total_valid_arrays = 0;
        for (int i = 0; i < size; ++i) {
            long long final_val = 0;
            for (int j = 0; j < size; ++j) {
                final_val = (final_val + T[i][j] * initial[j]) % MOD;
            }
            total_valid_arrays = (total_valid_arrays + final_val) % MOD;
        }

        return total_valid_arrays;
    }
};