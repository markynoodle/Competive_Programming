#include<bits/stdc++.h>
using namespace std;

#define all(x) x.begin(),x.end()
#define ll long long
#define fastOI ios_base::sync_with_stdio(false); \
cin.tie(nullptr);
auto cmp = [](int a, int b){return a > b;};


struct fenwick_tree{
    vector<int> tree;
    int n;
    fenwick_tree(int nn) : tree(nn+1, 0){
        n = nn;
    };

    int get_prefix_sum(int k) { // sum of first k elements
        int r = tree[0];
        for(int i = k; i > 0; i -= i&-i) r += tree[i];
        return r;
    }
    void increment_at(int k, int x){ //edit tree[k];
        for(int i = k+1; i<=n; i += i&-i)tree[i]+=x;
        return;
    }    
};

int main(){
    int n;
    cin>>n;
    fenwick_tree fenwick(n);
    int q;
    cin>>q;
    int a, b, c;
    for(int i= 0; i<q; i++){
        cin>>a;
        if(a == 1){
            cin>>b>>c;
            fenwick.increment_at(b, c);
        }
        if(a == 2){
            cin>>b>>c; //0 indexed [b,c)
            cout<<fenwick.get_prefix_sum(c)-fenwick.get_prefix_sum(b)<<"\n";
        }
        //for(auto k : fenwick.tree)cout<<k<<" ";
        //cout<<"\n";
    }
}

/*
TestCase 1:
Input:
5
6
1 0 1
1 1 2
1 4 5
2 0 5
2 1 5
2 1 3


Output:
8
7
2
*/