#include<bits/stdc++.h>

using namespace std;

#define int long long
const int maxn = 1e6 + 5;

using ll = long long;

vector<int> ad[maxn];
int ans[maxn], pos[maxn], lf[maxn];
vector<int> que;

int leaf = 0;

void dfs(int u){
  int add = 1;
  for (auto v : ad[u]){
    dfs(v);
    add = 0;
  }
  leaf += add;
}

void dfs2(int u, int lv){
  vector<pair<int, int>> val;
  int add = 1;
  for (auto v : ad[u]){
    dfs2(v, lv + 1);
    add = 0;
  }
  if (add){
    lf[u] = u;
  }
  else{
  for (auto x : ad[u]) val.push_back({pos[lf[x]], lf[x]});
  sort(val.begin(), val.end());
  for (int i = 0; i + 1 < val.size(); i++){
    ans[val[i].second] = lv + 1;
  }
  lf[u] = val.back().second;
  } 
}

void solve(){
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++){
    int u;
    cin >> u;
    pos[i] = n + 1;
    ad[u].push_back(i);
  }
  memset(ans, 0, sizeof ans);
  memset(pos, 0, sizeof pos);
  memset(lf, 0, sizeof lf);
  dfs(0);
  for (int i = 0; i < leaf; i++){
    int x;
    cin >> x;
    que.push_back(x);
    pos[x] = i;
  }
  dfs2(0, 0);
  for (auto x : que) cout << ans[x] << "\n";
}


int32_t main(){
  int t = 1;
  // cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
