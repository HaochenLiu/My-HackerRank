#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    string s;
    cin>>s;
    for(int i = 0; i < s.size(); i++) {
        cout<<char(((s[i] - '0') + 1) % 10 + '0');
    }
    cout<<endl;

    return 0;
}
