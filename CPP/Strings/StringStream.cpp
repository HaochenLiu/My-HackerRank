#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    int c;
    for(;~(c = getchar());) {
        putchar(c == 44 ? 10 : c);
    }
    
    return 0;
}
