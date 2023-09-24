#include <bits/stdc++.h>
using namespace std;

#define fastOI ios_base::sync_with_stdio(false); \
cin.tie(nullptr);
#define ll long long

//stole this from ScarletS
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

/*
int main(){
    int n = 4
    disjoint_set_union dsu(n);
    dsu.unite(n-1,n-2);
    cout<<dsu.sz[dsu.find_set(n-2)]<<"\n";
    for(auto k : dsu.p)cout<<k<<" ";
    cout<<"\n";
    for(auto k : dsu.sz)cout<<k<<" ";
}


Output should be -
2
0 1 3 3 4 
1 1 1 2 1
*/