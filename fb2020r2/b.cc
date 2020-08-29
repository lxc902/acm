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

double CC(ll x) {
  return x*(x-1)/2.0;
}

const int N = 8000+10;
void solve() {
  int n; double p; cin >>n >> p;
  double f[N][N];
  for(int i=0;i<N;i++) for(int j=0;j<N;j++) f[i][j]=0;
  f[1][1] = 0; f[1][0]=f[0][0] =0;
  f[2][1] = f[2][2] = 1.0;
  for(int i=3;i<=n;i++) for(int j=1;j<=i;j++) {
    double& ans=f[i][j];
    ans = 0;
    double no = 1 - (2.0/i);
    double ye = (2.0/i);
    ans+= no*CC(j-1)/CC(i-1)*( f[i-1][j-1] + 1 );
    ans+= no*CC(i-j)/CC(i-1)*( f[i-1][j] + 1 );
    double crs = 1 - CC(j-1)/CC(i-1) - CC(i-j)/CC(i-1);
    ans+= no*crs*p*( f[i-1][j-1] + 1 );
    ans+= no*crs*(1-p)*( f[i-1][j] + 1 );

    double low = 1.0*(j-1)/(i-1);
    double hig = 1.0*(i-j)/(i-1);
    ans+= ye*low*p*( f[i-1][j-1] + 1);
    ans+= ye*low*(1-p)*( 1 );
    ans+= ye*hig*p*( 1 );
    ans+= ye*hig*(1-p)*( f[i-1][j] + 1 );
  }
  for(int j=1;j<=n;j++) cout << setprecision(8) << fixed << f[n][j] << endl;
  //for(int j=1;j<=n;j++) printf("%.7f\n", f[n][j]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  for(int i=1;i<=t;i++) {
    cout<< "Case #"<<i<<":\n";
    solve();
  }
  return 0;
}
