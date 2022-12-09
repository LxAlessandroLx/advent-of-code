#include <iostream>
#include <fstream>
#include <string>

struct Assignment
{
    int ID_start, ID_end;
};

struct Pair
{
    Assignment one, two;
};

bool overlap(Pair pair);

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    Pair pair;
    unsigned fullyContain = 0;

    while (getline(input, line))
    {
        std::string p1 = line.substr(0, line.find(','));
        std::string p2 = line.substr(line.find(',')+1);

        pair.one.ID_start = std::stoi(p1.substr(0, p1.find('-')));
        pair.one.ID_end = std::stoi(p1.substr(p1.find('-')+1));

        pair.two.ID_start = std::stoi(p2.substr(0, p2.find('-')));
        pair.two.ID_end = std::stoi(p2.substr(p2.find('-')+1));

        fullyContain += overlap(pair);
    }

    std::cout << fullyContain << "\n";

    return 0;
}

bool overlap(Pair pair)
{
    int min = pair.one.ID_start < pair.two.ID_start ? pair.one.ID_start : pair.two.ID_start;
    int endMin = min == pair.one.ID_start ? pair.one.ID_end : pair.two.ID_end;
    int max = pair.one.ID_start > pair.two.ID_start ? pair.one.ID_start : pair.two.ID_start;

    if (max >= min && max <= endMin)
        return true;

    return false;
}
