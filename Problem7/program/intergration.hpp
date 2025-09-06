#pragma once
#include <iostream>
#include <functional> // std::function を使うために必要
#include <cmath>      // std::fabs を使うために必要
#include <stdexcept>  // std::runtime_error を使うために必要

class IntFunc
{
public:
    IntFunc(){};

    // 任意の関数 F(x) を受け取ってその値を返す
    double Get(std::function<double(double)> F, double x)
    {
        return F(x);
    }

    // 任意の関数fを、区間[a, b]で数値積分する関数
    // 精度epsに達するまで、分割数nを倍にしながら再計算する（適応的中点法）
    double Integrate(std::function<double(double)> f, double a, double b, double eps = 1e-9) const 
    {
        int n = 100; // 初期の分割数
        double h = (b - a) / n;
        double sum = 0.0;
        
        // 最初の積分値を計算
        for (int i = 0; i < n; ++i) 
        {
            sum += f(a + i * h + h / 2.0);
        }
        sum *= h;

        while (true) 
        {
            n *= 2;
            // 安全装置：分割数が多すぎたらエラーを投げて終了
            if (n > 10000000) 
            { 
                throw std::runtime_error("Too many iterations. The function may have a singularity.");
            }
            h /= 2.0;
            
            // 前回の結果を利用して効率的に計算を更新
            double new_sum = 0.0;
            for (int i = 0; i < n; i += 2) 
            {
                new_sum += f(a + i * h + h / 2.0);
            }
            new_sum = 0.5 * sum + h * new_sum;
            
            // 前回の結果との差が許容誤差epsより小さくなったら終了
            if (std::fabs(new_sum - sum) < eps) 
            {
                return new_sum;
            }
            sum = new_sum;
        }
    }
};