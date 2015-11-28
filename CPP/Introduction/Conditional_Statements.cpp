#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    vector<string> v = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int n;
    cin>>n;
    if(n > 9) {
        cout<<"Greater than 9"<<endl;
    } else {
        cout<<v[n]<<endl;
    }
    
    return 0;
}
