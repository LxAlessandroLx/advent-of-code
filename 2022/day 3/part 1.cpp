#include <iostream>
#include <fstream>
#include <string>

#define IS_LOWER(c) (c >= 'a' && c <= 'z')

unsigned checkSameItem(std::string str);

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    unsigned prioritySum = 0;

    while (getline(input, line))
    {
        prioritySum += checkSameItem(line);
    }

    std::cout << prioritySum << "\n";

    return 0;
}

unsigned checkSameItem(std::string str)
{
    const std::string firstHalf = str.substr(0, str.length()/2);
    const std::string secondHalf = str.substr(str.length()/2);

    for (const auto & c : firstHalf)
    {
        for (const auto & d : secondHalf)
        {
            if (c == d)
                return c + (IS_LOWER(c) ? - 'a' + 1 : - 'A' + 27);
        }
    }
}
