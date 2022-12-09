#include <iostream>
#include <stack>
#include <fstream>

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    std::stack<char> cratesStack[9];
    
    for (int i = 0; i < 9; i++)
    {
        std::getline(input, line);

        for (char crate : line)
            cratesStack[i].push(crate);
    }

    int crateNum;
    int srcCrate, dstCrate;

    while (input >> crateNum)
    {
        input >> srcCrate;
        input >> dstCrate;

        srcCrate--, dstCrate--;

        for (int i = 0; i < crateNum; i++)
        {
            cratesStack[dstCrate].push(cratesStack[srcCrate].top());
            cratesStack[srcCrate].pop();
        }   
    }

    for (int i = 0; i < 9; i++)
        std::cout << cratesStack[i].top();

    std::cout << "\n";

    return 0;
}
