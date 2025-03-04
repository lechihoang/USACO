#include<bits/stdc++.h>

using namespace std;

#define int long long
const int maxn = 1e6 + 5;

using ll = long long;

void solve(){
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  int ans = 0;
  if (a == c && b == d){
    cout << 0;
    return;
  } 
  while(a != c || b != d){
    if (c < a || d < b){
      cout << -1;
      return;
    }
    if (c > d){
      ans += max(1ll, (c - a) / d);
      c -= max(1ll, (c - a) / d) * d;
    }
    else if (d > c){
      ans += max(1ll, (d - b) / c);
      d -= max(1ll, (d - b) / c) * c;
    }
    else{
      cout << -1;
      return;
    }
  }
  cout << ans;
}


int32_t main(){
  int t = 1;
  cin >> t;
  while(t--){
    solve();
    cout << "\n";
  }
  return 0;
}