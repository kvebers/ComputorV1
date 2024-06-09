#include <iostream>
#include <sstream>
#include <vector>

struct Solver {
    float xPow2;
    float xPow1;
    float xPow0;
    Solver() : xPow2(0), xPow1(0), xPow0(0) {}
} solver;

std::ostream& operator<<(std::ostream& os, const Solver& solver) {
    os << solver.xPow2 << " * X^2";
    if (solver.xPow1 >= 0)
        os << " + " <<solver.xPow1 << " * X^1";
    else
        os << " - " << -solver.xPow1 << " * X^1";
    if (solver.xPow0 >= 0)
        os << " + " <<solver.xPow0 << " * X^0";
    else
        os << " - " << -solver.xPow0 << " * X^0";
    return os;
}

float simpleSolver(Solver &solver)
{
    float result = -solver.xPow0 / solver.xPow1;
    return result;
}

void difficultSolver(Solver &solver) {
    float delta = solver.xPow1 * solver.xPow1 - 4 * solver.xPow2 * solver.xPow0;
    if (delta < 0)
    {
        std::cout << "Discriminant is negative, the two solutions are:" << std::endl;
        std::cout << "(-" << solver.xPow1 /  2 / solver.xPow2 << " + i * "<< sqrt(-delta) /  2 / solver.xPow2 << std::endl;
        std::cout << "(-" << solver.xPow1 /  2 / solver.xPow2 << " - i * " << sqrt(-delta)  / 2 / solver.xPow2 << std::endl;
        exit(1);
    }
    float x1 = (-solver.xPow1 + sqrt(delta)) / (2 * solver.xPow2);
    float x2 = (-solver.xPow1 - sqrt(delta)) / (2 * solver.xPow2);
    std::cout << "Discriminant is positive or 0, the solutions are:" << std::endl;
    std::cout << x1 << std::endl;
    if (delta != 0)
        std::cout << x2 << std::endl;
}


void polynomSolver(Solver &solver)
{
    if (solver.xPow0 == 0 && solver.xPow1 == 0 && solver.xPow2 == 0)
    {
        std::cout << "All real numbers are solutions" << std::endl;
        exit(1);
    }
    if (solver.xPow2 == 0 && solver.xPow1 == 0 && solver.xPow0 != 0)
    {
        std::cout << "Something can't be nothing" << std::endl;
        exit(1);
    }
    if (solver.xPow2 == 0 && solver.xPow1 != 0)
    {
        std::cout << "Single Polynom Result: " << simpleSolver(solver) << std::endl;
        exit(1);
    }
    difficultSolver(solver);
    exit (1);
}


int main(int argc, char **argv)
{
    std::vector<std::string> args;
    if (argc == 2)
    {
        std::stringstream ss(argv[1]);
        std::string word;
        while (ss >> word) {
            args.push_back(word);
        }
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            args.push_back(argv[i]);
        }
    }
    Solver solver;
    int mode = 1;
    int last_symbol = 1;
    float value = 1.0;
    int degree = 0;
    for (unsigned long i = 0; i < args.size(); i++)
    {
        std::string arg = args[i];
        if (arg.find('=') != std::string::npos)
        {
            if (mode == -1)
            {
                std::cerr << "Multiple equations found" << std::endl;
                exit(1);
            }
            mode = -1;
        }
        else if (arg.find("X^-") != std::string::npos)
        {
            std::cerr << "Negative exponent" << std::endl;
            return 1;
        }
        else if (arg.find('-')  != std::string::npos)
            last_symbol = -1;
        else if (arg.find('+')  != std::string::npos || arg.find('=')  != std::string::npos)
            last_symbol = 1;
        else if (arg.find("X^2") != std::string::npos)
        {
            solver.xPow2 += mode * last_symbol * value;
            value = 1.0;
            if (degree < 2)
                degree = 2;
        }
        else if (arg.find("X^1") != std::string::npos)
        {
            solver.xPow1 += mode * last_symbol * value;
            value = 1.0;
            if (degree < 1)
                degree = 1;
        }
        else if (arg.find("X^0") != std::string::npos)
        {
            solver.xPow0 += mode * last_symbol * value;
            value = 1.0;
        }
        else if (arg.find("X^") != std::string::npos)
        {
            std::string exponentStr = arg.substr(arg.find("X^") + 2);
            int tempDegree;
            try {
            tempDegree = std::stoi(exponentStr);
            } catch (std::exception &e) {
                std::cerr << "Invalid exponent" << std::endl;
                exit (1);
            }
            if (tempDegree > degree)
                degree = tempDegree;
        }
        else if (arg.find('*') != std::string::npos)
            continue;
        else {
            try { value = std::stof(arg);} catch (std::exception &e) {}
        }
    }
    if (mode != -1) {
        std::cerr << "No equation found" << std::endl;
        return 1;
    }
    if (degree > 2)
    {
        std::cout << "Polynomial degree: " << degree << std::endl;
        std::cerr << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
        return 1;
    }
    std::cout << "Polynomial degree: " << degree << std::endl;
    std::cout << "Reduced Form: " << solver << " = 0" <<std::endl;
    polynomSolver(solver);
    return 0;
}