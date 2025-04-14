#include<bits/stdc++.h>
using namespace std;

#define debug(...) 42

#define int long long
using ll = long long;

const int maxn = 1e5;
const int mod = 1e9 + 7;

int dp[maxn][4][4][4];
string b = "ACGT";

void solve(){
   string s;
   cin >> s;
   int n = s.size();
   for (int i = 0; i < 4; i++){
      for (int j = 0; j < 4; j++){
         if (s[0] == '?' || s[0] == b[j]){
            dp[0][i][j][j] = 1;
         }
      }
   }
   for (int i = 1; i < n; i++){
      for (int m2 = 0; m2 < 4; m2++){
         if (s[i] != '?' && s[i] != b[m2]) continue;
         for (int n = 0; n < 4; n++){
            for (int l = 0; l < 4; l++){
               for (int m = 0; m < 4; m++){
                  // add
                  if (m2 != m){
                     dp[i][n][l][m2] = (dp[i][n][l][m2] + dp[i - 1][n][l][m]) % mod;
                  }
                  // split
                  if (n == m){
                     dp[i][l][m2][m2] = (dp[i][l][m2][m2] + dp[i - 1][n][l][m]) % mod;
                  }
               }
            }
         }
      }
   }
   int ans = 0;
   for (int i = 0; i < 4; i++){
      for (int j = 0; j < 4; j++){
         ans = (ans + dp[n - 1][i][j][i]) % mod;
      }
   }
   cout << ans;
}

int32_t main() {
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   int tt = 1;
   // cin >> tt;
   while(tt--) {
      solve();
   }
   return 0;
}
