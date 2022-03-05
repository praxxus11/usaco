#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <utility>
#include <set>

using namespace std;

struct pair_hash {
    size_t operator() (const pair<int, int> &pair) const {
        return hash<int>()(pair.first) ^ hash<int>()(pair.second);
    }
};

int main() {
    ifstream fin("lasers.in");
    ofstream fout("lasers.out");

    int n;
    pair<int,int> start, end;
    fin >> n >> start.first >> start.second >> end.first >> end.second;
    unordered_map<int,set<pair<int,int>>> ys, xs;
    unordered_map<pair<int,int>,int,pair_hash> dist;
    for (int i=0; i<n; i++) {
        int x, y; fin >> x >> y;
        ys[y].insert({x, y});
        xs[x].insert({x, y});
        dist[{x,y}] = 1e9;
    }
    for (pair<int,int> p : {start, end}) {
        ys[p.second].insert(p);
        xs[p.first].insert(p);
        dist[p] = 1e9;
    }
    
    dist[start] = 0;
    queue<pair<int,int>> q;
    q.push(start);
    while (!q.empty()) {
        pair<int,int> curr = q.front();
        q.pop();
        for (pair<int,int> p : ys[curr.second]) {
            if (dist[p] == 1e9) {
                dist[p] = 1 + dist[curr];
                q.push(p);
                // ys[curr.second].erase(p);
            }
        }
        for (pair<int,int> p : xs[curr.first]) {
            if (dist[p] == 1e9) {
                dist[p] = 1 + dist[curr];
                q.push(p);
                // xs[curr.first].erase(p);
            }
        }
        // ys[curr.second].erase(curr);
        // xs[curr.first].erase(curr);
        ys[curr.second].clear();
        xs[curr.first].clear();
    }
    fout << dist[end]-1;
}