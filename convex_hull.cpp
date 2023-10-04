#include <bits/stdc++.h>
using namespace std;
#define fastOI ios_base::sync_with_stdio(false); \
cin.tie(nullptr);
 
#define ll long long
 
struct pt{
    ll x;
    ll y;
};
 
auto cmp =[](pt a, pt b){
    if(a.x == b.x)return a.y < b.y;
    return a.x < b.x;
};
 
ll crossproduct(pt a, pt b, pt c){
    a = {a.x - c.x, a.y - c.y};
    b = {b.x - c.x, b.y - c.y};
    return a.x * b.y - b.x * a.y;
}
 
int main(){
    int n;
    cin>>n;
    vector<pt> pts(n);
    ll x, y;
    for(int i =0; i<n; i++){
        cin>>x>>y;
        pts[i] = {x, y};
    }
    sort(pts.begin(), pts.end(), cmp);
    vector<pt> hull;
    int sz = 0;
    for(int i=0; i<n; i++){
        while(sz >= 2 && 0 > crossproduct(hull[sz-2], hull[sz-1], pts[i])){
            hull.pop_back();
            sz--;
        }
        hull.push_back(pts[i]);
        sz++;
    }
    hull.pop_back();
    sz--;
    reverse(pts.begin(), pts.end());
    for(int i =0 ;i<n; i++){
        while(sz >= 2 && 0 > crossproduct(hull[sz-2], hull[sz-1], pts[i])){
            hull.pop_back();
            sz--;
        }
        hull.push_back(pts[i]);
        sz++;
    }
    hull.pop_back();
    sz--;
    cout<<sz<<"\n";
    for(auto k : hull)cout<<k.x<<" "<<k.y<<"\n";
}
