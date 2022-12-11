#include <fstream>
#include <iostream>
#include <string>

class CPU
{
    public:
        CPU() : X(1), cycle_count(0), signal_strength(0) {}
        void noop() { tick(); };

        void addx(const int val)
        {
            tick();
            tick();
            X += val;
        }

        int get_signal_strength() { return signal_strength; }

    private:
        void tick()
        {
            cycle_count++;
            if ((cycle_count - 20) % 40 == 0)
                signal_strength += cycle_count * X;
        }

        int X;
        int cycle_count;
        int signal_strength;
};

int main()
{
    std::fstream input("input.txt");
    std::string line;

    CPU cpu;

    while(std::getline(input, line))
    {
        if (line.substr(0,4) == "addx")
            cpu.addx(std::stoi(line.substr(5)));
        else
            cpu.noop();
    }

    std::cout << cpu.get_signal_strength() << '\n';

    return 0;
}
