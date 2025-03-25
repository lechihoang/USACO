#include<bits/stdc++.h>
using namespace std;

#define debug(...) 42


#define int long long
using ll = long long;

using P = pair<int,int>;
bitset<300> b[300][300];

int cross(P a, P b, P c){
  P ab = {b.first - a.first, b.second - a.second};
  P ac = {c.first - a.first, c.second - a.second};
  return ab.first * ac.second - ac.first * ab.second;
}

void solve(){
  int n;
  cin >> n;
  vector<P> a(n);
  for (auto& [x, y] : a) cin >> x >> y;
  debug(a);
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (j == i) continue;
      for (int k = 0; k < n; k++){
        if (cross(a[i], a[j], a[k]) > 0) b[i][j][k] = 1;
      }
    }
  }
  vector<int> ans(n - 2);
  for (int i = 0; i < n; i++){
    for (int j = i + 1; j < n; j++){
      for (int k = j + 1; k < n; k++){
        vector<int> t = {i, j, k};
        // debug(t);
        if (cross(a[t[0]], a[t[1]], a[t[2]]) < 0) swap(t[1], t[2]);
        auto val = b[t[0]][t[1]] & b[t[1]][t[2]] & b[t[2]][t[0]];
        ans[val.count()]++;
      }
    }
  }
  debug(ans);
  for (auto x : ans) cout << x << "\n";
}

int32_t main() {
  freopen("triangles.in", "r", stdin);
  freopen("triangles.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt = 1;
  // cin >> tt;
  while (tt--){
    solve();
  }
  return 0;
}
