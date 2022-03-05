#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <assert.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> cts(k);
    vector<int> cows(n);
    for (int i=0; i<n; i++) {
        int a; cin >> a; a--;
        cts[a].push_back(i);
        cows[i] = a;
    }
    vector<vector<bool>> good(n, vector<bool>(n));
    for (int i=0; i<k; i++) {
        for (int j=0; j<k; j++) {
            char c; cin >> c;
            good[i][j] = (c == '1');
        }
    }

    vector<vector<int>> adj(n);
    for (int i=0; i<n; i++) {
        int cur = cows[i];
        for (int j=0; j<k; j++) {
            if (good[cur][j]) {
                adj[i].insert(adj[i].end(), cts[j].begin(), cts[j].end());
            }
        }
    }

    for (int i=0; i<n; i++) {
        cout << 1+i << ": ";
        for (int j=0; j<adj[i].size(); j++) {
            cout << adj[i][j]+1 << ",";
        }
        cout << '\n';
    }
}