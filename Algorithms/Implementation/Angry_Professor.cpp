#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T;
    cin>>T;
    while(T--) {
        int N;
        int K;
        cin>>N>>K;
        int cnt = 0;
        for(int i = 0; i < N; i++) {
            int t;
            cin>>t;
            if(t <= 0) {
                cnt++;
            }
        }
        if(cnt < K) {
            cout<<"YES"<<endl;
        } else {
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
