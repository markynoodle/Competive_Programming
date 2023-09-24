#include <bits/stdc++.h>
using namespace std;


#define ll long long

int next_power_of_2(int n){ // segtree should have size 2 * next_power_of_2(n)
    return 1<<(__lg(n-1) + 1);
}


struct segment_tree{ // dont forget to use ll if needed
    vector<int> tree; 
    segment_tree(int n) : tree(){ // let n be the size of the segtree not just the number of elements
        tree.assign(n, 0); 
    }

    void update(int l, int r, int pos, int i, int x){ // use l = 0; r = next_power_of_2(n); pos = 1;
        if(l >  i || r <= i)return;
        if(l == i && l + 1 == r){
            tree[pos] = x;  // modify this if edit/adding... (here its edit)
            return;
        }
        int m = l + (r - l)/2;
        update(l, m, pos * 2, i, x);
        update(m, r, pos* 2 + 1, i, x);
        tree[pos] = tree[pos*2] + tree[pos * 2 + 1]; // modify this based on segtree (here its sum of segment)
        return;
    }

    int query(int l, int r, int pos, int ql , int qr){ // use l = 0; r = next_power_of_2(n); pos = 1;
        if(l >= qr || r <= ql)return 0; //return a neutral value
        if(ql <= l && r <= qr)return tree[pos]; // return the whole segment
        int m = l + (r - l)/2;
        return query(l, m, pos*2, ql, qr) + query(m, r, pos*2 + 1, ql, qr); //edit this base on segtree operation (here sum of segment)
    }
};



int main(){
    int n;
    cin>>n;
    int q;
    cin>>q;
    int npo2 = next_power_of_2(n);
    segment_tree segtree(npo2*2);
    int x, y;
    for(int i =0; i<q; i++){
        cin>>x>>y; //x = index, y = the new value
        segtree.update(0, npo2, 1, x, y);
    }
    cin>>q;
    //for(auto k : segtree.tree)cout<<k<<" ";
    //cout<<"\n";
    for(int i = 0; i<q; i++){
        cin>>x>>y; //x = ql, y = qr in interval [x, y)
        cout<<segtree.query(0, npo2, 1, x, y)<<"\n";
    }
}
/*
For input 
6
6
0 2
3 3
4 2
5 165
2 5
2 0
6
0 6
1 5
2 3
4 4
0 4
2 6

Output should be
172
5
0
0
5
170
*/