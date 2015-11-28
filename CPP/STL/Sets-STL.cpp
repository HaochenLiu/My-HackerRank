#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin>>n;
    set<int> s;
    for(int i = 0; i < n; i++) {
        int y;
        int x;
        cin>>y>>x;
        if(y == 1) {
            s.insert(x);
        } else if(y == 2) {
            s.erase(x);
        } else {
            if(s.count(x) > 0) {
                cout<<"Yes"<<endl;
            } else {
                cout<<"No"<<endl;
            }
        }
    }

    return 0;
}
