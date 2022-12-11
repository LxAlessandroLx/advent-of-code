#include <fstream>
#include <iostream>
#include <string>

class CRT
{
    public:
        void update(const int cycle, const int X)
        {
            const int row = (cycle % 240) / 40;
            const int col = (cycle % 240) % 40;

            screen[row][col] = (col >= X-1 && col <= X+1) ? '#' : '.';
        }

        void draw()
        {
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 40; j++)
                    std::cout << screen[i][j];

                std::cout << '\n';
            }
        }

    private:
        char screen[6][40] = {};
};

class CommunicationSystem
{
    public:
        CommunicationSystem() : X(1), currentCycle(0) {}
        void noop() { tick(); }

        void addx(const int val)
        {
            tick();
            tick();
            X += val;
        }

        void printCRT() { crt.draw(); }

    private:
        void tick()
        {
            crt.update(currentCycle, X);
            currentCycle++;
        }

        int X;
        int currentCycle;
        CRT crt;
};

int main()
{
    std::ifstream input("input.txt");
    std::string line;

    CommunicationSystem cs;

    while(std::getline(input, line))
    {
        if (line.substr(0,4) == "addx")
            cs.addx(std::stoi(line.substr(5)));
        else
            cs.noop();
    }

    cs.printCRT();

    return 0;
}
