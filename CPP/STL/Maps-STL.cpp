#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int n;
    cin>>n;
    map<string, int> m;
    for(int i = 0; i < n; i++) {
        int y;
        string s;
        int x;

        cin>>y;
        if(y == 1) {
            cin>>s>>x;
        } else {
            cin>>s;
        }

        if(y == 1) {
            m[s] += x;
        } else if(y == 2) {
            m.erase(s);
        } else {
            cout<<m[s]<<endl;
        }
    }

    return 0;
}
