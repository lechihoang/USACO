#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() { 
   int u;
   cin >> u;
   if (u == 1) {
      int c, t;
      cin >> c >> t;
      if (c == t) {
         cout << c << "\n";
         return;
      }
      int cur = c, pos = c;
      while (cur < t) {
         if (pos > cur / 2) {
            int nxt = 2 * pos;
            if (nxt > t) {
               cout << pos << "\n";
               return;
            }
            cur = nxt;
            pos--;
         } 
         else if (pos == 0) {
            cur++;
            pos = cur / 2;
      } else {
         if (t - cur <= pos) {
            cout << pos - t + cur << "\n";
            return;
         }
         cur += t - cur;
         pos = 0;
      }
   }
   cout << pos << "\n";
   } 
   else {
      int x, t;
      cin >> x >> t;
      int pos = x;
      if (x == t) {
         cout << x << "\n";
         return;
      }
      while (1) {
         if (pos == t) {
            cout << pos << "\n";
            return;
         }
         if (pos > t / 2) {
            cout << pos << "\n";
            return;
         }
         if (pos == t / 2) {
            pos = 0;
            t--;
         } else {
            int val = (t - 2 * pos) / 3;
            pos += max(val, 1ll);
            t -= max(val, 1ll);
         }
      }
   }
}

int32_t main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   int tt = 1;
   cin >> tt;
   while (tt--) {
      solve();
   }
   return 0;
}
