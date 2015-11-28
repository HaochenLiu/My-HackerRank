#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    cin>>n;
    unordered_map<int, int> m;
    unordered_map<int, int> minv;

    for(int i = 1; i <= n; i++) {
        int t;
        cin>>t;
        m[i] = t;
        minv[t] = i;
    }

    for(int i = 1; i <= n; i++) {
        if(m[i] != minv[i]) {
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;

    return 0;
}
