#include <iostream>
#include <fstream>
#include <vector>

unsigned getScenicScore(std::vector<std::vector<unsigned>> trees, int row, int column);

int main()
{
    std::ifstream input("input.txt");
    std::string line;

    std::vector<std::vector<unsigned>> treeHeights;
    unsigned maxScenicScore = 0;

    while (std::getline(input, line))
    {
        treeHeights.push_back({});

        treeHeights.back().reserve(line.size());

        for (char c : line)
            treeHeights.back().push_back((unsigned)c - '0');
    }

    for (int i = 0; i < treeHeights.size(); i++)
    {
        for (int j = 0; j < treeHeights[0].size(); j++)
        {
            const unsigned currentScenicScore = getScenicScore(treeHeights, i, j);

            if (maxScenicScore < currentScenicScore)
                maxScenicScore = currentScenicScore;
        }
    }

    std::cout << maxScenicScore << "\n";

    return 0;
}

unsigned getScenicScore(std::vector<std::vector<unsigned>> trees, int row, int column)
{
    unsigned left = 0, right = 0, top = 0, down = 0;

    // top
    for (int i = row-1; i >= 0; i--)
    {
        top++;
        if (trees[row][column] <= trees[i][column])
            break;
    }

    // down
    for (int i = row+1; i < trees.size(); i++)
    {
        down++;
        if (trees[row][column] <= trees[i][column])
            break;
    }

    // left
    for (int i = column-1; i >= 0; i--)
    {
        left++;
        if (trees[row][column] <= trees[row][i])
            break;
    }

    // right
    for (int i = column+1; i < trees[0].size(); i++)
    {
        right++;
        if (trees[row][column] <= trees[row][i])
            break;
    }

    return top * down * left * right;
}
