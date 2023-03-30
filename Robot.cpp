#include<bits/stdc++.h>
using namespace std;


int min_path[101][101];
int adj[101][101];
int n, m;
bool visited[1001];
void Floyd_Warshall(){
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                min_path[i][j] = min(min_path[i][j], min_path[i][k]+min_path[j][k]);
            }
        }
    }
}
queue<int> q;
vector<int> d(10001), p(10001);
map<int, int> mm;
void bfs(int s){
    q.push(s);
    visited[s] = true;
    p[s] = -1;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int i=0; i<n; i++){
            int u = i*100 + v - ((v/100)*100);
            if(mm[u] == 1 && adj[v/100][i] == 1 && !visited[u]){
                visited[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
            int uu = i + v - (v%100);
            if(mm[uu]==1 && adj[v%100][i]==1 && !visited[uu]){
                visited[uu] = true;
                q.push(uu);
                d[uu] = d[v] + 1;
                p[uu] = v;
            }
        }
    }
}
void shortestPath(int u){
    if(!visited[u]){
        cout << "Không thể!";
    } else {
        vector<int> path;
        for(int v = u; v!= -1; v = p[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        cout << "Lịch di chuyển" << " " << "khoảng cách" << '\n';
        for(int v: path){
            cout << v / 100 << ' ' << v % 100 << "                     " << min_path[v / 100][v % 100] << '\n';
        }
    }
}
void solve(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (i!=j){
                min_path[i][j] = 1e9;
            } else {
                min_path[i][j] = 0;
            }
        }
    }
    for(int i=0; i<m; i++){
        int x, y, w;
        cin >> x >> y >> w;
        min_path[x][y] = min_path[y][x] = w;
        adj[x][y] = adj[y][x] = 1;
    }
    Floyd_Warshall();
    int a, b, c, d, r;
    cin >> a >> b >> c >> d >> r;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i!=j && min_path[i][j] > r && min_path[i][j] < 1e9)
                mm[i*100 + j] = 1;
        }
    }
    bfs(a*100 + b);
    shortestPath(c*100 + d);
}
int main() {
    solve();
}