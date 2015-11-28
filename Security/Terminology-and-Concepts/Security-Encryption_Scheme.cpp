#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

long long fac(long long n) {
    if(n <= 1) return 1;
    return n * fac(n - 1);
}

int main() {
    long long n;
    cin>>n;
    cout<<fac(n)<<endl;

    return 0;
}
