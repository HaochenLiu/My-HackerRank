#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int c;
    while(~(c = getchar())) {
        putchar(c == 32 ? 10 : c);
    }
    
    return 0;
}
