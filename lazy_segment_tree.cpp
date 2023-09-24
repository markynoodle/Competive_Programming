#include <bits/stdc++.h>
using namespace std;
#define fastOI ios_base::sync_with_stdio(false); \
cin.tie(nullptr);

#define ll long long

int next_power_of_2(int n){ // segtree should have size 2 * next_power_of_2(n)
    return 1<<(__lg(n-1) + 1);
}

struct ToDo{
    bool need_update;
    int x; // val;
};

//this is an edit query and max element in range query lazy segtree

struct lazy_segment_tree{
    vector<int> tree;
    vector<ToDo> lazy;
    lazy_segment_tree(int n) : tree(){
        tree.assign(n, 0);
        lazy.assign(n, {false, 0});
    }

    void push(int pos){//this needs a makeover by each type of update type
        if(lazy[pos].need_update){
            lazy[pos].need_update = false;
            lazy[pos*2] = {true, lazy[pos].x};
            lazy[pos*2 + 1] = {true, lazy[pos].x};
            tree[pos*2] = lazy[pos].x;
            tree[pos*2 + 1] = lazy[pos].x; // change this based on wheather or not disructive
        }
    }

    void update_range(int l, int r, int pos, int ul, int ur, int x){
        if(r <= ul || ur <= l)return;
        if(l + 1 == r){
            tree[pos] = x; //if updates disruptive
            return;
        }
        if(ul <= l && r <= ur){ //percrastination
            tree[pos] = x;
            lazy[pos] = {true, x}; //if updates disruptive
            return;
        }
        push(pos);
        int m = l + (r - l)/2;
        update_range(l, m, pos*2, ul, ur, x);
        update_range(m, r, pos*2 + 1, ul, ur, x);
        tree[pos] = max(tree[pos*2], tree[pos*2 + 1]); // dont forget to update this
    }

    int query_range(int l, int r, int pos, int ql, int qr){
        if(r <= ql || qr <= l)return 0; // this needs to be a neutral value
        if(ql <= l && r <= qr)return tree[pos];//if addition add some extra stuff here
        push(pos);
        int m = l + (r - l)/2;
        return max(query_range(l, m, pos*2, ql, qr), query_range(m, r, pos*2 + 1, ql, qr)); // dont forget to update this
    }
};

int main(){
    int n;
    cin>>n;
    int npo2 = next_power_of_2(n);
    lazy_segment_tree lsg(npo2 * 2);
    int m;
    int a, b, c, d;
    cin>>m;
    for(int i =0 ; i<m; i++){
        cin>>a; //a = 1 if update a = 2 if query
        if(a == 1){
            cin>>b>>c>>d; //b = ul c = ur d = x;
            lsg.update_range(0, npo2, 1, b, c, d);
        }
        if(a == 2){
            cin>>b>>c; // b = ql c = qr
            cout<<lsg.query_range(0, npo2, 1, b, c)<<"\n";
        }
    }
}

/*
Testcase 1:
Input:
6
12
1 0 1 2
1 3 4 3
1 4 5 2
1 5 6 165
1 2 3 5
1 2 3 0
2 0 6
2 1 5
2 2 3
2 4 4
2 0 4
2 2 6
Output:
165
3
0
0
3
165

Tescase 2:
Input:
7
10
1 1 6 5
1 3 7 4
2 3 5
2 0 3
1 3 4 2
1 0 3 6
2 1 6
2 3 5
2 3 4
2 4 7

Output:
4
5
6
4
2
4
*/
