#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v;
    int n;
    cin>>n;

    for(int i = 0; i < n; i++) {
        int t;
        cin>>t;
        v.push_back(t);
    }

    int t;
    cin>>t;
    v.erase(v.begin() + t - 1);

    int t1;
    int t2;
    cin>>t1>>t2;
    v.erase(v.begin() + t1 - 1, v.begin() + t2 - 1);

    cout<<v.size()<<endl;
    for(int i = 0; i < v.size(); i++) {
        cout<<v[i]<<" ";
    }
    cout<<endl;

    return 0;
}
