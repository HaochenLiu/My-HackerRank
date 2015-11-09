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
    int pos = 0;
    int neg = 0;
    int zero = 0;
    for(int i = 0; i < N; i++) {
        int t;
        cin>>t;
        if(t > 0) {
            pos++;
        } else if(t < 0) {
            neg++;
        } else {
            zero++;
        }
    }
    
    printf("%.6f\n", (double)pos / (double)N);
    printf("%.6f\n", (double)neg / (double)N);
    printf("%.6f\n", (double)zero / (double)N);
    
    return 0;
}
