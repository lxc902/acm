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
#define pb push_back
#define all(x) x.begin(), x.end()
// #include <bits/stdc++.h>

using namespace std;


// Min Cost Max Flow.
template <typename T, typename C>
class mcmf {
 public:
  static constexpr T eps = (T) 1e-9;
 
  struct edge {
    int from;
    int to;
    T c;
    T f;
    C cost;
  };
 
  vector<vector<int>> g;
  vector<edge> edges;
  vector<C> d;
  vector<int> q;
  vector<bool> in_queue;
  vector<int> pe;
  int n;
  int st, fin;
  T flow;
  C cost;
 
  mcmf(int _n, int _st, int _fin) : n(_n), st(_st), fin(_fin) {
    assert(0 <= st && st < n && 0 <= fin && fin < n && st != fin);
    g.resize(n);
    d.resize(n);
    in_queue.resize(n);
    pe.resize(n);
    flow = 0;
    cost = 0;
  }
 
  void clear_flow() {
    for (const edge &e : edges) {
      e.f = 0;
    }
    flow = 0;
  }
   
  void add(int from, int to, T forward_cap, T backward_cap, C cost) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    g[from].push_back((int) edges.size());
    edges.push_back({from, to, forward_cap, 0, cost});
    g[to].push_back((int) edges.size());
    edges.push_back({to, from, backward_cap, 0, -cost});
  }
 
  bool expath() {
    fill(d.begin(), d.end(), numeric_limits<C>::max());
    q.clear();
    q.push_back(st);
    d[st] = 0;
    in_queue[st] = true;
    int beg = 0;
    bool found = false;
    while (beg < (int) q.size()) {
      int i = q[beg++];
      if (i == fin) {
        found = true;
      }
      in_queue[i] = false;
      for (int id : g[i]) {
        const edge &e = edges[id];
        if (e.c - e.f > eps && d[i] + e.cost < d[e.to]) {
          d[e.to] = d[i] + e.cost;
          pe[e.to] = id;
          if (!in_queue[e.to]) {
            q.push_back(e.to);
            in_queue[e.to] = true;
          }
        }
      }
    }
    if (found) {
      T push = numeric_limits<T>::max();
      int v = fin;
      while (v != st) {
        const edge &e = edges[pe[v]];
        push = min(push, e.c - e.f);
        v = e.from;
      }
      v = fin;
      while (v != st) {
        edge &e = edges[pe[v]];
        e.f += push;
        edge &back = edges[pe[v] ^ 1];
        back.f -= push;
        v = e.from;
      }
      flow += push;
      cost += push * d[fin];
    }
    return found;
  }
   
  pair<T, C> max_flow_min_cost() {
    while (expath()) {}
    return {flow, cost};
  }
};

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
    #define debug(...) cerr << "(" << __LINE__ << ": " \
        << #__VA_ARGS__ << "):  ", debug_out(__VA_ARGS__)
    #else
    #define debug(...) 42
    #endif
}

// DFS on tree. Usage: dfs(graph, root, pre-processing, post-processing);
namespace {
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
} // namespace

bool ok(const vector<vector<int>> & g, int n, int a, int b) {
  auto noop = [&](int x, int pa){}; // DNS

  vector<int> mxchild1(n, 0);
  vector<int> mxchild2(n, 0);
  vector<int> mxchild3(n, 0);
  auto get_mxchild = [&](int x,int pa){
    int& mx1=mxchild1[x];
    int& mx2=mxchild2[x];
    int& mx3=mxchild3[x];
    for(int y : g[x]) {
      if (y==pa) continue;
      int mxy=mxchild1[y] + 1;
      if (mxy > mx1) {
        mx3 = mx2;
        mx2 = mx1;
        mx1 = mxy;
      } else if (mxy > mx2) {
        mx3 = mx2;
        mx2 = mxy;
      } else if (mxy > mx3) {
        mx3 = mxy;
      }
    }
  };
  dfs(g, a, noop, get_mxchild);

  vector<int> par(n, 0);
  vector<int> mxup(n, 0);
  auto get_mxup = [&](int x,int pa){
    par[x]=pa;
    if (pa<0) return; // root
    int mxsib = (mxchild1[pa] == mxchild1[x]+1) ? mxchild2[pa] : mxchild1[pa];
    mxup[x] = max(mxup[pa], mxsib) + 1;
  };
  dfs(g, a, get_mxup, noop);

  { 
    debug(g);
    debug(mxchild1);
    debug(mxchild2);
    debug(mxchild3);
    debug(mxup);
    debug(par);
  }

  int k=1; int tb=b;
  vector<int> path;
  path.pb(b);
  while(tb != a) {
    tb=par[tb];
    k++;
    path.pb(tb);
  }
  std::reverse(all(path));
  debug(path);

  auto ispivot = [&](int x) ->bool{
    int cnt = 0;
    cnt += mxchild1[x]>=(k-1);
    cnt += mxchild2[x]>=(k-1);
    cnt += mxchild3[x]>=(k-1);
    cnt += mxup[x]>=(k-1);
    return (cnt >=3);
  };
  bool has_pivot = false;
  vector<bool> pivot(n);
  for (int i=0;i<n;i++) {
    pivot[i]=ispivot(i);
    if (pivot[i]) { has_pivot = true; }
  }
  debug(pivot);

  int maxl=0; int minr=k-1;
  int curl=0; int curr=k-1;
  int lastl = curl; int lastr = curr;
  while (maxl+1 < minr) {
    int vl=path[curl];
    int mx = mxup[vl];
    mx = max(mx, ((mxchild1[vl] == mxchild1[path[curl+1]]+1) ? mxchild2[vl] : mxchild1[vl]));
    curl -= mx; curr -= mx;
    minr = curr;
    if (maxl+1 >= minr) break;
    assert(mxchild1[path[curr]] - mx >= 0);
    mx = mxchild1[path[curr]];
    curl += mx; curr += mx;
    maxl = curl;
    if (curl==lastl && curr==lastr) break;
    lastl = curl; lastr = curr;
  }
  if (maxl+1 >= minr) return has_pivot;

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while(t--) {
    int n,a,b;
    cin >> n >> a >> b;
    a--; b--;
    vector<vector<int>> g(n);
    for(int i=0;i<n-1;i++) {
      int u,v;
      cin>>u>>v;
      u--;v--;
      g[u].pb(v);
      g[v].pb(u);
    }
    cout << ( ok(g, n, a, b) ? "YES" : "NO" ) << endl;
  }
  return 0;
}
