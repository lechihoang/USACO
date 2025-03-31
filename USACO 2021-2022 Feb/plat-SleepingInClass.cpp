#include<bits/stdc++.h>
using namespace std;

#define debug(...) 42


#define int long long

const int maxn = 1e5 + 5;
const int maxb = 103680;

int pre[maxn];
int queries[maxn];
int freq[maxb];

vector<pair<int,int>> prime;


int num(){
  int cnt = 1;
  for (auto [a, b] : prime){
    cnt *= b + 1;
  }
  return cnt;
}

int& get(int val){
  int idx = 0;
  for (int j = 0; j < prime.size(); j++){
    int cnt = 0;
    while(val % prime[j].first == 0){
      val /= prime[j].first;
      cnt++;
    }
    idx = idx * (prime[j].second + 1) + min(cnt, prime[j].second);
  }
  return freq[idx];
}


void solve(){
    int n;
    cin >> n;
    vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++){
      cin >> pre[i];
      pre[i] += pre[i - 1]; 
    }
    int r = pre[n];
    for (int i = 2; i <= 1e6; i++){
      if (r % i == 0){
        int cnt = 0;
        while(r % i == 0){
          r /= i;
          cnt++;
        }
        prime.push_back({i, cnt});
      }
    }
    for (int i = 1; i < n; i++){
      int tmp = __gcd(r, pre[i]);
      if (tmp != 1 && tmp != r){
        if (tmp > r / tmp){
          tmp = r / tmp;
        }
        if (tmp * tmp == r){
          prime.push_back({tmp, 2});
        }
        else{
          prime.push_back({tmp, 1});
          prime.push_back({r / tmp, 1});
        }
        r = 1;
      }
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
      cin >> queries[i];
      int tmp = queries[i];
      if(r % tmp == 0 && tmp != 1 && tmp != r){
        if(tmp > r / tmp){
        tmp = r /tmp;
      }
      if(tmp * tmp == r){
        prime.push_back({tmp, 2});
      }
      else{
        prime.push_back({tmp, 1});
        prime.push_back({r / tmp, 1});
      }
        r = 1;
      }
    }
    if(r != 1) prime.push_back({r, 1});
    for (int i = 1; i <= n; i++){
      get(pre[i])++;
    }
    int block = 1;
    for (int i = prime.size() - 1; i >= 0; i--){
      for (int j = num() - 1; j >= 0; j--){
        if (j / block % (prime[i].second + 1) > 0){
          freq[j - block] += freq[j];
        }
      }
      block *= prime[i].second + 1;
    }
    for (int i = 0; i < q; i++){
      if (pre[n] % queries[i] != 0){
        cout << -1 << "\n";
      }
      else{
        int ans = n + pre[n] / queries[i] - get(queries[i]) * 2; 
        cout << ans << "\n";
      }
    }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt = 1;
  // cin >> tt;
  while (tt--){
    solve();
  }
  return 0;
}
