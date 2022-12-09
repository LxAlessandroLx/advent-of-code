#include <iostream>
#include <fstream>
#include <vector>

bool isVisible(std::vector<std::vector<unsigned>> trees, int row, int column);

int main()
{
    std::ifstream input("input.txt");
    std::string line;

    std::vector<std::vector<unsigned>> treeHeights;
    unsigned visibleCount = 0;

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
            visibleCount += isVisible(treeHeights, i, j);
    }

    std::cout << visibleCount << "\n";

    return 0;
}

bool isVisible(std::vector<std::vector<unsigned>> trees, int row, int column)
{
    bool visible = true;

    // top
    for (int i = 0; i < row; i++)
    {
        if (trees[row][column] <= trees[i][column])
        {
            visible = false;
            break;
        }
    }
    if (visible) return true;
    visible = true;

    // down
    for (int i = trees.size()-1; i > row; i--)
    {
        if (trees[row][column] <= trees[i][column])
        {
            visible = false;
            break;
        }
    }
    if (visible) return true;
    visible = true;

    // left
    for (int i = 0; i < column; i++)
    {
        if (trees[row][column] <= trees[row][i])
        {
            visible = false;
            break;
        }
    }
    if (visible) return true;
    visible = true;

    // right
    for (int i = trees[0].size()-1; i > column; i--)
    {
        if (trees[row][column] <= trees[row][i])
        {
            visible = false;
            break;
        }
    }
    if (visible) return true;

    return false;
}
