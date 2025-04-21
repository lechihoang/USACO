#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define debug(...) 42
#endif

#define int long long

int n, k;

struct Block{
   int hi = -1e18;
   int lo = 1e18;
   vector<int> val;
   Block(vector<int> a){
      for (auto i : a){
         val.push_back(i);
         hi = max(hi, i);
         lo = min(lo, i);
      }
   }
   void add(int x){
      lo = min(lo, x);
      hi = max(hi, x);
      val.push_back(x);
      int i = val.size() - 1;
      while(i > 0 && abs(val[i] - val[i - 1]) <= k){
         swap(val[i], val[i - 1]);
         i--;
      }
      while(i < val.size() - 1 && val[i] > val[i + 1]){
         swap(val[i], val[i + 1]);
         i++;
      }
   }
   bool toen(int x){
      val.push_back(x);
      int i = val.size() - 1;
      while(i > 0 && abs(val[i] - val[i - 1]) <= k){
         swap(val[i], val[i - 1]);
         i--;
      }
      while(i < val.size() - 1 && val[i] > val[i + 1]){
         swap(val[i], val[i + 1]);
         i++;
      }
      bool ans = val.back() == x;
      val.erase(val.begin() + i);
      return ans;
   }
};


void solve(){
   cin >> n >> k;
   const int len = floor(sqrt(n));
   vector<Block> sqrt = {Block({})};
   for (int i = 0; i < n; i++){
      int x;
      cin >> x;
      int j = sqrt.size() - 1;
      while(j > 0 && (x + k >= sqrt[j].hi && x - k <= sqrt[j].lo)) j--;
      if (j < sqrt.size() - 1 && sqrt[j].toen(x)){
         j++;
         while(j < sqrt.size() - 1 && x >= sqrt[j].hi) j++;
      }
      sqrt[j].add(x);
      if (sqrt[j].val.size() > len){
         int mid = (sqrt[j].val.size()) / 2;
         vector<int> l(sqrt[j].val.begin(), sqrt[j].val.begin() + mid);
         vector<int> r(sqrt[j].val.begin() + mid, sqrt[j].val.end());
         sqrt.insert(sqrt.begin() + j, Block(l));
         sqrt[j + 1] = Block(r);
      }
   }
   for (auto x : sqrt){
      for (auto y : x.val){
         cout << y << "\n";
      }
   }
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
