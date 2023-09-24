#include <bits/stdc++.h>
using namespace std;


#define ll long long

vector<vector<int>> adj;
vector<int> preorder;
vector<int> min_back;
int timer = 0;
int bridges = 0;
set<int> articulation_points;
void dfs(int u, int v){
    preorder[u] = min_back[u] = timer;
    timer++;
    int children = 0;
    for(auto k : adj[u]){
        if(k == v)continue;
        if(preorder[k] != -1){
            min_back[u] = min(min_back[u],preorder[k]);
            continue;
        }
        children++;
        dfs(k, u);
        min_back[u] = min(min_back[u], min_back[k]);


        if(min_back[k] > preorder[u])bridges++;
        if(min_back[k] >= preorder[u] && u != v){
            articulation_points.insert(u);
        }
    }
    if(u == v && children > 1)articulation_points.insert(u);
    return;
}   




int main(){
    int n;
    cin>>n;
    int m;
    cin>>m;
    adj.resize(n, vector<int>());
    preorder.resize(n, -1);
    min_back.assign(n, -1);
    int x, y;
    for(int i =0; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for(int i =0; i<n; i++){
        if(preorder[i] != -1)continue;
        dfs(i, i);
    }
    cout<<articulation_points.size()<<" "<<bridges<<"\n";
}

/*
testcase 1:
Input:
6 7
0 1
0 2
1 2
2 3
2 4
3 4
4 5
Output:
2 1

Testcase 2:
Input:
5 5
0 1
1 2
2 3
3 4
4 0
Output:
0 0

Tescase 3:
7 6
0 1
0 2
0 3
2 5
5 4
4 6
Output:
4 6

*/