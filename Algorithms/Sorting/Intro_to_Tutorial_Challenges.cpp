#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int V;
    int n;
    cin>>V>>n;
    for(int i = 0; i < n; i++) {
        int t;
        cin>>t;
        if(t == V) {
            cout<<i<<endl;
            break;
        }
    }

    return 0;
}
