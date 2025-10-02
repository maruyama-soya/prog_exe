#include <iostream>  // 入出力機能を使う
#include "ode_euler.hpp" // 自分で作ったクラス定義 (設計図) を使う

int main() 
{
    std::cout << "Hello, World!" << std::endl; // 画面に文字を表示

    ODE_Euler solver(1.0, 0.0, 0.02); // オイラー法で計算するオブジェクトを作るß
    solver.solve();             // ODE_Euler クラスの solve メソッドを呼び出して計算を実行
    std::cout << "Finished!" << std::endl; // 計算が終わったことを表示
    return 0;                    // プログラムを正常終了させる
}