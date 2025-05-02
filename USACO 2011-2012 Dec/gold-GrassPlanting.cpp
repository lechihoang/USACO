#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define debug(...) 42
#endif

#define int long long
using ll = long long;

const int maxn = 1e5 + 5;
int par[maxn], heavy[maxn], tin[maxn], sz[maxn], head[maxn], dep[maxn], timeDfs = 0, n, q;
vector<int> ad[maxn];

struct SegmentTree
{
   int n;
   vector<ll> st, lz;

   SegmentTree(int _n = 0){
      n = _n;
      st.assign((_n << 2) + 5, 0);
      lz.assign((_n << 2) + 5, 0);
   }
   void push(int id, int l, int r){
      int tmp = lz[id], x = id << 1, y = id << 1 | 1;
      int mid = (l + r) >> 1;
      st[x] += tmp * (mid - l + 1); lz[x] += tmp;
      st[y] += tmp * (r - mid) ; lz[y] += tmp;
      lz[id] = 0;
    }

   void update(int id, int l, int r, int u, int v, int val){
      if (l > v || r < u) return;
      if (l >= u && r <= v) {
         st[id] += val * (r - l + 1);
         lz[id] += val; 
         return;
      }

      push(id, l, r);

      int mid = (l + r) >> 1;
      update(id << 1, l, mid, u, v, val);
      update(id << 1 | 1, mid + 1, r, u, v, val);
 
      st[id] = st[id << 1] + st[id << 1 | 1];
   }

   int get(int id, int l, int r, int u, int v){
      if (v < l || u > r) return 0;
      if (l >= u && r <= v) return st[id];
      push(id, l, r);
      int mid = (l + r) >> 1;
      return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
   }
   void update(int l, int r, int val){
      update(1, 1, n, l, r, val);
   }

   int get(int l, int r){
      return get(1, 1, n, l, r);
   }
};

SegmentTree Segtree;

void dfs(int u){
   int mx = -1;
   sz[u] = 1;
   for (auto v : ad[u]){
      if (v == par[u]) continue;
      par[v] = u;
      dep[v] = dep[u] + 1;
      dfs(v);
      sz[u] += sz[v];
      if (mx == -1 || sz[v] > sz[mx]) mx = v; 
   }
   heavy[u] = mx;
}

void hld(int u, int h){
   head[u] = h;
   tin[u] = ++timeDfs;
   if (heavy[u] != -1) hld(heavy[u], h);
   for (auto v : ad[u]){
      if (v != par[u] && v != heavy[u]){
         hld(v, v);
      }
   }
}

void hld_update(int u, int v, int val){
   while(head[u] != head[v]){
      if (dep[head[u]] < dep[head[v]]) swap(u, v);
      Segtree.update(tin[head[u]], tin[u], val);
      u = par[head[u]];
   }
   if (dep[u] > dep[v]) swap(u, v);
   u = heavy[u];
   if (u != -1 && tin[u] <= tin[v]) Segtree.update(tin[u], tin[v], val);
}

int hld_query(int u, int v){
   int ans = 0;
   while(head[u] != head[v]){
      if (dep[head[u]] < dep[head[v]]) swap(u, v);
      ans += Segtree.get(tin[head[u]], tin[u]);
      u = par[head[u]];
   }
   if (dep[u] > dep[v]) swap(u, v);
   u = heavy[u];
   if (u != -1 && tin[u] <= tin[v]) ans += Segtree.get(tin[u], tin[v]);
   return ans;
}

int32_t main() {
   freopen("grassplant.in", "r", stdin);
   freopen("grassplant.out", "w", stdout);
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   memset(heavy, -1, sizeof heavy);
   cin >> n >> q;
   Segtree = SegmentTree(n);
   for (int i = 0; i < n - 1; i++){
      int u, v;
      cin >> u >> v;
      ad[u].push_back(v);
      ad[v].push_back(u);
   }
   dep[1] = 1;
   dfs(1);
   hld(1, 1);
   while(q--){
      char t;
      int l, r;
      cin >> t >> l >> r;
      if (t == 'P') hld_update(l, r, 1);
      else cout << hld_query(l, r) << "\n";
   }
   return 0;
}
