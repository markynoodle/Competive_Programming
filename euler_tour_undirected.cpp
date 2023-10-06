#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fastIO ios_base::sync_with_stdio(false);\
cin.tie(nullptr);

vector<int> find_euler_tour(vector<vector<pair<int,int>>> & adj, int n, int m){
    vector<int> curcuit;
    vector<int> used(m, 0);
    vector<int> path;
    path.push_back(1);
    while(!path.empty()){
        int last = path.back();
        while(!adj[last].empty() && used[adj[last].back().second] == 1)adj[last].pop_back();
        
        if(adj[last].empty()){
            curcuit.push_back(last);
            path.pop_back();
        }
        else{
            used[adj[last].back().second] = 1;
            path.push_back(adj[last].back().first);
            adj[last].pop_back();
        }
    }
    return curcuit;   
}

int main(){
    fastIO
    int n;
    cin>>n;
    int m;
    cin>>m;
    vector<vector<pair<int,int>>> adj(n+1, vector<pair<int,int>>());
    int x, y;
    vector<int> cnt(n+1, 0);
    for(int i = 0; i<m; i++){
        cin>>x>>y;
        adj[x].push_back({y, i});
        adj[y].push_back({x, i});
        cnt[x]++;
        cnt[y]++;
    }
    bool pos = true;
    for(auto k : cnt){
        if(k % 2 == 1)pos = false;
    }
    if(!pos){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }
    vector<int> sol = find_euler_tour(adj, n, m);
    if(sol.size() != m+1){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }
    for(auto k : sol)cout<<k<<" ";
    cout<<"\n";

}


/*
Input:
6 8
1 2
1 3
2 3
2 4
2 6
3 5
3 6
4 5
Output:
1 2 3 5 4 2 6 3 1

Input:
10 16
9 10
8 6
8 5
1 7
2 8
3 8
3 1
6 3
10 3
8 9
3 5
10 2
5 9
7 8
9 3
5 10
Output:
1 7 8 6 3 8 5 3 10 9 8 2 10 5 9 3 1
*/