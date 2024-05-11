#include <iostream>
#include <string>
#include <list>;

using std::list;
using std::string;
using std::cout;
using std::endl;


struct Point
{
    public:
    int X;
    int Y;
    Point(int x, int y )
    {
        X = x;
        Y = y;
    }
    string toString()
    {
        string str = "X:" + std::to_string(X) + " Y:" + std::to_string(Y);
        return str;
    }
};

class Way
{
    list<Point> way;
    int totalCost;

public:
    Way(Point p, int costPoint)
    {
        way.push_back(p);
        totalCost = costPoint;
    }
    void AddPoint(Point p, int costPoint)
    {
        way.push_front(p);
        totalCost += costPoint;
    }
    void showWay()
    {
        for (Point n : way)
           cout << n.toString() <<"z" << "\t";
        cout << std::endl;
    }
    int GetTotalCost()
    {
        return totalCost;
    }

};

Way getBestWay(Point currPosition, Point finishPosition, int** zone)
{
    //если попали на финиш
    if (currPosition.X == finishPosition.X && currPosition.Y == finishPosition.Y)
    {
        return Way(finishPosition, zone[finishPosition.Y][finishPosition.X]);
    }
    if (currPosition.X == finishPosition.X || currPosition.Y == finishPosition.Y)
    {
        //если уже прижаты к одной из граней матрицы ---> то путь остался один --**(Гарантирует не выход за пределы массива)**
        Point nextPos = currPosition;
        //cout << "current position" << currPosition.toString()<<endl;
        if (currPosition.X == finishPosition.X) 
        {
            nextPos.Y += 1;
        }
        else 
        {
            nextPos.X += 1;
        }
        Way w1 = getBestWay(nextPos, finishPosition, zone);
        w1.AddPoint(currPosition, zone[currPosition.Y][currPosition.X]);
        return w1;
    }
    //cout << "midle position" << endl;
    
    //текущее положение точки имеет два варианта движения (вниз или вправо)
    Point nextPos1(currPosition.X+1, currPosition.Y);
    Point nextPos2(currPosition.X, currPosition.Y + 1);
    Way w1 = getBestWay(nextPos1, finishPosition, zone);
    Way w2 = getBestWay(nextPos2, finishPosition, zone);
    if (w1.GetTotalCost() < w2.GetTotalCost())
    {
        w1.AddPoint(currPosition, zone[currPosition.Y][currPosition.X]);
        return w1;
    }
    else
    {
        w2.AddPoint(currPosition, zone[currPosition.Y][currPosition.X]);
        return w2;
    }
}

int** getRandomMatrix(int row, int col)
{
    //инициализация случайной матрицы для проверки алгоритма поиска оптимального пути
    int** zone = new int* [row];
    for (size_t i = 0; i < row; i++)
    {
        *(zone + i) = new int[col];
    }
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            zone[i][j] = rand() % (3 + 1); // от 0 до 3
            cout << zone[i][j] << '\t';
        }
        cout << endl;
    }
    return zone;
}
const int ROW = 5;
const int COLS = 6;

int main()
{
    setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы

    //инициализация матрицы со случайными значения цена точки -- для проверки алгоритма поиска оптимального пути
    int** zone = getRandomMatrix(ROW, COLS);

    Point startPos(0, 0); // начальная позиция 
    Point finishPos(COLS -1, ROW-1); // целевая позиция

    cout << "showWay:\n";
    //Получение оптимального пути по матрице
    Way bestWay = getBestWay(startPos, finishPos, zone);
    bestWay.showWay();
    cout << "TotalCost:"<< bestWay.GetTotalCost();

    //удаление исходной матрицы
    for (size_t i = 0; i < ROW; i++)
    {
        delete[] zone[i];
    }
    delete[] zone;
}