#include <iomanip> // 出力フォーマットのため
#include "intde.hpp" // 多重指数変換自動積分プログラムのヘッダーファイル
#include <iostream>

int main() {

   IntDE myIntegrator; // IntDEクラスのインスタンスを作成
   size_t count=0; // 関数呼び出し回数をカウントする変数
   double err,err_req=1e-6; // err: 実際の誤差, err_req: 要求する誤差 (10^-6)

   myIntegrator.Initialize(err_req); // IntDEオブジェクトを初期化し、要求精度を設定

   // 積分を実行
   auto v = myIntegrator.Integrate([&count](double x, void *param) 
   {
       count++; // 関数が呼ばれるたびにカウントを増やす
       return 1.0 / std::sqrt(x * (1.0 - x)); // 積分対象の関数
    }, 0.0, 1.0, err); // 積分区間 [0.0, 1.0] と誤差を格納する変数err

   // 結果を出力
   std::cout << "Integral value: " << std::setprecision(12) << v << ", Error: " << err << " requested: " << err_req << " by " << count << " steps"<< std::endl;

   return 0;
}