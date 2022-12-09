#include <iostream>
#include <fstream>

int findMarker(std::string str);

int main()
{
    std::ifstream input("input.txt");
    std::string str;

    std::getline(input, str);

    std::cout << findMarker(str) << "\n";

    return 0;
}

int findMarker(std::string str)
{
    for (int k = 3;; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i != j && str[k-i] == str[k-j])
                    goto skip;
            }
        }
        return k+1;
        skip:;
    }

    return -1;
}
