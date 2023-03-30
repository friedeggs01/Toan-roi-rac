

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

vector<int> parent, sz;

void make_set(int v)
{
    parent[v] = v;
    sz[v] = 1;
}

void init_set(int n)
{
    parent.resize(n + 1);
    sz.resize(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        make_set(i);
    }
}

int find_set(int v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
}

int n = 5757;
int timeDfs = 0;
int scc = 0; // Num of strongly connected components
int low[10001], num[10001];
vector<int> adj[10001];
bool visited[10001] = {0};
vector<int> p(n+1);

stack<int> st;
queue<int> q;
map<int, string> mpp;
map<string, int> checkIdMap;

void initGraph()
{
    for (int i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;
        mpp[i] = s;
        checkIdMap[s] = i;
    }
    for (int i = 1; i < n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            string s1 = mpp[i], s2 = mpp[j];
            map<int, int> m1, m2;
            for (int k = 1; k < s1.size(); ++k)
            {
                m1[s1[k]]++;
            }
            for (int k = 0; k < s2.size(); ++k)
            {
                m2[s2[k]]++;
            }
            bool check = 1;
            for (auto k : m1)
            {
                if (k.second > m2[k.first])
                {
                    check = 0;
                    break;
                }
            }
            if (check)
            {
                adj[i].push_back(j);
            }
        }
    }
    for (int i = 1; i < n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            string s3 = mpp[j], s4 = mpp[i];
            map<int, int> m3, m4;
            for (int k = 1; k < s3.size(); ++k)
            {
                m3[s3[k]]++;
            }
            for (int k = 0; k < s4.size(); ++k)
            {
                m4[s4[k]]++;
            }
            bool check = 1;
            for (auto k : m3)
            {
                if (k.second > m4[k.first])
                {
                    check = 0;
                    break;
                }
            }
            if (check)
            {
                adj[j].push_back(i);
            }
        }
    }
}

void dfs(int u) // here, visited = ones which have been deleted in the stack
{
    num[u] = low[u] = ++timeDfs;
    st.push(u);
    for (int v : adj[u])
    {
        if (visited[v]) continue;
        if (!num[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], num[v]);
    }
    if (low[u] == num[u])
    {
        scc++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            visited[v] = true;
            union_sets(u, v);
        } while (v != u); // each stack deleting loop = a strongly connected component
    }
}

void sameStronglyConnectedComponent(string s)
{   
    int id = checkIdMap[s];
    for (int i = 1; i <= n; ++i)
    {
        if (find_set(id) == find_set(i))
        {
            cout << mpp[i] << ' ';
        }
    }
    cout << '\n';
}

void bfs(int s)
{
    q.push(s);
    visited[s] = true;
    p[s] = -1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int u : adj[v])
        {
            if (!visited[u])
            {
                visited[u] = true;
                q.push(u);
                p[u] = v;
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
            cout << mpp[v] << " ";
    }
}

void shortestPathBetween(string u, string v)
{
    memset(visited, false, sizeof(visited));
    int uu = checkIdMap[u], vv = checkIdMap[v];
    bfs(uu);
    shortestPath(vv);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    setIO("A");
    // int t;
    // cin >> t;
    // for (int i = 1; i <= t; ++i)
    init_set(n);
    initGraph();
    for (int i = 1; i <= n; ++i)
        if (!num[i])
            dfs(i);
    cout << scc << '\n';
    sameStronglyConnectedComponent("words");
    shortestPathBetween("words", "graph");
    return 0;
}
