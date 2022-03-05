#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>

using namespace std;

void bfs1(int node, vector<int>& dists, vector<vector<int>>& adj) {
    dists[node] = 0;
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int n : adj[curr]) {
            if (dists[n] == 1e9) {
                dists[n] = 1 + dists[curr];
                q.push(n);
            }
        }
    }
}

int main() {
    ifstream fin("piggyback.in");
    ofstream fout("piggyback.out");
    int b, e, p, n, m;
    fin >> b >> e >> p >> n >> m;
    vector<vector<int>> adj(n);
    for (int i=0; i<m; i++) {
        int a, b;
        fin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dists(n, 1e9);
    vector<int> distsb(n, 1e9);
    vector<int> distse(n, 1e9);
    bfs1(n-1, dists, adj);
    bfs1(0, distsb, adj);
    bfs1(1, distse, adj);
    int res = 1e9;
    for (int i=0; i<n; i++) {
        res = min(res, b*distsb[i] + e*distse[i] + p*dists[i]);
    }
    fout << res;
}