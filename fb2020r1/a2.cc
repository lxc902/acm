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
  Usage 1 (defaut): Min Int PQ, i.e. top() gives minimum:
    PQ s;

  Usage 2: custom comparator (becomes Max Int PQ):
    auto cmp = [&](auto i, auto j) { return i > j; };
    PQ s(cmp);

  Usage 3.1: custom type + comparator (becomes Min LL PQ):
    PQ<ll, std::greater<ll>> s(cmp);

  Usage 4: custom type + comparator (becomes Max Double PQ):
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
  auto cmp = [&](auto i, auto j) { return abs(i) < abs(j); };
  PQ<ll, decltype(cmp)> s(cmp);
  ll peri = (h[0]+w[0])*2%P;
  ll ans = peri%P;
  s.insert(+l[0]);
  s.insert(-(l[0]+w[0]));
  for(int i=1;i<n;i++) {
    ll L = l[i];
    ll R = l[i]+w[i];
    auto lo = s.s.lower_bound(L);
    auto up = s.s.upper_bound(R);
    ll lastr=-1;
    vll rm;
    for(auto it = lo; it != up; it++) {
      ll v = *it;
      if (v > 0) {
        if (lastr != -1) {
          peri = (peri + (abs(v) - lastr)*2)%P;
          peri = ((peri - h[i]*2)%P + P)% P;
        }
      } else lastr = abs(v);
      rm.pb(v);
    }
    int insL = 1, insR = 1;
    if (lo != up) {
      if (*lo > 0) peri = (peri + (*lo - L)*2)%P;
      else insL = 0;
      auto la = up;
      la -- ;
      if (*la < 0) peri = (peri + (R - abs(*la))*2)%P;
      else insR = 0;
    }
    if (lo == up) {
      if (up == s.s.end() || *up > 0) {
        peri = (peri + (h[i] + w[i])*2)%P;
      } else insL = insR = 0;
    }
    //debug(peri);

    ans = (ans * peri)%P;
    for(ll v : rm) s.remove(v);
    if (insL) s.insert(L);
    if (insR) s.insert(-R);
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
