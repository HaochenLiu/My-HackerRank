#include <iostream>
#include <deque> 
#include <vector> 

using namespace std;

void maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> d;
    int n = nums.size();
    if(k < 1 || k > n) return;
    if(k == 1) return;

    for(int i = 0; i < k; i++) {
        while(!d.empty() && d.back() < nums[i]) {
            d.pop_back();
        }
        d.push_back(nums[i]);
    }
    cout<<d.front()<<" ";

    for(int i = k; i < n; i++) {
        if(d.front() == nums[i - k]) {
            d.pop_front();
        }
        while(!d.empty() && d.back() < nums[i]) {
            d.pop_back();
        }
        d.push_back(nums[i]);
        cout<<d.front()<<" ";
    }
    cout<<endl;

    return;
}

int main() {  
    int t;
    cin>>t;
    while(t > 0) {
        int n;
        int k;
        cin>>n>>k;
        vector<int> v;
        for(int i = 0; i < n; i++) {
            int t;
            cin>>t;
            v.push_back(t);
        }
        maxSlidingWindow(v, k);
        t--;
    }
    return 0;
}
