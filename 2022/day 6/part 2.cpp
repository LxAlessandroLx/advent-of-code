#include <iostream>
#include <fstream>

int findMarker(std::string str, unsigned charactersNum = 4);

int main()
{
    std::ifstream input("input.txt");
    std::string str;

    std::getline(input, str);

    std::cout << findMarker(str, 14) << "\n";

    return 0;
}

int findMarker(std::string str, unsigned charactersNum)
{
    for (int k = charactersNum-1;; k++)
    {
        for (int i = 0; i < charactersNum-1; i++)
        {
            for (int j = 0; j < charactersNum; j++)
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
