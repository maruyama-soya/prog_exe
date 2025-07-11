#include <iostream>
#include <fstream>
#include <filesystem>
#include "jacobi.hpp"

#define USE_JACOBI

int main() 
{
    std::filesystem::path myPath = "./data";
    std::filesystem::create_directories(myPath);

#ifdef USE_JACOBI
    Jacobi JJ;

    std::cout << "Enter the value for C: ";
    std::cin >> JJ.C;

    size_t n; 
    std::cout << "Enter the grid size N: ";
    std::cin >> n;

    if (std::cin.fail() || n <= 1) 
    {
        std::cerr << "Invalid input for N. Please enter an integer greater than 1." << std::endl;
        return 1;
    }
    
    JJ.resize(n);
    JJ.Init();

    JJ.intermediate_filename = myPath / "jacobi_intermediate.txt";
    JJ.SaveTimes.insert(100);
    JJ.SaveTimes.insert(1000);
    JJ.SaveTimes.insert(10000);

    // ★★★ 変更点：Solverに関数の引数としてログファイル名を渡す ★★★
    std::cout << "\n--- Solving by Jacobi Iteration ---" << std::endl;
    if (!JJ.Solver(20000, myPath / "jacobi_norm_log.txt")) 
    { 
        std::cout << "\nERROR: Jacobi method did not converge within the maximum iterations." << std::endl;
    }
    JJ.Save(myPath / "jacobi_final.txt");

    std::cout << "\n--- Solving by Direct Inverse ---" << std::endl;
    JJ.Inv();
    JJ.Save(myPath / "inverse_result.txt");

#endif

    std::cout << "\nAll processes finished." << std::endl;
    return 0;
}