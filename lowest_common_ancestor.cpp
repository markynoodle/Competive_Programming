#include <bits/stdc++.h>
using namespace std;
#define fastOI ios_base::sync_with_stdio(false); \
cin.tie(nullptr);
 
#define ll long long

vector<vector<int>> adj;
vector<vector<int>> ancestors;
vector<int> pre;
vector<int> post;
vector<int> dist; //not used here but you can find dist from root

int timer = 0;
int lg = 20; // change this log based on N. Here n <= 2^20

void dfs(int u, int v){
    dist[u] = dist[v] + 1;
    pre[u] = timer;
    timer++;
    ancestors[u][0] = v;
    for(int i = 1; i<lg; i++){
        ancestors[u][i] = ancestors[ancestors[u][i-1]][i-1];
    }
    for(auto k : adj[u]){
        if(k == v)continue;
        dfs(k, u);
    }
    post[u] = timer;
    timer++;
}

bool isancestor(int a, int b){ // a is ancestor fo b
    return pre[a] <= pre[b] && post[a] >= post[b];
}

int lca(int a, int b){
    if(isancestor(a, b))return a;
    if(isancestor(b, a))return b;
    for(int i = lg-1; i>=0; i--){
        if(!isancestor(ancestors[a][i], b)) a = ancestors[a][i];
    }
    return ancestors[a][0];
}

int main(){
    int n;
    cin>>n;
    adj.assign(n, vector<int>());
    ancestors.assign(n, vector<int>(lg, 0));
    pre.assign(n, -1);
    post.assign(n, -1);
    dist.assign(n, -1);
    int x, y;
    for(int i =0; i<n-1; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(0, 0);

    int q;
    cin>>q;
    for(int i =0; i<q; i++){
        cin>>x>>y;
        cout<<lca(x, y)<<"\n";
    }
}

/*
Testcase 1:
Intput:
8
0 1
1 2
1 3
3 4
3 5
0 6
6 7
7
2 7
2 4
4 5
6 7
5 0
0 0
3 3
Output:
0
1
3
6
0
0
3
*/