#include <bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;



// Debug functions.
namespace std {
    // To Use: `debug(arr[123]);`
    // Enable in Local Run: $ g++ -D LOCAL_DEBUG a.cc -o a.out;
    // Using `std` to make complier prefer std::to_string for primitives.
 
    template <typename A, typename B>
    string to_string(pair<A, B> p);
    
    template <typename A, typename B, typename C>
    string to_string(tuple<A, B, C> p);
    
    template <typename A, typename B, typename C, typename D>
    string to_string(tuple<A, B, C, D> p);
    
    string to_string(const string& s) {
    return '"' + s + '"';
    }
    
    string to_string(const char* s) {
    return to_string((string) s);
    }
    
    string to_string(bool b) {
    return (b ? "true" : "false");
    }
    
    string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
        res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
    }
    
    template <size_t N>
    string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
    }
    
    template <typename A>
    string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
        res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
    }
    
    template <typename A, typename B>
    string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
    }
    
    template <typename A, typename B, typename C>
    string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
    }
    
    template <typename A, typename B, typename C, typename D>
    string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
    }
    
    void debug_out() { cerr << endl; }
    
    template <typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
    }
    
    #ifdef LOCAL_DEBUG
    #define debug(...) cerr << "[" << __LINE__ << ": " \
        << #__VA_ARGS__ << "] = ", debug_out(__VA_ARGS__)
    #else
    #define debug(...) 42
    #endif
} // t/debug



int T;
void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  vector<bool> cov(n, false);
  for (int i=0;i<n;i++) cov[i] = s.at(i)=='#';
  vector<vi> g(n);
  auto add = [&](int x, int y) {
    --x; --y;
    g[x].pb(y);
    g[y].pb(x);
  };
  vi e(n+1);
  for(int i=2;i<=k+1;i++) {
    cin >> e[i];
    add(i, e[i]);
    //debug(i, e[i]);
  }
  ll a,b,c; cin >> a >> b >> c;
  for (int i=k+2;i<=n;i++) {
    e[i] = (a*e[i-2] + b*e[i-1] + c)%(i-1)+1;
    add(i, e[i]);
    //debug(i, e[i]);
  }
  for(int i=1;i<n;i++) e[i]=e[i+1]-1; //!
  vi vis(n, -1);
  function<void(int,int,int)> dfs = [&](int x, int pa, int col) {
    vis[x] = col;
    for(int v : g[x]) if (v!=pa) {
      if (!cov[v]) dfs(v, x, col);
    }
    return 0;
  };
  int cols = 0;
  for(int i=0;i<n;i++) {
    if(vis[i]==-1 && !cov[i]) dfs(i, -1, cols++);
  }
  vi cnt(cols, 0);
  for(int i=0;i<n;i++) {
    if (vis[i]>=0) cnt[vis[i]]++;
  }
  debug(n, a,b,c);
  debug(cols, e);
  // start calc ans.
  if (cols <= 1) {
    vll down(n);
    function<void(int,int)> dfsdown = [&](int x,int pa) {
      down[x] = 1;
      for(int v : g[x]) if (v!=pa) {
        dfsdown(v, x);
        down[x] += down[v];
      }
    };
    dfsdown(0, -1);
    //ll ans1= cols==0 ? 0 : ( (cnt[0])*(cnt[0]-1)/2 ); // WOW ll() WRONG! stack overflow.
    // Fortunately FB Hacker Cup 2020 Round 1 C: Quarantine didn't have that case in
    // their system test...
    ll ans1= cols==0 ? 0 : ( ll(cnt[0])*(cnt[0]-1)/2 ); // WOW ll() OK (see c.in.ll).
    ll ans2= 0;
    //debug(down);
    for(int i=1;i<n;i++) {
      if (cov[i] || cov[e[i]]) {
        ans2 += down[i]*(n-down[i]);
      }
    }
    if (cols==1) {
      vll downgood(n);
      function<void(int,int)> dfsdowngood = [&](int x,int pa) {
        downgood[x] = 1;
        for(int v : g[x]) if (v!=pa && !cov[v]) {
          dfsdowngood(v, x);
          downgood[x] += downgood[v];
        }
      };
      int fir =-1;
      for(int i=0;i<n;i++) if (!cov[i]) {dfsdowngood(i, -1); fir=i; break;}
      //debug(downgood);
      for(int i=1;i<n;i++) if (!cov[i] && !cov[e[i]] && i!=fir) {
        ll x = downgood[i]; ll y = cnt[0] - downgood[i];
        assert(fir >= 0);
        ans2 += x*y;
      }
    }
    cout << ans1 << ' ' <<  ans2 << endl;
    return;
  }
  // cols >=2
  //debug(cnt);
  int bade = n-1;
  int mx1 = -1; int mx2 = -1;
  for (int i=0;i<cols;i++) {
    bade -= cnt[i]-1;
    if (cnt[i]>mx1) {mx2=mx1; mx1=cnt[i];}
    else if (cnt[i]>mx2) {mx2=cnt[i];}
  }
  assert(mx1>0);
  assert(mx2>0);
  vll down1(n); vll down2(n);
  function<void(int,int)> dfsdown12 = [&](int x,int pa) {
    if (!cov[x]) {
      down1[x] = cnt[vis[x]] == mx1;
      down2[x] = cnt[vis[x]] == mx2;
    } else down1[x]=down2[x]=0;
    for(int v : g[x]) if (v!=pa) {
      dfsdown12(v, x);
      down1[x] += down1[v];
      down2[x] += down2[v];
    }
  };
  dfsdown12(0, -1);
  //debug(down1);
  //debug(down2);
  ll ans1, ans2;
  auto C2 = [](ll x) {return x*(x-1)/2;};
  vi scnt(cnt); sort(all(scnt)); reverse(all(scnt)); // sorted
  if (mx1 == mx2) {
    ans1 = C2(mx1*2);
    for(int i=2;i<cols;i++) ans1 += C2(scnt[i]);
    ans2 = 0;
    for (int i=1;i<n;i++) if (cov[i] || cov[e[i]]) { // bad e
      ans2 += down1[i] * (down1[0] - down1[i]);
    }
  } else { // mx1 > mx2
    ans1 = C2(mx1 + mx2);
    for(int i=2;i<cols;i++) ans1 += C2(scnt[i]);
    ans2 = 0;
    for (int i=1;i<n;i++) if (cov[i] || cov[e[i]]) { // bad e
      ans2 += down1[i] * (down2[0] - down2[i]);
      ans2 += down2[i] * (down1[0] - down1[i]);
    }
  }
  cout << ans1 << ' ' <<  ans2 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  for(int i=1;i<=t;i++) {
    T=i;
    cout<< "Case #"<<i<<": ";
    solve();
  }
  return 0;
}
