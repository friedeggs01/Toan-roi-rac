#include <bits/stdc++.h>
using namespace std;

map<int, string> mpp;
map<string, int> checkIdMap;
vector<int> adj[10001];
bool visited[10001] = {0};
queue<int> q;
int p[10001];

void initGraph()
{
    for (int i = 1; i <= 5757; ++i)
    {
        string s;
        cin >> s;
        mpp[i] = s;
        checkIdMap[s] = i;
    }
    for (int i = 1; i <= 5756; ++i)
    {
        for (int j = i + 1; j <= 5757; ++j)
        {
            string s1 = mpp[i], s2 = mpp[j];
            int diff_num = 0;
            for (int k = 0; k < s1.size(); ++k)
            {
                if (s1[k] != s2[k])
                    diff_num++;
            }
            if (diff_num == 1)
            {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
}

void bfs(int s)
{
    while (!q.empty())
        q.pop();
    q.push(s);
    visited[s] = true;
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
            }
        }
    }
}

void countConnectedComponents()
{
    memset(visited, false, sizeof(visited));
    int cnt = 0;
    for (int i = 1; i <= 5757; ++i)
    {
        if (!visited[i])
        {
            bfs(i);
            cnt++;
        }
    }
    cout << cnt << '\n';
}

void bfs1(int s)
{
    while (!q.empty())
        q.pop();
    memset(p, 0, sizeof(p));
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
    bfs1(uu);
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
    initGraph();
    countConnectedComponents();
    shortestPathBetween("words", "graph");
    return 0;
}
