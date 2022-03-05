#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

struct cr {
    int x, y;
    int dist(const cr& c) {
        return pow(x-c.x,2) + pow(y-c.y,2);
    }
    cr incr(char c) {
        cr n = *this;
        if (c == 'N') n.y++;
        else if (c == 'S') n.y--;
        else if (c == 'W') n.x--;
        else if (c == 'E') n.x++;
        return n;
    }
};


int main() {
    ifstream fin("radio.in");
    ofstream fout("radio.out");

    int n, m; fin >> n >> m;
    cr f, b;
    fin >> f.x >> f.y;
    fin >> b.x >> b.y;
    string fp, bp;
    fin >> fp >> bp;


    cr ftemp = f, btemp = b;
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    vector<vector<pair<cr,cr>>> cors(n+1, vector<pair<cr,cr>>(m+1, {f,b}));
    for (int i=0; i<=n; i++) {
        if (i>=1) {
            cors[i][0].first = cors[i-1][0].first.incr(fp[i-1]);
            cors[i][0].second = cors[i-1][0].second;
        }
        for (int j=0; j<=m; j++) {
            if (j>=1) {
                cors[i][j].first = cors[i][j-1].first;
                cors[i][j].second = cors[i][j-1].second.incr(bp[j-1]);
            }
        }
    }
    // for (auto v : cors) {
    //     for (auto pi : v) {
    //         cout << "[(" << pi.first.x << ',' << pi.first.y << ")(" << pi.second.x << ',' << pi.second.y << ")] ";
    //     }
    //     cout << '\n';
    // }
    for (int i=1; i<=n; i++) {
        dp[i][0] += cors[i][0].first.dist(cors[i][0].second) + dp[i-1][0];
    }
    for (int j=1; j<=m; j++) {
        dp[0][j] += cors[0][j].first.dist(cors[0][j].second) + dp[0][j-1];
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            dp[i][j] += cors[i][j].first.dist(cors[i][j].second);
            dp[i][j] += min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1]));
        }
    }
    fout << dp[n][m];
    // for (int i=0; i<=n; i++) {
    //     for (int j=0; j<=m; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
}