
#include <deque>

class LRUCache{
public:
    deque<pair<int,int> >v;
    int cp;
    LRUCache(const int &x) {
        cp = x;
    }
    
    int get(int x){
        for(int i = 0; i < v.size(); i++) {
            if(v[i].first == x) {
                return v[i].second;
            }
        }
        return -1;
    }
    
    void set(int x,int y){
        int i = 0;

        for(; i < v.size(); i++) {
            if(v[i].first == x) { 
                v.erase(v.begin() + i);
                break;
            }
        }

        if(i == cp) {
            v.pop_back();
        }
        v.push_front(make_pair(x, y));
    }
};
