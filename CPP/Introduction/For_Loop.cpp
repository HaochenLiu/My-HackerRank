#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main() {
    vector<string> v = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    vector<string> e = {"even", "odd"};
    int a, b;
    cin>>a>>b;
    while(a <= b) {
        cout<<(a < 10 ? v[a] : e[a % 2])<<endl;
        a++;
    }
    
    return 0;
}
