#include <iostream>
#include <vector>

using namespace std;

int main() {
    int s, n;
    cin >> s >> n;
    vector<int> v;
    vector<int> w;
    for (int i=0; i<n; i++) {
        int val, wei, quant;
        cin >> val >> wei >> quant;
        quant = min(quant, 2000/(wei+1));
        for (int q=0; q<quant; q++) {
            v.push_back(val);
            w.push_back(wei);
        }
    }
    vector<vector<int>> dp(v.size(), vector<int>(s+1, 0));
    for (int i=0; i<=s; i++) if (w[0] <= i) dp[0][i] = v[0];

    for (int i=1; i<v.size(); i++) {
        for (int j=1; j<=s; j++) {
            int a = 0;
            if (j-w[i] >= 0) a = v[i] + dp[i-1][j-w[i]];
            dp[i][j] = max(dp[i-1][j], a);
        }
    } 
    cout << dp[v.size()-1][s];
}