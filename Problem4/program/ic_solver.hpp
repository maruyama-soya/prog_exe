#pragma once
#include <string>
#include <filesystem>
#include <vector>

class IC_Solver {
public:
    int N;  // 分割数
    double C = 1.0; // 定数C
    double x0 = 0.0, x1 = 2 * M_PI; // xの範囲
    std::vector<double> y, z, x;

    std::filesystem::path outPath;

    IC_Solver(std::filesystem::path p);

    void solve();
    void step(int i, double dx);
    void write_result() const;
};

#include "ic_solver.hpp"
#include <fstream>
#include <cmath>
#include <iostream>

IC_Solver::IC_Solver(std::filesystem::path p) : outPath(p) {
    std::cout << "Solver initialized" << std::endl;
}

void IC_Solver::solve() {
    double dx = (x1 - x0) / N;
    x.resize(N + 1);
    y.resize(N + 1);
    z.resize(N + 1);

    x[0] = x0;
    y[0] = 1.0;
    z[0] = 0.0;

    for (int i = 0; i < N; ++i) {
        x[i+1] = x[i] + dx;
        y[i+1] = y[i] + dx * z[i];
        z[i+1] = z[i] - dx * C * y[i];
    }

    write_result();
}

void IC_Solver::write_result() const {
    std::filesystem::create_directories(outPath);
    std::ofstream file(outPath / "solution.csv");
    for (int i = 0; i <= N; ++i) {
        file << x[i] << "," << y[i] << "," << z[i] << "\n";
    }
    std::cout << "Saved to: " << outPath / "solution.csv" << std::endl;
}