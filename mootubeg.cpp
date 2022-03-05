#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

map<int,vector<pair<int,int>>,greater<int>> rels;
vector<pair<int,int>> dsu; 
vector<int> sizes;

int find(int n) {
    if (n != dsu[n].first) 
        return dsu[n].first = find(dsu[n].first);
    return n;
}

void join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (dsu[a].second < dsu[b].second) 
            swap(a, b);
        dsu[b].first = a;
        if (dsu[a].second == dsu[b].second)
            dsu[a].second++;
        sizes[a] += sizes[b];
    }
}

int main() {
    ifstream fin("mootube.in");
    ofstream fout("mootube.out");
    int n, q;
    fin >> n >> q;
    for (int i=0; i<n-1; i++) {
        int a, b, r; fin >> a >> b >> r;
        a--; b--;
        rels[r].push_back({a, b});
    }
    for (int i=0; i<n; i++) {
        dsu.push_back({i, 0});
        sizes.push_back(1);
    }
    vector<pair<pair<int,int>,int>> qs;
    for (int i=0; i<q; i++) {
        int k, v; fin >> k >> v; v--;
        qs.push_back({{k, v}, i});
    }
    sort(qs.begin(), qs.end(), [](pair<pair<int,int>,int>& a, pair<pair<int,int>,int>& b) {
        return a.first.first > b.first.first;
    });
    vector<int> res(q);
    auto it = rels.begin();
    for (int i=0; i<q; i++) {
        int currk = qs[i].first.first;
        while (it != rels.end() && it->first >= currk) {
            for (auto pr : it->second) {
                join(pr.first, pr.second);
            }
            it++;
        }
        res[qs[i].second] = sizes[find(qs[i].first.second)]-1;
    }
    for (int r : res) fout << r << '\n';
}