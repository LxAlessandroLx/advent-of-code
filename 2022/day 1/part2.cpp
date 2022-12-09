#include <iostream>
#include <fstream>
#include <string>

int sum(int array[3]);

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    int num = 0;
    int topThree[3];
    unsigned index = 0;

    while (getline(input, line))
    {
        try
        {
            num += std::stoi(line);
        }
        catch(const std::invalid_argument& e)
        {
            if (index < 3)
            {
                topThree[index++] = num;
            }
            else
            {
                int *min = &topThree[0];

                for (int i = 1; i < 3; i++)
                {
                    if (topThree[i] < *min)
                    {
                        min = &topThree[i];
                    }
                }

                if (*min < num)
                    *min = num;
            }

            num = 0;
        }
    }

    std::cout << sum(topThree) << "\n";

    return 0;
}

int sum(int array[3])
{
    int sum = 0;

    for (int i = 0; i < 3; i++)
    {
        sum += array[i];
    }

    return sum;
}
