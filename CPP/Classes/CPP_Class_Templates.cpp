template<typename T>
class AddElements{
private:
    T x;

public:
    AddElements(const T &_x):x(_x){}
    T add(const T &o){return x+o;}
    T concatenate(const T &o){return x+o;}
};
