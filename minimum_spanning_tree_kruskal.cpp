#include <bits/stdc++.h>
using namespace std;

#define fastOI ios_base::sync_with_stdio(false); \
cin.tie(nullptr);
#define ll long long

struct edge{
    int cost;
    int u;
    int v;
};

auto cmp = [](edge a, edge b){return a.cost > b.cost;}; //return true if the first argument should be more to the left when sorted "smaller"

priority_queue<edge, vector<edge>, decltype(cmp)> pq(cmp);

struct disjoint_set_union {
    vector<int> p;
    vector<int> sz;
    disjoint_set_union(int n) : p(), sz(){
        p.assign(n+1, 0);
        sz.assign(n+1, 1);
        iota(p.begin(), p.end(), 0);

    }

    int find_set(int i){
        if(i == p[i])return i;
        return p[i] = find_set(p[i]);
    }
    
    void unite(int u, int v){
        u = find_set(u);
        v = find_set(v);
        if(u != v){
            if(sz[u] < sz[v])swap(u, v);
            p[v] = u;
            sz[u] += sz[v];
        }
    }

    bool connected(int u, int v){
        return find_set(u) == find_set(v);
    }
};
//if the graph is not connected then it will create multiple MSTs
int main(){
    int n;
    cin>>n;
    disjoint_set_union dsu(n);
    int m;
    cin>>m;
    int x, y, z;
    for(int i =0; i<m; i++){
        cin>>x>>y>>z;
        pq.push({x, y, z});
    }
    ll cost = 0;
    while(!pq.empty()){
        edge cur = pq.top();
        pq.pop();
        if(dsu.connected(cur.u, cur.v))continue;
        cost+=cur.cost;
        dsu.unite(cur.u, cur.v);
    }
    cout<<cost<<"\n";
}

/*
Tescase 1:
Input:
5
5
10 0 1
2 0 2
3 3 2
10 4 3
1 1 3
Output:
16

Testcase 2:
Input:
5
10
10 0 1
6 1 2
7 2 3
8 3 4
9 4 0
2 0 2
1 2 4
4 3 0
3 1 4
5 3 1
Output:
10
*/