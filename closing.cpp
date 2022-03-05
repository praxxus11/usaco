#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

int find(int n, vector<int>& par) {
    if (n != par[n]) return par[n] = find(par[n], par);
    return n;
}

void unite(int a, int b, vector<int>& par, vector<int>& hei, int& clumps) {
    int fa = find(a, par);
    int fb = find(b, par);
    if (fa != fb) {
        clumps--;
        if (hei[fa] < hei[fb]) 
            par[fa] = fb;
        else 
            par[fb] = fa;
        if (hei[fa] == hei[fb]) {
            hei[fa]++;
        }
    }
}

int main() {
    ifstream fin("closing.in");
    ofstream fout("closing.out");

    int n, m;
    fin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> ord;
    map<int,bool> open;
    for (int i=0; i<m; i++) {
        int a, b; fin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i=0; i<n; i++) {
        int a; fin >> a; a--;
        ord.push_back(a);
    }
    vector<int> par(n), hei(n);
    for (int i=0; i<n; i++) par[i] = i;

    vector<bool> res;
    int sz = n;
    for (int i=n-1; i>=0; i--) {
        for (int node : adj[ord[i]]) {
            if (open[node]) {
                unite(node, ord[i], par, hei, sz);
            }
        }
        int closed = i;
        res.push_back(sz - closed == 1);
        open[ord[i]] = 1;
    }
    for (int i=n-1; i>=0; i--) {
        fout << (res[i] ? "YES\n" : "NO\n");
    }
}