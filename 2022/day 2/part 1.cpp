#include <iostream>
#include <fstream>

#define CURRENT_YOU (you - 'X' + 1)
#define CURRENT_OPPONENT (opponent - 'A' + 1)

int main()
{
    std::ifstream input("input.txt");

    char opponent;
    char you;
    unsigned score = 0;

    while (input >> opponent)
    {
        input >> you;

        score += CURRENT_YOU;

        if (CURRENT_OPPONENT % 3 + 1 == CURRENT_YOU)
            score += 6;
        else if (CURRENT_OPPONENT == CURRENT_YOU)
            score += 3;
    }

    std::cout << score << "\n";
    
    return 0;
}
