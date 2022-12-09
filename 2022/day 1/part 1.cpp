#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    int num = 0;
    int max = 0;

    while (getline(input, line))
    {
        try
        {
            num += std::stoi(line);
        }
        catch(const std::invalid_argument& e)
        {
            if (max < num)
                max = num;
            num = 0;
        }
    }

    std::cout << max << "\n";

    return 0;
}
