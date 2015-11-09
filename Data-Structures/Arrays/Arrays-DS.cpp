#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin>>N;
    vector<int> v;
    for(int i = 0; i < N; i++) {
        int t;
        cin>>t;
        v.push_back(t);
    }

    for(int i = N - 1; i >= 0; i--) {
        cout<<v[i]<<" ";
    }
    cout<<endl;

    return 0;
}
