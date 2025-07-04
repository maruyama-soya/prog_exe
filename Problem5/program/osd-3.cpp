#include "osd-3.hpp" // 作成したヘッダーファイルをインクルード
#include <iostream>      // std::cout を使うため
#include <limits> // std::numeric_limits を使うため

//何でやクソ野郎！！！

int main() {
    // BC_Solver クラスのオブジェクトを作成
    BC_Solver solver;

    // パラメータと境界条件を設定
    solver.Y0 = 1.0;
    solver.Y1 = 0.0;

    // C の値をコンソールから入力
    std::cout << "Enter the value for C: ";
    std::cin >> solver.C;

    // N の値をコンソールから入力
    std::cout << "Enter the value for N: ";
    std::cin >> solver.N;

    // 入力エラーチェック（オプションだが推奨）
    if (std::cin.fail() || solver.N <= 0) {
        std::cerr << "Invalid input for C or N. Please enter valid numbers." << std::endl;
        return 1; // エラー終了
    }

    std::cout << "Solving boundary value problem with C=" << solver.C << " and N=" << solver.N << "..." << std::endl;

    // 問題を解く
    solver.Solve();

    // 結果をファイルに保存
    // 保存先のパスを適宜変更してください
    // macOS/Linux 環境を想定しています。Windowsの場合、getenv("HOME")はOneDriveパスを返さない可能性があります。
    std::filesystem::path myPath=getenv("HOME");
    // OneDriveのパスは環境依存なので、安全策としてプログラムの実行ディレクトリに保存
    // もし特定のパスに保存したい場合は、上記の myPath を適切に設定してください
    myPath/= "OneDrive - Kyoto University/M1前期/プログラミング演習/prog_exe/Problem5/data"; // m直接パスを指定
    
    // 今回の例ではカレントディレクトリに "solution.dat" を保存
    myPath /= "solution.dat"; 
    
    // BC_SolverクラスのSaveメソッドがstd::filesystem::pathを受け取るため、直接outputPathを渡します。
    // myPath はここでは直接使われませんが、もし特定のディレクトリに保存したい場合は
    // outputPath = myPath / "solution.dat"; のように変更できます。
    solver.Save(myPath);

    std::cout << "Solution saved to " << myPath.string() << std::endl;

    return 0;
}