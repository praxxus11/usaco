#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

vector<pii> dsu;
map<ll,vector<pii>> dists;
vector<pii> pts;

ll pow2(ll x) { return x*x; }

int find(int n) {
    if (n != dsu[n].first) 
        return dsu[n].first = find(dsu[n].first);
    return n;
}

void unite(int a, int b, int& ct) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (dsu[a].second < dsu[b].second) 
            swap(a, b);
        dsu[b].first = a;
        if (dsu[a].second == dsu[b].second)
            dsu[a].second++;
        ct--;
    }
}

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");

    int n; fin >> n;
    int groups = n;
    for (int i=0; i<n; i++) {
        int a, b; fin >> a >> b;
        pts.push_back({a, b});
        dsu.push_back({i, 0});
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n && j!=i; j++) {
            dists[pow2(pts[i].first-pts[j].first) + pow2(pts[i].second-pts[j].second)].push_back({i, j});
        }
    }
    ll result = dists.begin()->first;
    auto it = dists.begin();
    while (groups > 1) {
        result = it->first;
        for (pii pr : dists[result]) {
            unite(pr.first, pr.second, groups);
        }
        it++;
    }
    fout << result << '\n';
}