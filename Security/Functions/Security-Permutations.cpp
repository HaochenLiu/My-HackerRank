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
    for(int i = 1; i <= n; i++) {
        int t;
        cin>>t;
        m[i] = t;
    }

    for(int i = 1; i <= n; i++) {
        cout<<m[m[i]]<<endl;
    }

    return 0;
}
