#include <iostream>
#include <vector>
#include <fstream>

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    std::vector<char> piles[9];
    
    for (int i = 0; i < 9; i++)
    {
        std::getline(input, line);

        for (char crate : line)
            piles[i].push_back(crate);
    }

    int crateNum;
    int srcCrate, dstCrate;

    while (input >> crateNum)
    {
        input >> srcCrate;
        input >> dstCrate;

        srcCrate--, dstCrate--;

        for (int i = crateNum; i > 0; i--)
            piles[dstCrate].push_back(piles[srcCrate][piles[srcCrate].size()-i]);

        piles[srcCrate].erase(piles[srcCrate].end()-crateNum, piles[srcCrate].end());
    }

    for (int i = 0; i < 9; i++)
        std::cout << piles[i].back();

    std::cout << "\n";

    return 0;
}
