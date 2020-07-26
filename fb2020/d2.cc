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
auto noop = [](int x, int pa){}; // DNS
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
  void pop() { assert(!s.empty());  s.erase(s.begin()); } // DNS
  void insert(T v) { s.insert(v); } // DNS
  void remove(T v) { auto it=s.find(v); if(it!=s.end()) {s.erase(it);} }

  bool empty() { return s.empty(); } // DNS
  multiset<T, Compare> s;  // DNS private
 private:
};

void solve() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  a--; b--;
  vector<vector<int>> g(n);
  vector<ll> c(n);
  for(int i=0;i<n;i++) {
    int p; cin >> p >> c[i];
    if (p) {
      g[i].pb(p-1); g[p-1].pb(i);
    }
  }

  vector<ll> cost(n, -1);
  vector<int> d2s(n);
  vector<int> par(n);
  dfspre(g, a, -1, [&](int x,int pa) {
    if (pa>=0) {
      d2s[x]=d2s[pa]+1;
      if (d2s[x]<=m && c[x]!=0) cost[x]=c[x];
    } else {
      d2s[x] = 0;
      cost[x]=0;
    }
    par[x] = pa;
  });
  vector<int> path;
  int tb=b; while(tb!=-1) { path.pb(tb); tb=par[tb]; }
  reverse(all(path));

  vector<int> d2d(n);
  dfspre(g, b, -1, [&](int x,int pa) {
    if (pa>=0) d2d[x]=d2d[pa]+1;
    else d2d[x] = 0;
  });

  vector<int> drank(n, -1);
  PQ pq([&](int i, int j) { return cost[i] < cost[j]; });
  auto updcost = [&](int i) {
    if(pq.empty()) return;
    if(c[i]==0 && i!=b) return;
    if (cost[i] == -1 || cost[i] > cost[pq.top()]+c[i]) cost[i] = cost[pq.top()]+c[i];
  };
  auto updpq = [&](int i) {
    if (cost[i]<0) return;
    int d = d2d[i];
    if (drank[d]<0 || cost[drank[d]]>cost[i]) {
      if (drank[d]>=0) pq.remove(drank[d]);
      drank[d] = i;
      pq.insert(drank[d]);
    }
  };

  for(int i=0;i<path.size();i++) {
    int v = path[i];
    updcost(v);
    if (i==path.size()-1) break;
    int nxt = path[i+1];
    int out = d2d[v] + m;
    if (out<n && drank[out]>=0) {
      pq.remove(drank[out]);
      drank[out] = -1;
    }
    out--;
    for (int y : g[v]) if(y!=par[v] && y!=nxt) {
      dfs(g, y, v, [&](int x, int pa) { // pre
        updcost(x);
        if (out>=0 && out<n && drank[out]>=0) {
          pq.remove(drank[out]);
        }
        out--;
      },
      [&](int x, int pa) { // post
        out++;
        if (out>=0 && out<n && drank[out]>=0) {
          pq.insert(drank[out]);
        }
      });
    }

    updpq(v);
    for (int y : g[v]) if(y!=par[v] && y!=nxt) {
      dfspre(g, y, v, [&](int x, int pa) { // pre
        if (d2d[x] - d2d[v] <= m-1) {
          updpq(x);
        }
      });
    }
    //debug(i, pq.s);
    //debug(cost);
  }
  //debug(b);
  //debug(cost);
  if (cost[b] <0 ) cout << -1 <<endl;
  else cout << cost [b] - c[b] << endl;
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
