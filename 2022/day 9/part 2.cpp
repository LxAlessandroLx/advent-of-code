#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Position
{
    int x, y;

    void move(const Position & pos)
    {
        x += pos.x;
        y += pos.y;
    }

    bool operator ==(const Position & pos) { return x == pos.x && y == pos.y; }
};

class Rope
{
    public:
        Rope();

        bool touch(unsigned knot);
        void move(const Position & pos);

        unsigned getCoveredCells() { return coveredCells.size(); }
        bool isAlignedX(unsigned knot) { return knots[knot-1].x == knots[knot].x; }
        bool isAlignedY(unsigned knot) { return knots[knot-1].y == knots[knot].y; }

    private:
        Position knots[10];
        Position & head, & tail;
        std::vector<Position> coveredCells;
};

Rope::Rope() :
    knots({0}),
    head(knots[0]),
    tail(knots[9])
{
    coveredCells.push_back({0,0});
}

bool Rope::touch(unsigned knot)
{
    for (int i = knots[knot].x-1; i <= knots[knot].x+1; i++)
    {
        for (int j = knots[knot].y-1; j <= knots[knot].y+1; j++)
        {
            if (knots[knot-1].x == i && knots[knot-1].y == j)
                return true;
        }
    }

    return false;
}

void Rope::move(const Position & pos)
{
    head.move(pos);

    for (int i = 1; i < 10; i++)
    {
        if (touch(i))
            return;

        if (!isAlignedX(i))
            knots[i].x = knots[i-1].x > knots[i].x ? knots[i].x+1 : knots[i].x-1;
        if (!isAlignedY(i))
            knots[i].y = knots[i-1].y > knots[i].y ? knots[i].y+1 : knots[i].y-1;

    }

    if (std::find(coveredCells.begin(), coveredCells.end(), tail) == coveredCells.end())
    {
        coveredCells.push_back(tail);
    }
}

void move(Rope & rope, const Position & pos, unsigned steps = 1);

int main()
{
    std::ifstream input("input.txt");

    char direction;
    unsigned steps;

    Rope rope;

    while (input >> direction)
    {
        input >> steps;
        switch (direction)
        {
            case 'R':
                move(rope, {1,0}, steps);
                break;
            case 'L':
                move(rope, {-1,0}, steps);
                break;
            case 'U':
                move(rope, {0,-1}, steps);
                break;
            case 'D':
                move(rope, {0,1}, steps);
                break;
        }
    }

    std::cout << rope.getCoveredCells() << "\n";
    
    return 0;
}

void move(Rope & rope, const Position & pos, unsigned steps)
{
    while (steps--)
        rope.move(pos);
}
