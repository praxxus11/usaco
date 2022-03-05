#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("milkorder.in");
    ofstream fout("milkorder.out");
    int n, m, k;
    fin >> n >> m >> k;
    vector<int> ord(m);
    vector<bool> cows(n+1, 0);
    vector<pair<int,int>> sp(k);
    for (int& i : ord) fin >> i;
    for (pair<int,int>& pr : sp) fin >> pr.first >> pr.second;

    for (pair<int,int>& pr : sp) {
        
        int target = pr.first;
        cows[pr.second] = 1;
        for (int i=0; i<ord.size(); i++) {
            if (ord[i] == target) {
                int oi = i;
                int ci = pr.second;
                while (ord[oi] != -1 && oi >= 0) {
                    if (cows[ci] == 0) {
                        cows[ci] = 1;
                        ord[oi] = -1;
                        oi--;
                    }
                    ci--;
                } 
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!cows[i]) {
            fout << i;
            break;
        }
    }

}