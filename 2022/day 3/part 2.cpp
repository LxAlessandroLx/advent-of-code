#include <iostream>
#include <fstream>
#include <string>

#define IS_LOWER(c) (c >= 'a' && c <= 'z')

struct Group
{
    std::string elf1, elf2, elf3;
};

unsigned findBadge(Group group);

int main()
{
    std::ifstream input("input.txt");

    Group group;
    unsigned prioritySum = 0;

    while (getline(input, group.elf1))
    {
        getline(input, group.elf2);
        getline(input, group.elf3);

        prioritySum += findBadge(group);
    }

    std::cout << prioritySum << "\n";

    return 0;
}

unsigned findBadge(Group group)
{
    for (const auto & c : group.elf1)
    {
        for (const auto & d : group.elf2)
        {
            for (const auto & e : group.elf3)
            {
                if (c == d && d == e)
                    return c + (IS_LOWER(c) ? - 'a' + 1 : - 'A' + 27);
            }
        }
    }
}
