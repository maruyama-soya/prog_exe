#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// 被積分関数 (この関数は変更なし)
double integrand(double th, double U) 
{
    auto UC = U * std::cos(th);
    auto US = U * std::sin(th);
    auto ERF = std::erf(UC);
    auto EXP = std::exp(-US * US);
    const double COEF = M_2_SQRTPI / 4.0;
    return COEF * EXP * ERF * UC;
}

// ★★★ 変更点：シンプソン公式で積分を計算する関数 ★★★
// 引数: N (分割数、必ず偶数), U (パラメータU)
// 戻り値: 積分の近似値
double calculate_integral_simpson(int N, double U) 
{
    // Nが奇数の場合はエラー
    if (N % 2 != 0) 
    {
        std::cerr << "エラー: シンプソン公式の分割数Nは偶数である必要があります。" << std::endl;
        return 0.0;
    }

    double sum = 0.0;
    const double dth = 2.0 * M_PI / N;

    // y_0 と y_N の部分を先に足す
    sum += integrand(0.0, U);
    sum += integrand(2.0 * M_PI, U);

    // 係数が4になる奇数番目の項 (y_1, y_3, ...) を足す
    for (int i = 1; i < N; i += 2) 
    {
        sum += 4.0 * integrand(dth * i, U);
    }

    // 係数が2になる偶数番目の項 (y_2, y_4, ...) を足す
    for (int i = 2; i < N - 1; i += 2) 
    {
        sum += 2.0 * integrand(dth * i, U);
    }
    
    return sum * dth / 3.0;
}

int main() 
{
    const double U = 1.0;
    // ★★★ 変更点：テストするNの値。偶数のみを指定 ★★★
    const std::vector<int> N_values = {10, 20, 40, 80, 160, 320};

    std::cout << "U = " << U << " (シンプソン公式)" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "N\t誤差 (Error)" << std::endl;
    std::cout << "-------------------------" << std::endl;

    for (int N : N_values) 
    {
        // ★★★ 変更点：シンプソン公式の関数を呼び出す ★★★
        double integral_sum = calculate_integral_simpson(N, U);
        double final_error = integral_sum + std::exp(-U * U) - 1.0;

        std::cout << N << "\t" 
                  << std::scientific << std::setprecision(5) << final_error 
                  << std::endl;
    }

    return 0;
}