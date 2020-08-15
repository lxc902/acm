#include <vector>
#include <cassert>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define ll long long
#define pb push_back
#define all(x) x.begin(), x.end()
// #include <bits/stdc++.h>
 
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
}
 
// DFS on tree. Usage: dfs(graph, root, pre-processing, post-processing);
namespace {
auto noop = [](int x, int pa){};
using proc_func = std::function<void(int x, int pa)>;
void dfs(const vector<vector<int>>& g, int x, int parent, proc_func pre, proc_func post) {
  pre(x, parent);
  for(int y : g[x]) {
    if (y==parent) continue;
    dfs(g, y, x, pre, post);
  }
  post(x, parent);
}
void dfs(const vector<vector<int>>& g, int root, proc_func pre, proc_func post) {
  dfs(g, root, /*parent=*/-1, pre, post);
}
void dfspre(const vector<vector<int>>& g, int root, int parent, proc_func pre) {
  dfs(g, root, parent, pre, noop);
}
void dfspost(const vector<vector<int>>& g, int root, int parent, proc_func post) {
  dfs(g, root, parent, noop, post);
}
} // namespace

// Min Priority Queue
template<typename T = int, typename Compare = std::less<T>>
class PQ {
  /**
  Usage 1 (defaut): Min Int PQ, i.e. top() gives minimum:
    PQ pq;

  Usage 2: custom comparator (becomes Max Int PQ):
    auto cmp = [&](auto i, auto j) { return i > j; };
    PQ pq(cmp);

  Usage 3: custom type + comparator (becomes Max Double PQ):
    auto cmp = [&](auto i, auto j) { return i > j; };
    PQ<double, decltype(cmp)> pq(cmp);
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
};

void solve() {
  int n; cin>> n;
  vector<pair<int,int>> phs(n);
  for(int i=0;i<n;i++) cin >> phs[i].first >> phs[i].second;
  sort(all(phs));
  map<int,int> left;
  auto update = [&](int& bst, int val) {
    if (val>bst) bst = val;
  };
  int mx=0;
  for(auto ph : phs) {
    int pi = ph.first;
    int hi = ph.second;
    update(left[pi+hi], left[pi]+hi);
    update(left[pi], left[pi-hi]+hi);
    mx = max(mx, left[pi+hi]);
    mx = max(mx, left[pi]);
  }
  cout << mx << endl;
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
