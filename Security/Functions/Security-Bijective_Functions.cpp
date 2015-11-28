#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<int> s;
    int n;
    cin>>n;
    for(int i = 0; i < n; i++) {
        int t;
        cin>>t;
        if(s.count(t) > 0) {
            cout<<"NO"<<endl;
            return 0;
        }
        s.insert(t);
    }
    cout<<"YES"<<endl;
    
    return 0;
}
