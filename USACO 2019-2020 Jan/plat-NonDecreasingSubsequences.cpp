#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define debug(...) 42
#endif

#define int long long

const int maxn = 5e4 + 5;
const int maxq = 2e5 + 5;
const int mod = 1e9 + 7;

int a[maxn], ans[maxq];
int dpl[maxn][20], dpr[maxn][20], suml[maxn][20], sumr[maxn][20];

void dnc(int l, int r, vector<array<int, 3>>& que){
   if (!que.size()) return;
   int m = (l + r) / 2;
   for (int start = 0; start < 20; start++){
      fill(dpl[m + 1], dpl[m + 1] + 20, 0);
      dpl[m + 1][start] = 1;
      for (int i = m; i >= l; i--){
         for (int v = 0; v < 20; v++) dpl[i][v] = dpl[i + 1][v];
         for (int v = a[i]; v < 20; v++) dpl[i][a[i]] = (dpl[i][a[i]] + dpl[i + 1][v]) % mod;
      }
      for (int i = m + 1; i >= l; i--){
         int sum = 0;
         for (int v = 0; v < 20; v++) sum = (sum + dpl[i][v]) % mod;
         suml[i][start] = sum;
      }
   }
   for (int start = 0; start < 20; start++){
      fill(dpr[m], dpr[m] + 20, 0);
      dpr[m][start] = 1;
      for (int i = m + 1; i <= r; i++){
         for (int v = 0; v < 20; v++) dpr[i][v] = dpr[i - 1][v];
         for (int v = 0; v <= a[i]; v++) dpr[i][a[i]] = (dpr[i][a[i]] + dpr[i - 1][v]) % mod;
      }
      for (int i = m; i <= r; i++){
         int sum = 0;
         for (int v = 0; v < 20; v++) sum = (sum + dpr[i][v]) % mod;
         sumr[i][start] = sum;
      }
   }
   vector<array<int, 3>> left, right;
   for (auto [u, o, idx] : que){
      if (o < m){
         left.push_back({u, o, idx});
      }
      else if (m < u){
         right.push_back({u, o, idx});
      }
      else{
         int res = 0;
         for (int v = 0; v < 20; v++){
            int l1 = suml[u][v];
            if (v > 0){
               l1 = (l1 - suml[u][v - 1] + mod) % mod;
            }
            int r1 = sumr[o][v];
            res = (res + l1 * r1) % mod;
         }
         ans[idx] = (ans[idx] + res) % mod;
      }
   }
   if (l == r) return;
   dnc(l, m - 1, left);
   dnc(m + 1, r, right);
}

void solve(){
   int n, k, q;
   cin >> n >> k;
   for (int i = 1; i <= n; i++){
      cin >> a[i];
      a[i]--;
   }
   cin >> q;
   vector<array<int, 3>> b;
   for (int i = 0; i < q; i++){
      int l, r;
      cin >> l >> r;
      b.push_back({l, r, i});
   }
   dnc(1, n, b);
   for (int i = 0; i < q; i++) cout << ans[i] << "\n";
}

int32_t main() {
   freopen("nondec.in", "r", stdin);
   freopen("nondec.out", "w", stdout);
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   int tt = 1;
   // cin >> tt;
   while(tt--) {
      solve();
   }
   return 0;
}