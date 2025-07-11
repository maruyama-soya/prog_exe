#include <iostream>
#include <vector>
#include <cmath>    // cos, sin, erf, exp, M_PIなどの数学関数を使うため
#include <iomanip>  // 出力フォーマットを整えるため

// 被積分関数
// 引数: th (角度θ), U (パラメータU)
double integrand(double th, double U) 
{
    auto UC = U * std::cos(th);
    auto US = U * std::sin(th);
    auto ERF = std::erf(UC);      // C++17標準の誤差関数 erf
    auto EXP = std::exp(-US * US);

    // M_2_SQRTPIは2/√π を示す定数。COEF = (2/√π)/4 = 1/(2√π)
    const double COEF = M_2_SQRTPI / 4.0;
    
    return COEF * EXP * ERF * UC;
}

// 台形公式で積分を計算する関数
// 引数: N (分割数), U (パラメータU)
// 戻り値: 積分の近似値
double calculate_integral(int N, double U) 
{
    double sum = 0.0;
    const double dth = 2.0 * M_PI / N; // 1ステップあたりの角度

    for (int i = 0; i < N; i++) 
    {
        double y0 = integrand(dth * i, U);
        double y1 = integrand(dth * (i + 1), U);
        // 台形の面積 (y0+y1) * dth / 2 を足し合わせる
        sum += (y0 + y1);
    }
    
    return sum * dth / 2.0;
}

int main() 
{
    const double U = 1.0; // パラメータUを1に固定
    const std::vector<int> N_values = {10, 20, 40, 80, 160, 320}; // テストする分割数Nのリスト

    std::cout << "U = " << U << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "N\t誤差 (Error)" << std::endl;
    std::cout << "-------------------------" << std::endl;

    // 各Nについて計算を実行
    for (int N : N_values) 
    {
        // 1. 台形公式で積分値を計算
        double integral_sum = calculate_integral(N, U);

        // 2. 最終的な誤差を計算
        double final_error = integral_sum + std::exp(-U * U) - 1.0;

        // 3. 結果を出力
        std::cout << N << "\t" 
                  << std::scientific << std::setprecision(5) << final_error 
                  << std::endl;
    }

    return 0;
}