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

        bool touch();
        void move(const Position & pos);

        unsigned getCoveredCells() { return coveredCells.size(); }
        bool isAlignedX() { return head.x == tail.x; }
        bool isAlignedY() { return head.y == tail.y; }

    private:
        Position head, tail;
        std::vector<Position> coveredCells;
};

Rope::Rope() :
    head({0,0}),
    tail({0,0})
{
    coveredCells.push_back({0,0});
}

bool Rope::touch()
{
    for (int i = tail.x-1; i <= tail.x+1; i++)
    {
        for (int j = tail.y-1; j <= tail.y+1; j++)
        {
            if (head.x == i && head.y == j)
                return true;
        }
    }

    return false;
}

void Rope::move(const Position & pos)
{
    head.move(pos);

    if (touch())
        return;

    if (!isAlignedX())
        tail.x = head.x > tail.x ? tail.x+1 : tail.x-1;
    if (!isAlignedY())
        tail.y = head.y > tail.y ? tail.y+1 : tail.y-1;

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
