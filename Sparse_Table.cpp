#include<bits/stdc++.h>
using namespace std;

#define all(x) x.begin(),x.end()
#define ll long long
#define fastOI ios_base::sync_with_stdio(false); cin.tie(nullptr);
auto cmp = [](int a, int b){return a > b;};
auto cmp1 = [](pair<ll,ll> a, pair<ll,ll> b){return a.second < b.second;};
ll mod = 1000000007;

ll lg = 20;

int main(){
    int n;
    cin>>n;
    int q;
    cin>>q;
    vector<ll> vals(n);
    vector<vector<ll>> sparse(n, vector<ll> (lg, 0));
    for(int i =0; i<n; i++){
        cin>>vals[i];
        sparse[i][0] = vals[i];
    }
    for(int j = 1; j<lg; j++){
        int d = (1<<j);
        for(int i = 0; i<n-d+1; i++){
            sparse[i][j] = sparse[i][j-1] + sparse[i + d/2][j-1];
        }
    }
    while(q--){
        ll sum =0;
        ll x, y;
        cin>>x>>y;
        x--;
        for(int i = lg-1; i>=0; i--){
            //cout<<x<<" "<<x + (1<<i)<<" ";
            if(x + (1<<i) <= y){
                sum += sparse[x][i];
                x += (1<<i);
            }
        }
        cout<<sum<<"\n";
    }
}


/*
Input:
8 4
3 2 4 5 1 1 5 3
2 4
5 6
1 8
3 3
Output:
11
2
24
4
*/
