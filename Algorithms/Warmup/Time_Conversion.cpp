#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string time;
    cin>>time;
    if(time == "12:00:00AM") {
        cout<<"00:00:00"<<endl;
    } else if(time == "12:00:00PM") {
        cout<<"12:00:00"<<endl;
    } else if(time[8] == 'A') {
        if(time[0] == '1' && time[1] == '2') {
            time[0] = '0';
            time[1] = '0';
       }
        cout<<time.substr(0, 8)<<endl;
    } else {
        if(time[0] != '1' || time[1] != '2') {
            if(time[1] >= '8') {
                time[1] = time[1] - 8;
                time[0] = time[0] + 2;
            } else {
                time[1] = time[1] + 2;
                time[0] = time[0] + 1;
            }
        }
        cout<<time.substr(0, 8)<<endl;
    }
    return 0;
}
