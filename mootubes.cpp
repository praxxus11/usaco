#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int dfs(vector<vector<int>>& adj, vector<bool>& vis, vector<vector<int>>& rel, int n, int k) {
    vis[n] = 1;
    int res = 1;
    for (int node : adj[n]) {
        if (!vis[node] && rel[node][n] >= k) {
            res += dfs(adj, vis, rel, node, k);
        }
    }
    return res;
}

int main() {
    ifstream fin("mootube.in");
    ofstream fout("mootube.out");
    int n, q;
    fin >> n >> q;
    vector<vector<int>> adj(n), rel(n, vector<int>(n, -1));
    for (int i=0; i<n-1; i++) {
        int a, b, r; fin >> a >> b >> r; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        rel[a][b] = r;
        rel[b][a] = r;
    }
    while (q--) {
        int k, v; fin >> k >> v; v--;
        vector<bool> vis(n);
        fout << dfs(adj, vis, rel, v, k)-1 << '\n';
    }

}