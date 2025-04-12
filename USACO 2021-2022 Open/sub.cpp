#include<bits/stdc++.h>
using namespace std;

#define debug(...) 42

#define int long long
using ll = long long;

struct A{
   int q, t, x, n;
   bool operator < (const A& y){
      if (x - t == y.x - y.t) return q > y.q;
      return x - t < y.x - y.t;
   }
};

void solve(){
   int N;
   cin >> N;
   map<int,int> mp;
   vector<A> p(N);
   for (int i = 0; i < N; i++) cin >> p[i].q >> p[i].t >> p[i].x >> p[i].n;
   sort(p.begin(), p.end());
   int ans = 0;
   for (int i = 0; i < N; i++){
      auto [q, t, x, n] = p[i];
      if (q == 2) mp[x + t] += n;
      else{
         while(n){
            map<int, int>::iterator it = mp.lower_bound(x + t);
            if (it == mp.end()) break;
            int sub = min(n, it->second);
            it->second -= sub;
            if (it->second == 0) mp.erase(it);
            n -= sub;
            ans += sub;
         }
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
