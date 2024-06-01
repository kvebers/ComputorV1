#include <iostream>

struct Solver {
    float xPow2;
    float xPow1;
    float xPow0;

    Solver() : xPow2(0), xPow1(0), xPow0(0) {}
} solver;

std::ostream& operator<<(std::ostream& os, const Solver& solver) {
    os << "x^2: " << solver.xPow2 << ", x^1: " << solver.xPow1 << ", x^0: " << solver.xPow0;
    return os;
}

int main(int argc, char **argv)
{

    Solver solver;
    int mode = 1;
    int last_symbol = 1;
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg.find('=') != std::string::npos)
            mode = -1;
    }
    return 0;
}