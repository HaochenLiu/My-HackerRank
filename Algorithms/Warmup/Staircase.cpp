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
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N - 1 - i; j++) {
            cout<<" ";
        }
        for(int j = 0; j <= i; j++) {
            cout<<"#";
        }
        cout<<endl;
    }
    return 0;
}
