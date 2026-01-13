#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() { 
   int n, k;
   string s;
   cin >> n >> k >> s;
   vector<vector<int>> cnt(2, vector<int> (k, 0));
   for (int i = 0; i < k; i++){
     int val = 0;
     for (int j = i; j < n; j += k){
         cnt[val][i]++;
         if (j + k < n) val ^= (s[j] - '0') ^ (s[j + 1] - '0');
     }
   }
   int cur = s[0] - '0';
   int mi = 0, mx = 0, cur0 = 0, cur1 = 0, get = 1e9;
   for (int i = 0; i < k; i++){
      mi += min(cnt[0][i], cnt[1][i]);
      mx += max(cnt[0][i], cnt[1][i]);
      if (cnt[0][i] < cnt[1][i]) cur0 ^= 1; 
      if (cnt[0][i] > cnt[1][i]) cur1 ^= 1;
      get = min(get, abs(cnt[0][i] - cnt[1][i]));
   }
   if (cur0 != cur) mi += get;
   if (cur1 != cur) mx -= get;
   cout << mi << " " << mx << "\n";
}

int32_t main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   int tt = 1;
   cin >> tt;
   vis.resize(maxn);
   while(tt--) {
      solve();
   }
   return 0;
}
