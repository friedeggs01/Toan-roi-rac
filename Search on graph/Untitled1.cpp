#include<bits/stdc++.h>
using namespace std;
vector<string> vs;
vector< vector< int > > v;
vector<int> p, r;
int ans = 0;

bool check(string x, string y){
	int cnt = 0;
	for(int i = 0; i < 5; i++){
		if(x[i] != y[i]) cnt++;
		if(cnt > 1) return false;
	}
	if(cnt == 1) return true;
	return false;
}

void transfer(){
	bool f;
	v.resize(vs.size());
	for(int i = 0; i < vs.size(); i++){
		p.push_back(i);
		r.push_back(1);
		for(int j = i + 1; j < vs.size(); j++){
			f = check(vs[i], vs[j]);
			if(f){
				v[i].push_back(j);
				v[j].push_back(i);
			}
		}
	}
}

int find(int x){
	if(p[x] == x) return x;
	p[x] = find(p[x]);
	return p[x];
}

void Union(int x, int y){
	int px = find(x), py = find(y);
	if(px == py) return;
	if(r[px] < r[py]){
		p[px] = py;
	}
	else if(r[px] > r[py]){
		p[py] = px;
	}
	else{
		p[py] = px;
		r[px]++;
	}
}

void timSoTPLT(){
	for(int i = 0; i < vs.size(); i++){
		for(int j = 0; j < v[i].size(); j++){
			Union(i, v[i][j]);
		}
	}
	for(int i = 0; i < vs.size(); i++){
		if(p[i] == i) ans++;
	}
	cout << ans;
}

void bfs(int root, int pos){
	int vi[vs.size()], f[vs.size()];
	for(int i = 0; i < vs.size(); i++){
		vi[i] = 0;
		f[i] = -1;
	}
	int x;
	queue<int> q;
	q.push(root);
	vi[root] = 1;
	while(!q.empty()){
		x = q.front();
		q.pop();
		if(x == pos) break;
		for(int i = 0; i < v[x].size(); i++){
			if(!vi[v[x][i]]){
				f[v[x][i]] = x;
				vi[v[x][i]] = 1;
				q.push(v[x][i]);
			}
		}
	}
	vector<int> path;
	path.push_back(pos);
	x = f[pos];
	while(x != -1){
		path.push_back(x);
		x = f[x];
	}
	for(int i = path.size() - 1; i >= 0; i--) cout << vs[path[i]] << ' ';
}

void timDNN(string x, string y){
	int posx, posy;
	for(int i = 0; i < vs.size(); i++){
		if(vs[i] == x) posx = i;
		if(vs[i] == y) posy = i;
	}
	bfs(posx, posy);
}

signed main(){
//	freopen("in.txt","r",stdin);
//	freopen(".out","w",stdout);
//	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string s, s1;
	while(cin >> s){
		if(s == "1") break;
		vs.push_back(s);
	}
	transfer();
	timSoTPLT();
	cin >> s >> s1;
	timDNN(s, s1);
	//bfs(0, 3);
}

