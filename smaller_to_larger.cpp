#include<bits/stdc++.h>
using namespace std;

#define all(x) x.begin(),x.end()
#define ll long long
#define fastOI ios_base::sync_with_stdio(false); \
cin.tie(nullptr);
auto cmp = [](int a, int b){return a > b;};

//smaller to larger trees;


struct graph{
    vector<vector<int>>adj;
    vector<int> color;
    vector<int> sol;

    graph(int n) : adj(n, vector<int>()), color(n, 0), sol(n, 0){}
    map<int,int> dfs(int u, int v){
        map<int,int> cur;
        cur[color[u]]++;
        for(auto k : adj[u]){
            if(k == v)continue;

            map<int,int> child = dfs(k, u);
            if(child.size() > cur.size())swap(child, cur);
            for(auto k : child){
                cur[k.first] += k.second;
            }
        }
        sol[u] = cur[color[u]];
        return cur;
    }
};

int main(){
    int n;
    cin>>n;
    graph g(n);

    int x, y;
    for(int i =0; i<n-1; i++){
        cin>>x>>y;
        g.adj[x].push_back(y);
        g.adj[y].push_back(x);
    }
    for(int i = 0; i<n; i++){
        cin>>g.color[i];
    }
    g.dfs(0,0);
    for(auto k : g.sol)cout<<k<<" ";
    cout<<"\n";
}

/*
Problem given rooted tree at 0 and a color for each node find the number of 
nodes that are the same color for each node and its subtree
Input:
9
0 1
0 2
0 3
1 4
1 5
3 6
3 7
3 8
0 1 0 2 0 1 2 0 1
Output:
4 2 1 2 1 1 1 1 1

*/
