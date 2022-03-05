#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <map>
#include <fstream>

using namespace std;
typedef pair<int,int> pii;

vector<pii> dsu;
map<int,vector<pii>> adj;
set<int,greater<int>> blocks;
vector<int> sizes;
int sch[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

bool good(int n, int i, int j) {
    return (i>=0&&i<n&&j>=0&&j<n);
}

int find(int n) {
    if (n != dsu[n].first) 
        return dsu[n].first = find(dsu[n].first);
    return n;
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (dsu[a].second < dsu[b].second) 
            swap(a, b);
        dsu[b].first = a;
        if (dsu[a].second == dsu[b].second)
            dsu[a].second++;
        sizes[a] += sizes[b];
        blocks.insert(sizes[a]);
    }
}

int main() {
    ifstream fin("tractor.in");
    ofstream fout("tractor.out");
    int n; fin >> n;
    vector<vector<int>> grd(n, vector<int>(n));
    for (auto& v : grd) for (int& i : v) fin >> i;
    for (int i=0; i<n*n; i++) dsu.push_back({i, 0});
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (int s=0; s<4; s++) {
                int ii = i+sch[s][0], jj = j+sch[s][1];
                if (good(n, ii, jj)) {
                    adj[abs(grd[i][j]-grd[ii][jj])].push_back({i*n + j, ii*n + jj});
                }
            }
        }
    }
    
    for (int i=0; i<n*n; i++) {
        blocks.insert(1);
        sizes.push_back(1);
    }
    int res = adj.begin()->first;
    auto it = adj.begin();
    while (*blocks.begin() < (n*n+1)/2) {
        res = it->first;
        for (pii pr : it->second) {
            unite(pr.first, pr.second);
        }
        it++;
    }
    fout << res << '\n';
}