#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>

class Monkey
{
public:
    Monkey() : 
        addItself(false), multiplyItself(false), 
        addFactor(0), multiplyFactor(1), 
        inspectedCount(0) 
    {}

    void addItem(const int item) { items.push(item); }
    bool hasItems() { return !items.empty(); }
    unsigned getInspectedCount() { return inspectedCount; }

    void throwItem(std::vector<Monkey> & monkeys)
    {
        monkeys[(items.front() % testFactor == 0) ? monkey1 : monkey2].addItem(items.front());

        items.pop();
    }

    void inspect()
    {
        int & currentItem = items.front();

        if (addItself)
            addFactor = currentItem;
        else if (multiplyItself)
            multiplyFactor = currentItem;

        currentItem = (currentItem + addFactor) * multiplyFactor;
        currentItem /= 3;

        inspectedCount++;
    }

    int monkey1, monkey2;
    bool addItself, multiplyItself;
    int addFactor, multiplyFactor, testFactor;

private:
    std::queue<int> items;
    unsigned inspectedCount;
};

class Parser
{
public:
    static Monkey parse(std::ifstream & file)
    {
        Monkey monkey;

        parseItems(file, monkey);
        parseOperation(file, monkey);
        parseTest(file, monkey);
        parseCondition(file, monkey, true);
        parseCondition(file, monkey, false);

        return monkey;
    }

private:
    Parser() {}

    static void parseItems(std::ifstream & file, Monkey & monkey)
    {
        std::string line;
        std::getline(file, line);

        line.erase(0, line.find(':') + 2);

        size_t pos = 0;
        while ((pos = line.find(", ")) != std::string::npos)
        {
            monkey.addItem(std::stoi(line.substr(0, pos)));
            line.erase(0, pos + 2);
        }

        monkey.addItem(std::stoi(line));
    }

    static void parseOperation(std::ifstream & file, Monkey & monkey)
    {
        std::string line;
        std::getline(file, line);

        line.erase(0, line.find("old") + 4);
        
        if (line[2] == 'o') // old
        {
            if (line[0] == '+')
                monkey.addItself = true;
            else
                monkey.multiplyItself = true;
        }
        else
        {
            int factor = std::stoi(line.substr(1));

            if (line[0] == '+')
                monkey.addFactor = factor;
            else
                monkey.multiplyFactor = factor;
        }
    }

    static void parseTest(std::ifstream & file, Monkey & monkey)
    {
        std::string line;
        std::getline(file, line);

        line.erase(0, line.find("by") + 3);
        monkey.testFactor = std::stoi(line);
    }

    static void parseCondition(std::ifstream & file, Monkey & monkey, const bool condition)
    {
        std::string line;
        std::getline(file, line);

        if (condition)
            monkey.monkey1 = std::stoi(line.substr(line.find("monkey") + 7));
        else
            monkey.monkey2 = std::stoi(line.substr(line.find("monkey") + 7));
    }
};

int main()
{
    std::ifstream input("input.txt");
    std::string line;

    std::vector<Monkey> monkeys;

    while (std::getline(input, line))
    {
        monkeys.push_back(Parser::parse(input));

        std::getline(input, line);
    }

    for (int i = 0; i < 20; i++)
    {
        for (Monkey & monkey : monkeys)
        {
            while (monkey.hasItems())
            {
                monkey.inspect();

                monkey.throwItem(monkeys);
            }
        }
    }

    std::sort(monkeys.begin(), monkeys.end(), [](Monkey & m1, Monkey & m2) { return m1.getInspectedCount() > m2.getInspectedCount(); });
    std::cout << monkeys[0].getInspectedCount() * monkeys[1].getInspectedCount() << "\n";

    return 0;
}
