#include <bits/stdc++.h>
using ll=long long;
#define pb push_back
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define vll vector<ll>
 
using namespace std;


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



void input(vll& a, int n, int k) {
  for(int i=0;i<k;i++) {
    cin >> a[i];
  }
  vll p(4);
  for (int i=0;i<4;i++) cin>>p[i];
  for (int i=k;i<n;i++) {
    a[i] = (p[0]*a[i-2] + p[1]*a[i-1] + p[2])%p[3] + 1;
  }
}

void solve() {
  int n,m,k,fuck;
  cin >> n >> m >> k >> fuck;
  vll p(n); vll q(m);
  input(p, n, k);
  input(q, m, k);
  //debug(p);
  //debug(q);
  sort(all(p)); sort(all(q));
  ll L=0, R=1000000000L;
  auto cost = [](ll x, ll l, ll r) {
    assert (l<=r);
    if (x<=l) return r-x;
    if (x>=r) return x-l;
    ll d = min(x-l, r-x);
    return d+r-l;
  };
  auto ok = [&](ll ans) {
    int j=m-1;
    for(int i=n-1;i>=0;i--) {
      ll right =  j>=0 ? q[j] : 0;
      while(j>=0 && cost(p[i], q[j], right) <= ans) {
        j--;
      }
    }
    return j<0;
  };
  while(L<R) {
    ll m = (L+R)/2;
    if (ok(m)) R=m;
    else L=m+1;
  }
  cout << R << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  for(int i=1;i<=t;i++) {
    cout<< "Case #"<<i<<": ";
    solve();
  }
  return 0;
}
