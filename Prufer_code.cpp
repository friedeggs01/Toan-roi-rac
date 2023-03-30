#include<bits/stdc++.h>
using namespace std;
bool check(set<int> s[1001], int n){
    int c=0;
    for(int i=1; i<=n; i++){
        if(s[i].size() != 0){
            c++;
        }
    }
    if(c>1) return true;
    if(s[0].size()>1){
        return true;
    }
    return false;
}
int main() {
    int n, a, b;
    cin >> n;
    set<int> s[1001];
    for(int i=0; i<n-1; i++){
        cin >> a >> b;
       s[a].insert(b);
       s[b].insert(a);
    }
    while(check(s, n)){
        for(int j=1; j<=n; j++){
            if(s[j].size() == 1){
                auto c = s[j].begin();
                cout << *c << " ";
                s[j].erase(*c);
                s[*c].erase(j);
            }
        }
    }
}