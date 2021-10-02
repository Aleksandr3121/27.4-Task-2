#include <iostream>
#include <cmath>

using namespace std;

struct Coordinate {
    double x, y;
};

enum class Color {
    RED,
    BLUE,
    GREEN
};

istream& operator>>(istream& stream, Color& color) {
    string in_str;
    stream >> in_str;
    if (in_str == "red")color = Color::RED;
    else if (in_str == "blue")color = Color::BLUE;
    else if (in_str == "green")color == Color::GREEN;
    else stream.clear(ios::failbit);
    return stream;
}

ostream& operator<<(ostream& stream, const Color& color) {
    if (color == Color::RED)stream << "red";
    else if (color == Color::BLUE)stream << "blue";
    else stream << "green";
    return stream;
}

class Rectangle;

class Figure {
public:
    Figure(Coordinate inCenter, Color inColor, string inName) :
            center(inCenter),
            color(inColor),
            name(inName) {}

    virtual const string& GetName() const{
        return name;
    }

    virtual double Square() const = 0;

    virtual Rectangle SearchRectangle() const = 0;



protected:
    Coordinate center;
    Color color;
    string name;
};

class Rectangle : public Figure {
public:
    Rectangle(Coordinate inCenter, Color inColor, double inHeight, double inWidth) :
            Figure(inCenter, inColor, "rectangle"),
            height(inHeight),
            width(inWidth) {}

    double Square() const override {
        return height * width;
    }

    Rectangle SearchRectangle() const override {
        return Rectangle(center, color, height + 1, width + 1);
    }

    void PrintRectangle() {
        cout << "Coordinate of center: {" << center.x << ", " << center.y << "}\n"
             << "Color of rectangle: " << color << '\n'
             << "Height: " << height << '\n'
             << "Width: " << width << endl;
    }

private:
    double height;
    double width;
};

class Circle : public Figure {
public:
    Circle(Coordinate inCenter, Color inColor, double inRadius) :
            Figure(inCenter, inColor, "circle"),
            radius(inRadius) {}

    double Square() const override {
        return 3.14 * radius * radius;
    }

    Rectangle SearchRectangle() const override {
        return Rectangle(center, color, radius + 1, radius + 1);
    }

private:
    double radius;
};

class Quadrate : public Figure {
public:
    Quadrate(Coordinate inCenter, Color inColor, double inEdgeLength) :
            Figure(inCenter, inColor, "square"),
            edgeLength(inEdgeLength) {}

    double Square() const override {
        return edgeLength * edgeLength;
    }

    Rectangle SearchRectangle() const override {
        return Rectangle(center, color, edgeLength + 1, edgeLength + 1);
    }

private:
    double edgeLength;
};

class EquilateralTriangle : public Figure {
public:
    EquilateralTriangle(Coordinate inCenter, Color inColor, double inEdgeLength) :
            Figure(inCenter, inColor, "triangle"),
            edgeLength(inEdgeLength) {}

    double Square() const override {
        return edgeLength * edgeLength * sqrt(3) / 4;
    }

    Rectangle SearchRectangle() const override {
        //для нахождения прямоугольника возьмем радиус описанной окружности
        double a = edgeLength * sqrt(3) / 3;
        return Rectangle(center, color, a + 1, a + 1);
    }

private:
    double edgeLength;
};

void SquareFigureAndSearchRectangle(const Figure& figure) {
    cout<<"Square of "<<figure.GetName()<<' '<<figure.Square()<<'\n'
        <<"Found rectangle:\n";
    figure.SearchRectangle().PrintRectangle();
}

int main() {
    string figure;
    while (cin >> figure && figure != "exit") {
        if (figure == "circle") {
            double x, y, r;
            Color color;
            cout << "Enter coordinate center of " << figure << ": ";
            cin >> x >> y;
            cout << "Enter color(red or blue or green) of " << figure << ": ";
            cin >> color;
            cout << "Enter radius of " << figure << ": ";
            cin >> r;
            Circle circle(Coordinate{x, y}, color, r);
            SquareFigureAndSearchRectangle(circle);
        } else if (figure == "square") {
            double x, y, edgeLength;
            Color color;
            cout << "Enter coordinate center of " << figure << ": ";
            cin >> x >> y;
            cout << "Enter color(red or blue or green) of " << figure << ": ";
            cin >> color;
            cout << "Enter edge length of " << figure << ": ";
            cin >> edgeLength;
            Quadrate square(Coordinate{x, y}, color, edgeLength);
            SquareFigureAndSearchRectangle(square);
        } else if (figure == "triangle") {
            double x, y, edgeLength;
            Color color;
            cout << "Enter coordinate center of " << figure << ": ";
            cin >> x >> y;
            cout << "Enter color(red or blue or green) of " << figure << ": ";
            cin >> color;
            cout << "Enter edge length of " << figure << ": ";
            cin >> edgeLength;
            EquilateralTriangle triangle(Coordinate{x, y}, color, edgeLength);
            SquareFigureAndSearchRectangle(triangle);
        } else if (figure == "rectangle") {
            double x, y, height, width;
            Color color;
            cout << "Enter coordinate center of " << figure << ": ";
            cin >> x >> y;
            cout << "Enter color(red or blue or green) of " << figure << ": ";
            cin >> color;
            cout << "Enter height of " << figure << ": ";
            cin >> height;
            cout << "Enter width of " << figure << ": ";
            cin >> width;
            Rectangle rectangle(Coordinate{x, y}, color, height, width);
            SquareFigureAndSearchRectangle(rectangle);
        } else cout << "Unknown command" << endl;
    }
    return 0;
}
