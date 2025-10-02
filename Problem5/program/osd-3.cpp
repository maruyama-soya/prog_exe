#include "osd-3.hpp" 
#include <iostream>
#include <limits>
#include <filesystem>

int main() 
{
    BC_Solver solver;

    // 境界条件を設定
    solver.Y0 = 1.0;
    solver.Y1 = 0.0;

    // パラメータ入力
    std::cout << "Enter the value for C: ";
    std::cin >> solver.C;
    std::cout << "Enter the value for N: ";
    std::cin >> solver.N;

    if (std::cin.fail() || solver.N <= 0 || solver.C <= 0) 
    {
        std::cerr << "Invalid input. Please enter positive numbers for C and N." << std::endl;
        return 1;
    }

    std::cout << "Solving with C=" << solver.C << ", N=" << solver.N << "..." << std::endl;

    solver.Solve();

    // 実行ディレクトリに保存
    std::filesystem::path myPath = "program/solution.dat";
    solver.Save(myPath);

    std::cout << "Solution saved to " << myPath.string() << std::endl;
    return 0;
}