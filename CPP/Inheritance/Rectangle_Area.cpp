class Rectangle {
protected:
    int width;
    int height;

public:
    void Input() {
        scanf("%d%d", &width, &height);
    }

    void Display() {
        printf("%d %d\n", width, height);
    }
};

class RectangleArea: public Rectangle {
public:
    void Display() {
        printf("%d\n", width * height);
    }
};
