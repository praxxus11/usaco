#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <fstream>

using namespace std;

int dp[1001][1001][2];

int dist(pair<int,int>& p1, pair<int,int>& p2) {
    return pow(p1.first-p2.first, 2) + pow(p1.second-p2.second, 2);
}

int main() {
    ifstream fin("checklist.in");
    ofstream fout("checklist.out");
    int h, g;
    fin >> h >> g;
    vector<pair<int,int>> hs(h);
    vector<pair<int,int>> gs(g);
    for (pair<int,int>& pi : hs) fin >> pi.first >> pi.second;
    for (pair<int,int>& pi : gs) fin >> pi.first >> pi.second;

    for (int i=1; i<=h; i++) {
        if (i>=2) dp[i][0][0] += dp[i-1][0][0] + dist(hs[i-1], hs[i-2]);
        dp[i][0][1] = 1e9;
    }    
    for (int i=1; i<=g; i++) {
        dp[0][i][0] = dp[0][i][1] = 1e9;
    }
    // dp[i][j][0] is on i'th h and j'th g if you use h as last
    // dp[i][j][1] is on i'th h and j'th g if you use g as last
    for (int i=1; i<=h; i++) {
        for (int j=1; j<=g; j++) {
            int a=1e9, b=1e9;
            if (i>=2) a = dist(hs[i-1], hs[i-2]);
            if (j>=2) b = dist(gs[j-1], gs[j-2]);
            dp[i][j][0] = min(dp[i-1][j][0] + a, dp[i-1][j][1] + dist(hs[i-1], gs[j-1]));
            dp[i][j][1] = min(dp[i][j-1][0] + dist(hs[i-1], gs[j-1]), dp[i][j-1][1] + b);
        }
    }
    // cout << min(dp[h][g][0], dp[h][g][1]);
    fout << dp[h][g][0];
    // for (int i=0; i<=h; i++) {
    //     for (int j=0; j<=g; j++) {
    //         cout << "(" << dp[i][j][0] << ',' << dp[i][j][1] << ") ";
    //     }
    //     cout << '\n';
    // }
}