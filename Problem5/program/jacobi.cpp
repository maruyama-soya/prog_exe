#include <iostream>
#include <fstream>
#include <filesystem>
#include "jacobi.hpp"

#define USE_JACOBI

int main() {
    std::filesystem::path myPath = "./jacobi_data";
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

    // ★追加: 途中経過を保存するファイル名と、保存したい回数を設定する
    JJ.intermediate_filename = myPath / "jacobi_intermediate.txt";
    JJ.SaveTimes.insert(1);
    JJ.SaveTimes.insert(10);
    JJ.SaveTimes.insert(100);
    JJ.SaveTimes.insert(1000);
    JJ.SaveTimes.insert(5000);
    JJ.SaveTimes.insert(10000);

    // ★変更: Solverの戻り値をチェックし、収束しなかった場合にメッセージを出す
    std::cout << "\n--- Solving by Jacobi Iteration ---" << std::endl;
    if (!JJ.Solver(20000)) 
    { // 最大反復回数を少し増やしてテスト
        std::cout << "\nERROR: Jacobi method did not converge within the maximum iterations." << std::endl;
    }
    // Solverが成功しても失敗しても、その時点での最終結果は保存する
    JJ.Save(myPath / "jacobi_final.txt");//ヤコビ法の結果を保存

    std::cout << "\n--- Solving by Direct Inverse ---" << std::endl;
    JJ.Inv();
    JJ.Save(myPath / "inverse_result.txt");//直接解法の結果を保存

#else
    std::cout << "BC_Solver part is not implemented." << std::endl;
#endif

    std::cout << "\nAll processes finished." << std::endl;
    return 0;
}