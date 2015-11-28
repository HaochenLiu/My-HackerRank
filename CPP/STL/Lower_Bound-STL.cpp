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

    cin>>n;
    for(int i = 0; i < n; i++) {
        int t;
        cin>>t;
        auto it = lower_bound(v.begin(), v.end(), t);
        if(*it == t) {
            cout<<"Yes ";
        } else {
            cout<<"No ";
        }
        cout<<it - v.begin() + 1<<endl;
    }

    return 0;
}
