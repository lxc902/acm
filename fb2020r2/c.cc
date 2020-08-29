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


// Mx Priority Queue
//template<typename T = int, typename Compare = std::greater<T>> // !!
class PQ {
  /**
  Usage 1 (defaut): Min int PQ, i.e. top() gives minimum:
    PQ s;

  Usage 2: custom comparator (becomes Max int PQ):
    auto cmp = [&](auto i, auto j) { return i > j; };
    PQ s(cmp);

  Usage 3: custom type (becomes Min ll PQ):
    PQ<ll> s;

  Usage 4.1: custom type + std comparator (becomes Max ll PQ):
    PQ<ll, std::greater<ll>> s;
  Usage 4.2: custom type + custom comparator (becomes Max double PQ):
    auto cmp = [&](auto i, auto j) { return i > j; };
    PQ<double, decltype(cmp)> s(cmp);
  */
 public:
  using T = int;
  using Compare = std::greater<T>;
  PQ(Compare comp = Compare()):s(comp) {}
  void make(const vector<T>& in) { s.insert(all(in)); }
  void make(initializer_list<T> in) { s.insert(all(in)); }

  const T& top() { assert(!s.empty()); return *s.begin(); }
  void pop() { assert(!s.empty());  s.erase(s.begin()); }
  void insert(T v) { s.insert(v); }
  void remove(T v) { auto it=s.find(v); if(it!=s.end()) {s.erase(it);} }

  bool empty() { return s.empty(); }
  multiset<T, Compare> s;  // DNS private
 private:
}; // t/PQ



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



void input(vll& a, int n, int k, int mod) {
  for(int i=0;i<k;i++) {
    cin >> a[i];
  }
  vll p(3);
  for (int i=0;i<3;i++) cin>>p[i];
  for (int i=k;i<n;i++) {
    a[i] = (p[0]*a[i-2] + p[1]*a[i-1] + p[2])%mod;
  }
}
ll sum(vll& a) {
  ll s=0;
  for (ll x : a) s+=x;
  return s;
}

const int P = 1000000007;
void solve() {
  int n,m,e,k; cin>>n>>m>>e>>k;
  vll x(n);
  vll y(n);
  input(x, n, k, m);
  input(y, n, k, m);
  vll I(e);
  vll W(e);
  input(I, e, k, (n*m+n));
  input(W, e, k, 1000000000);
  //debug(x,y,I,W);
  //debug(x);
  //debug(y);

  vll wei( n*m+n , 1);
  ll sw = n*m+n;
  PQ big;
  vector<PQ> sml(n);
  vector<PQ> sml_bet(n); //bet xy
  vector<PQ> sml_oth(n); // <x or > y
  ll sum_sml_top = n;
  PQ cut2nd;

  { // init PQs
    for(int i=0;i<n;i++) big.insert(1);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) sml[i].insert(1);
    for(int i=0;i<n;i++) if(x[i]>y[i]) swap(x[i], y[i]);
    for(int i=0;i<n;i++) assert(x[i]<=y[i]);
    for(int i=0;i<n;i++) {
      if(x[i]==y[i]) continue;
      for(int j=x[i];j<y[i];j++) sml_bet[i].insert(1);
      for(int j=0;j<x[i];j++) sml_oth[i].insert(1);
      for(int j=y[i];j<m;j++) sml_oth[i].insert(1);
    }
  }
  auto upd = [&](int eid, int neww) {
    if (eid < n*m) { // small circles
      int i = eid/m;
      int j = eid%m;
      sum_sml_top -= sml[i].top();
      sml[i].remove(wei[eid]);
      sml[i].insert(neww);
      sum_sml_top += sml[i].top();
      if (x[i]!=y[i]) {
        cut2nd.remove(min(sml_bet[i].top() , sml_oth[i].top()));
        if (j>=x[i] && j<y[i]) { sml_bet[i].remove(wei[eid]); sml_bet[i].insert(neww); }
        else { sml_oth[i].remove(wei[eid]); sml_oth[i].insert(neww); }
        cut2nd.insert(min(sml_bet[i].top() , sml_oth[i].top()));
        //max_cut2 = max(max_cut2, ll(sum_sml_top + sml_bet[i].top() + sml_oth[i].top() - sml[i].top()));
      }
    } else {
      big.remove(wei[eid]); big.insert(neww);
    }
    sw -= wei[eid]; sw += neww;
    wei[eid] = neww;
  };
  auto calc = [&]() {
    ll a = big.top() + sum_sml_top;
    if (!cut2nd.empty()) {
      ll a2 = sum_sml_top + cut2nd.top();
      a = max(a, a2);
    }
    a = sw - a;
    return (a%P + P)%P;
  };

  ll ans=1;
  for(int i=0;i<e;i++) {
    upd(I[i], W[i]);
    ans = ans*calc()%P;
    //debug(i,calc());
  }
  //debug(x);
  //debug(y);
  //debug(I);
  //debug(W);
  //debug(wei);
  cout << ans << endl;
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
