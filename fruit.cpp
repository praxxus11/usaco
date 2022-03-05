#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int res(int t, int a, int b) {
    vector<bool> dp(t+1, 0);
    vector<bool> dp2(t+1, 0);
    dp[0] = dp2[0] = 1;
    for (int i = 1; i <= t; i++) {
        if (i - a >= 0 && dp[i-a]) dp[i] = 1;
        if (i - b >= 0 && dp[i-b]) dp[i] = 1;
        dp2[i/2] = dp2[i/2] || dp[i];
    }
    for (int i = 1; i <= t; i++) {
        if (i - a >= 0 && dp2[i-a]) dp2[i] = 1;
        if (i - b >= 0 && dp2[i-b]) dp2[i] = 1;
    }
    int mx;
    for (int i = 0; i <= t; i++) {
        if (dp[i] || dp2[i]) mx = i;
    }
    return mx;
}

int main() {
    ifstream fin("feast.in");
    ofstream fout("feast.out");
    int t, a, b;
    fin >> t >> a >> b;
    fout << res(t, a, b);
}