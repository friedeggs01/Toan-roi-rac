#include<bits/stdc++.h>
using namespace std;

vector<string> colorCodes = {"aliceblue","antiquewhite","aqua","aquamarine","azure","beige","bisque","black","blanchedalmond","blue","blueviolet","brown","burlywood","cadetblue","chartreuse","chocolate","coral","cornflowerblue","cornsilk","crimson","cyan","darkblue","darkcyan","darkgoldenrod","darkgray","darkgreen","darkgrey","darkkhaki","darkmagenta","darkolivegreen","darkorange","darkorchid","darkred","darksalmon","darkseagreen","darkslateblue","darkslategray","darkslategrey","darkturquoise","darkviolet","deeppink","deepskyblue","dimgray","dimgrey","dodgerblue","firebrick","floralwhite","forestgreen","fuchsia","gainsboro","ghostwhite","gold","goldenrod","gray","grey","green","greenyellow","honeydew","hotpink","indianred","indigo","ivory","khaki","lavender","lavenderblush","lawngreen","lemonchiffon","lightblue","lightcoral","lightcyan","lightgoldenrodyellow","lightgray","lightgreen","lightgrey","lightpink","lightsalmon","lightseagreen","lightskyblue","lightslategray","lightslategrey","lightsteelblue","lightyellow","lime","limegreen","linen","magenta","maroon","mediumaquamarine","mediumblue","mediumorchid","mediumpurple","mediumseagreen","mediumslateblue","mediumspringgreen","mediumturquoise","mediumvioletred","midnightblue","mintcream","mistyrose","moccasin","navajowhite","navy","oldlace","olive","olivedrab","orange","orangered","orchid","palegoldenrod","palegreen","paleturquoise","palevioletred","papayawhip","peachpuff","peru","pink","plum","powderblue","purple","red","rosybrown","royalblue","saddlebrown","salmon","sandybrown","seagreen","seashell","sienna","silver","skyblue","slateblue","slategray","slategrey","snow","springgreen","steelblue","tan","teal","thistle","tomato","turquoise","violet","wheat","white","whitesmoke","yellow","yellowgreen"};
string funcGetColorFromNum(int x){
    string r;
    int sz=colorCodes.size();
    do{
        r.append(colorCodes[x%sz]);
        x/=sz;
    }while(x>0);
    return r;
} 

class Graph
{
    int V;   
    list<int> *adj;    
public:
    Graph(int V)   { this->V = V; adj = new list<int>[V+1]; }
    ~Graph()       { delete [] adj; }
  
    void addEdge(int v, int w);
    void greedyColoring();
};
  
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
  
void Graph::greedyColoring()
{
    int result[V];
  
    result[1]  = 0;
    for (int u = 2; u < V+1; u++)
        result[u] = -1;

    bool available[V];
    for (int cr = 0; cr < V; cr++)
        available[cr] = false;

    for (int u = 2; u<V+1; u++)
    {

        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = true;
    
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr] == false)
                break;
  
        result[u] = cr;
  
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = false;
    }
  
    for (int u = 1; u < V+1; u++)
        cout << u << " [fillcolor=" << funcGetColorFromNum(result[u]) << ", style=filled] ; \n";
}

int main()
{
    int n, m, a, b;
    cin >> n >> m;
    Graph g(n);
    int p[m+1], q[m+1];
    for(int i=0; i<m; i++){
        cin >> a >> b;
        p[i] = a;
        q[i] = b;
        g.addEdge(a, b);
    }
    cout << "graph dothi \n" << "{ \n";
    g.greedyColoring();
    for(int i=0; i<m; i++){
        cout << p[i] << " -- " << q[i] << ";" << "\n";
    }
    cout << "}";
}