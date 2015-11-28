class Student{
private:
    vector<int> a;

public:
    void Input() {
        for(int i = 0; i < 5; i++) {
            int x;
            scanf("%d", &x);
            a.push_back(x);
        }
    }
    
    int CalculateTotalScore(){
        int r = 0;
        for(int i = 0; i < a.size(); i++) {
            r += a[i];
        }
        return r;
    }
};
