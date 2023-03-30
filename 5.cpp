#include <bits/stdc++.h>
using namespace std;

#define UNIQUE(S) S.erase(unique(S.begin(), S.end()), S.end())
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define MAXN 500001

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const ll mod = 998244353; // 1e9 + 7;
const ll oo = (ll)(1e18) + 7;
const double eps = 1e-3;
const double eps_cmp = 1e-7;

ll dr[] = {1, 1, 0, -1, -1, -1, 0, 1}; // S,SE,E,NE,N,NW,W,SW neighbors
ll dc[] = {0, 1, 1, 1, 0, -1, -1, -1}; // trick to explore an implicit 2D grid graph
bool valid(ll i, ll j, ll n, ll m) { return i >= 0 && i < n && j >= 0 && j < m; }

bool isEqual(double a, double b)
{
    return (abs(a - b) < eps_cmp);
}

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &x) { return out << x.f << ' ' << x.s; }
template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &x) { return in >> x.f >> x.s; }

template <typename T>
istream &operator>>(istream &in, vector<T> &a)
{
    for (auto &x : a)
        in >> x;
    return in;
};
template <typename T>
ostream &operator<<(ostream &out, vector<T> &a)
{
    for (auto &x : a)
        out << x << ' ';
    return out;
};

int adj[101][101];
int min_path_length[101][101];
bool visited[10001];
int n, m;

void Floyd_Warshall()
{
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                min_path_length[i][j] = min(min_path_length[i][j], min_path_length[i][k] + min_path_length[k][j]);
            }
        }
    }
}

queue<int> q;
vector<int> d(10001), p(10001);
map<int, int> mm;

void bfs(int s)
{
    q.push(s);
    visited[s] = true;
    p[s] = -1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int i = 0; i < n; ++i)
        {
            int u = i * 100 + v - ((v / 100)*100);
            if (mm[u] == 1 && adj[v / 100][i] == 1 && !visited[u])
            {
                visited[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
            int uu = i + v - (v % 100);
            if (mm[uu] == 1 && adj[v % 100][i] == 1 && !visited[uu])
            {
                visited[uu] = true;
                q.push(uu);
                d[uu] = d[v] + 1;
                p[uu] = v;
            }
        }
    }
}

void shortestPath(int u)
{
    if (!visited[u])
    {
        cout << "No path!";
    }
    else
    {
        vector<int> path;
        for (int v = u; v != -1; v = p[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        cout << "Path: ";
        for (int v : path)
        {
            cout << v / 100 << ' ' << v % 100 << ' ' << min_path_length[v / 100][v % 100] << '\n';
        }
    }
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
                min_path_length[i][j] = 1000000000;
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        int point1, point2, weight;
        cin >> point1 >> point2 >> weight;
        min_path_length[point1][point2] = min_path_length[point2][point1] = weight;
        adj[point1][point2] = adj[point2][point1] = 1;
    }
    Floyd_Warshall();
    int a, b, c, d, r;
    cin >> a >> b >> c >> d >> r;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i != j && min_path_length[i][j] >= r && min_path_length[i][j] < 1000000000)
                mm[i * 100 + j] = 1;
        }
    }
    bfs(a * 100 + b);
    shortestPath(c * 100 + d);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    setIO("A");
    solve();
    return 0;
}
