#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <fstream>
#include <cmath>
#include <assert.h>

using namespace std;

int n, m;
vector<vector<char>> grid;

struct pt {
    int i, j;
    bool reg;
};

bool good(int i, int j) {
    return i>=0 && i<n && j>=0 && j<m && grid[i][j]!='#';
}

int main() {
#define f
#ifdef f
    ifstream cin("gravity.in");
    ofstream cout("gravity.out");
#endif
    cin >> n >> m;
    pt start, end;
    for (int i=0; i<n; i++) {
        grid.push_back({});
        for (int j=0; j<m; j++) {
            char c; cin >> c;
            grid[i].push_back(c);
            if (c=='C') start={i,j,1};
            if (c=='D') end={i,j,1};
        }
    }
    vector<vector<int>> dists_reg(n, vector<int>(m, 1e9));
    vector<vector<int>> dists_neg(n, vector<int>(m, 1e9));
    dists_reg[start.i][start.j] = 0;
    deque<pt> q;
    q.push_front(start);

    while (!q.empty()) {
        pt curr = q.front();
        int i=curr.i, j=curr.j;
        q.pop_front();
        if (curr.reg) {
            // can fall down, turn gravity, or go left or right
            if (good(i+1, j)) {
                if (dists_reg[i+1][j]==1e9) {
                    q.push_front({i+1,j,1});
                    dists_reg[i+1][j] = dists_reg[i][j];
                }
            }
            else if (i<n-1) {
                if (good(i,j-1) && dists_reg[i][j-1]==1e9) {
                    q.push_front({i,j-1,1});
                    dists_reg[i][j-1] = dists_reg[i][j];
                }
                if (good(i,j+1) && dists_reg[i][j+1]==1e9) {
                    q.push_front({i,j+1,1});
                    dists_reg[i][j+1] = dists_reg[i][j];
                }
                if (dists_neg[i][j]==1e9) {
                    q.push_back({i,j,0});
                    dists_neg[i][j] = 1 + dists_reg[i][j];
                }
            }
        }
        else {
            if (good(i-1, j)) {
                if (dists_neg[i-1][j]==1e9) {
                    q.push_front({i-1,j,0});
                    dists_neg[i-1][j] = dists_neg[i][j];
                }
            }
            else if (i>=1) {
                if (good(i,j-1) && dists_neg[i][j-1]==1e9) {
                    q.push_front({i,j-1,0});
                    dists_neg[i][j-1] = dists_neg[i][j];
                }
                if (good(i,j+1) && dists_neg[i][j+1]==1e9) {
                    q.push_front({i,j+1,0});
                    dists_neg[i][j+1] = dists_neg[i][j];
                }
                if (dists_reg[i][j]==1e9) {
                    q.push_back({i,j,1});
                    dists_reg[i][j] = 1 + dists_neg[i][j];
                }
            }
        }
    }
    int a=dists_reg[end.i][end.j], b=dists_neg[end.i][end.j];
    cout << ((a == 1e9 && b == 1e9) ? -1 : min(a, b));
}