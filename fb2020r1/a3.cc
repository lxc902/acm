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


// Min Priority Queue
template<typename T = int, typename Compare = std::less<T>>
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


void solve() {
  int n,k;
  cin >> n >> k;
  vll l(n);
  for (int i=0;i<k;i++) cin>>l[i];
  vll pl(4);
  for (int i=0;i<4;i++) cin>>pl[i];
  auto calc = [](ll v2, ll v1, vll p) {
    return (p[0]*v2%p[3] + p[1]*v1%p[3] + p[2])%p[3] + 1;
  };
  for (int i=k;i<n;i++) l[i]=calc(l[i-2], l[i-1], pl);
  vll w(n);
  for (int i=0;i<k;i++) cin>>w[i];
  vll pw(4);
  for (int i=0;i<4;i++) cin>>pw[i];
  for (int i=k;i<n;i++) w[i]=calc(w[i-2], w[i-1], pw);
  vll h(n);
  for (int i=0;i<k;i++) cin>>h[i];
  vll ph(4);
  for (int i=0;i<4;i++) cin>>ph[i];
  for (int i=k;i<n;i++) h[i]=calc(h[i-2], h[i-1], ph);
  //debug(l);
  //debug(w);
  //debug(h);

  const int P=1000000007;
  PQ<ll> s;
  map<ll, ll> left; // height left of the point
  map<ll, ll> delt; // delta of point
  ll peri = (w[0])*2%P;
  auto ins = [&](ll p, ll lh, ll d) {
    s.insert(p);
    left[p] = lh;
    delt[p] = d;
    peri = (peri + d)%P;
  };
  ins(l[0], 0, h[0]);
  ins(l[0]+w[0], h[0], h[0]);
  ll ans = peri%P;
  //debug(peri, ans);
  for(int i=1;i<n;i++) {
    ll L = l[i];
    ll R = l[i]+w[i];
    ll H = h[i];
    auto lo = s.s.lower_bound(L);
    auto up = s.s.upper_bound(R);
    ll lastp=L;
    vll rm;
    for(auto it = lo; it != up; it++) {
      ll v = *it;
      peri = ((peri - delt[v])%P + P)%P;
      if (left[v] == 0) peri = (peri + 2*(v-lastp))%P;
      lastp = v;
      rm.pb(v);
      //debug("removing", v, peri);
    }
    if (lo != up) {
      ll lr = 0;
      if (up != s.s.end()) lr = left[*up];
      auto la = up; la--;
      //debug(*la, peri);
      if (lr == 0) peri = (peri + 2*(R-*la))%P;

      ins(L, left[*lo], H-left[*lo]);
      //debug("add", L, peri);
      ins(R, H, H-lr);
      //debug("add", R, peri);
    }
    if (lo == up) {
      if (up == s.s.end() || left[*up] == 0) {
        ins(L, 0, H);
        ins(R, H, H);
        peri = (peri + w[i]*2)%P;
      } else {
        ins(L, left[*up], H-left[*up]);
        ins(R, H, H-left[*up]);
      }
    }

    ans = (ans * peri)%P;
    //debug(peri, ans);
    for(ll v : rm) {s.remove(v); if(v!=L && v!=R) {left.erase(v); delt.erase(v);}}
  }
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
