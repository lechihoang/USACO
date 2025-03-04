#include<bits/stdc++.h>

using namespace std;

void solve(){
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto& x : a) cin >> x;
  vector<pair<int,int>> b;
  b.push_back({-1, n});
  int suf = -1;
  for (int i = n - 1; i >= 0; i--){
    suf = max(suf, a[i]);
    if (a[i] == suf) b.push_back({a[i], i});
  } 
  b.push_back({n + 1, -1});
  reverse(b.begin(), b.end());
  for (int i = 1; i < b.size() - 1; i++){
    if (b[i].first != b[i + 1].first){
      vector<pair<int,int>> add;
      suf = b[i + 1].first;
      for (int j = b[i + 1].second - 1; j > b[i - 1].second; j--){
        if (b[i].second == j) continue;
        suf = max(suf, a[j]);
        if (suf == a[j]) add.push_back({a[j], j});
      }
      reverse(add.begin(), add.end());
      if (add.size()){
        b.insert(b.begin() + i + 1, add.begin(), add.end());
        break;
      }
    }
  }
  for (int i = 1; i < b.size() - 1; i++){
    cout << a[b[i].second] << " \n"[i == b.size() - 2];
  }
}


int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
  return 0;
}