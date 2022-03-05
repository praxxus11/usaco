#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("nocross.in");
    ofstream fout("nocross.out");
    int n;
    fin >> n;
    vector<int> l(n), r(n);
    for (int& i : l) fin >> i;
    for (int& i : r) fin >> i;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (abs(l[i]-l[j])<=4) {
                dp[i][j]++;
                if (i&&j) dp[i][j] += dp[i-1][j-1];
            }
            else {
                int a=0, b=0;
                if (i) a = dp[i-1][j];
                if (j) b = dp[i][j-1];
                dp[i][j] = max(a, b);
            }
        }
    }
    int res = -1;
    for (auto v : dp) {
        for (auto i : v) if (i > res) res = i;
    }
    fout << res;
}