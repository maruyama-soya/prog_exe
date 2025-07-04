#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Eigen/Dense>
#include <unordered_set> // ★追加: unordered_set を使うために必要

class Jacobi 
{
private:
    Eigen::MatrixXd myMAT;
    Eigen::VectorXd myVEC;
    Eigen::VectorXd mySOL;
public:
    double Xmin = 0.0, Xmax = 1.0;
    double Y0 = 1.0, Y1 = 0.0;
    double C = 1.0;
    double dx, err;

    // ★追加: 途中経過を保存するためのメンバ変数
    std::unordered_set<size_t> SaveTimes;
    std::filesystem::path intermediate_filename;

    Jacobi() 
    {
        std::cout << "Jacobi solver initialized." << std::endl;
        // ★追加: コンストラクタでメンバ変数を初期化しておく
        SaveTimes.clear();
        intermediate_filename = "intermediate_results.txt"; // デフォルトのファイル名
    }

    void resize(size_t n) 
    {
        if (n <= 1) 
        {
            throw std::invalid_argument("N must be greater than 1.");
        }
        myMAT.resize(n-1, n-1);
        myMAT.setZero();
        myVEC.resize(n-1);
        myVEC.setZero();
        mySOL.resize(n);
        mySOL.setZero();
    }

    void Init() 
    {
        dx = (Xmax - Xmin) / (mySOL.size() - 1);
        
        for (int i = 0; i < myMAT.rows(); ++i) 
        {
            myMAT(i, i) = 2.0 - C * dx * dx;
            if (i > 0) myMAT(i, i - 1) = -1.0; 
            if (i < myMAT.rows() - 1) myMAT(i, i + 1) = -1.0; 
        }

        myVEC(0) += Y0;
        myVEC(myVEC.size() - 1) += Y1;

        mySOL(0) = Y0;
        mySOL(mySOL.size() - 1) = Y1;
    }

    void Inv() 
    {
        auto SOL = myMAT.inverse() * myVEC; 
        for(int i=0; i < SOL.size(); ++i) 
        {
            mySOL(i+1) = SOL(i);
        }
    }

    // ★変更: 戻り値の型を void から bool に変更
    bool Solver(size_t max_iter = 20000) 
    {
        size_t message_iter = 1000;
        double tol = 1e-4;
        Eigen::VectorXd x_old(myVEC.size());
        Eigen::VectorXd x_new(myVEC.size());
        x_old.setZero();

        // ★追加: 途中経過を保存するためのファイルストリームを最初に開く
        // これにより、すべての途中経過が同じファイルに追記される
        std::filesystem::create_directories(intermediate_filename.parent_path());
        std::ofstream ofs(intermediate_filename);

        size_t iter = 0;
        while (iter < max_iter) 
        {
            iter++;
            for (int i = 0; i < myMAT.rows(); ++i) 
            {
                double sigma = 0.0;
                for (int j = 0; j < myMAT.cols(); ++j) 
                {
                    if (j != i) 
                    {
                        sigma += myMAT(i, j) * x_old(j);
                    }
                }
                x_new(i) = (myVEC(i) - sigma) / myMAT(i, i);
            }
            err = (x_new - x_old).norm();
            if (err < tol) break;
            
            x_old = x_new;
            if (iter % message_iter == 0) 
            {
                std::cout << " Iteration " << iter << " : Error = " << err << std::endl;
            }

            // ★追加: 指定された回数に到達したら、ファイルに書き出す
            if (SaveTimes.count(iter)) { // .count() は .contains() と同じ機能(C++20以前でも使える)
                std::cout << " -> Saving intermediate result at iteration " << iter << std::endl;
                ofs << std::endl << "# iter = " << iter << std::endl;
                ofs << Xmin << " " << Y0 << std::endl;
                for(size_t i=0; i < x_new.size(); ++i) 
                {
                    ofs << (i+1)*dx << " " << x_new[i] << std::endl;
                }
                ofs << Xmax << " " << Y1 << std::endl;
            }
        }
        
        if (iter >= max_iter) 
        {
            std::cout << "Timeout. Error= " << err << std::endl;
        } else {
            std::cout << "Converged in " << iter << " iterations." << std::endl;
        }
        
        for (int i = 0; i < myMAT.rows(); ++i) 
        {
            mySOL(i + 1) = x_new(i);
        }

        // ★変更: 収束したか(true)タイムアウトしたか(false)を返す
        return iter < max_iter;
    }

    void Save(const std::filesystem::path& filename) const 
    {
        std::ofstream ofs(filename);
        if (!ofs) {
            std::cerr << "Error: Could not open file "<< filename << std::endl;
            return;
        }
        for (int i = 0; i < mySOL.size(); ++i) 
        {
            ofs << i * dx << " " << mySOL(i) << std::endl;
        }
        std::cout << "Final solution saved to " << filename << std::endl;
    }
};