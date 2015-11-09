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
    vector<vector<int>> matrix(N, vector<int>(N, 0));
    int sum1 = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin>>matrix[i][j];
        }
    }
    
    for(int i = 0; i < N; i++) {
        sum1 += matrix[i][i];
    }
    
    int sum2 = 0;
    for(int i = 0; i < N; i++) {
        sum2 += matrix[i][N - 1 - i];
    }

    cout<<abs(sum1 - sum2)<<endl;
    
    return 0;
}
