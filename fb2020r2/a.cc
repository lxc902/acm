#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) x.begin(), x.end()
//#define pct __builtin_popcount // count of 1s
// ll: _popcountll; _ctz: tail zeros; _clz: leading zeros.



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
    a[i] = (p[0]*a[i-2] + p[1]*a[i-1] + p[2])%p[3] ;
  }
}
ll sum(vll& a) {
  ll s=0;
  for (ll x : a) s+=x;
  return s;
}
void solve() {
  int n,k; cin >> n >> k;
  vll s(n);
  vll x(n);
  vll y(n);
  input(s, n, k);
  input(x, n, k);
  input(y, n, k);
  ll sx=sum(x); ll sy =sum(y); ll ss=sum(s);
  if (ss < sx || ss > (sx+sy)) cout << -1 << endl;
  else {
    ll ans1=0; ll ans2=0;
    for(int i=0;i<n;i++) {
      if (s[i]<x[i]) ans1+=(x[i]-s[i]);
      if (s[i]>x[i]+y[i]) ans2+=(s[i]-x[i]-y[i]);
    }
    cout<<max(ans1,ans2)<<endl;
  }
  //debug(s, x, y);
  //debug(ss, sx, sy);
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
