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

    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++) {
        cout<<v[i]<<" ";
    }
    cout<<endl;

    return 0;
}
