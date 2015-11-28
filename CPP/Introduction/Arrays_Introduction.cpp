#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

int main() {
    stack<int> st;
    int n;
    cin>>n;
    for(int i = 0; i < n; i++) {
        int t;
        cin>>t;
        st.push(t);
    }
    while(!st.empty()) {
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<endl;

    return 0;
}
