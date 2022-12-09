#include <iostream>
#include <fstream>

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

        switch (you)
        {
            case 'X':
                score += (CURRENT_OPPONENT + 1) % 3 + 1;
                break;
            case 'Y':
                score += CURRENT_OPPONENT + 3;
                break;
            case 'Z': 
                score += (CURRENT_OPPONENT % 3 + 1) + 6;
                break;
        }
    }

    std::cout << score << "\n";
    

    return 0;
}