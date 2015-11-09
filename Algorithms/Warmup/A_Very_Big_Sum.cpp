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
    long long sum = 0;
    long long t;
    for(int i = 0; i < N; i++) {
        cin>>t;
        sum += t;
    }
    cout<<sum<<endl;
    
    return 0;
}
