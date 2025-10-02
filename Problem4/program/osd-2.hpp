// ic_solver.hpp の修正案（以前の回答から再掲）
#include <iostream>
#include <filesystem>   //フォルダー操作
#include <fstream>      //ファイル入出力
#include <cmath>        //数学関連

class IC_Solver {
    double C=1.0;
    double Xmin=0.0;
    double Xmax=2*M_PI;

    double Ymin=1.0;
    double Zmin=0.0;
    std::filesystem::path DataFile;  //データを保存するファイル名
    // ★追加: データフォルダーのパスを保持するメンバー変数
    std::filesystem::path DataFolder; 

public:
    int N;

    IC_Solver(std::filesystem::path path) :N(100)
    {
       if (!std::filesystem::exists(path)) std::filesystem::create_directories(path);
       // ★修正: DataFolder を初期化
       DataFolder = path; // コンストラクタで受け取ったパスをメンバー変数に保存
       std::cout << "IC_Solver::Using DataFolder[" << DataFolder.string() << "]" << std::endl;
    }
    IC_Solver()
    {
       throw("何やっとんじゃぼけ〜"); // エラーメッセージも具体的にすると良い
    }

    void Solve(std::string filename)
    {
    // ★修正済み：DataFolder を使って正しく上書き
    DataFile = DataFolder / filename;  // ← これが正解！

    std::cout << "IC_Solver::Using DataFile[" << DataFile.string() << "]" << std::endl;
    std::ofstream ofs(DataFile);      // 出力ファイルを書き出し用に準備

    double dx = Xmax / N;             // 区間幅
    double y = Ymin, z = Zmin;        // 初期値
    for (int i = 0; i < N; i++) 
    {
        y = y + z * dx;
        z = z - C * y * dx;
        ofs << dx * (i + 1) << " " << y << std::endl;
    }
    ofs.close();  // 出力ファイルを閉じる
}
    // もし main.cpp で ode.solve(); (引数なし) を呼び出したいなら、
    // 以下のようなオーバーロードも ic_solver.hpp に追加できます
    // void Solve(){
    //     Solve("tako_hati.dat"); // デフォルトのファイル名で呼び出す
    // }
};