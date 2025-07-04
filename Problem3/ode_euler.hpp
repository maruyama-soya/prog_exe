#pragma once
#include <iostream>
#include <cmath>

// y' = -y をオイラー法で解くクラス
class ODE_Euler {
public:
    double y;  // 現在のy
    double x;  // 現在のx
    double dx; // 刻み幅

    // コンストラクタ
    ODE_Euler() {
        std::cout << "Starting solver-A" << std::endl;
    };

    ODE_Euler(double y0, double x0, double dx0) : y(y0), x(x0), dx(dx0) {
        std::cout << "Starting solver-B" << std::endl;
    };

    // 1ステップ進める
    void step() {
        y += dx * (-y);
        x += dx;
        std::cout << x << " " << y << std::endl;
    }

    // 誤差を表示
    void print() {
        double y_true = std::exp(-x);
        std::cout << "x=" << x << ", y=" << y << ", error=" << y - y_true << std::endl;
    }
    void solve(){
        std::cout << "Solving ODE using Euler's method..." << std::endl;
        while (x < 1.0) {
            step();
        }
        print();
    }
};