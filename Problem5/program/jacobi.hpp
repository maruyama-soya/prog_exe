#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Eigen/Dense>
#include <unordered_set>
#include <iomanip> // std::setprecision を使うために追加

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

    std::unordered_set<size_t> SaveTimes;
    std::filesystem::path intermediate_filename;

    Jacobi() 
    {
        std::cout << "Jacobi solver initialized." << std::endl;
        SaveTimes.clear();
        intermediate_filename = "intermediate_results.txt";
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

    // ★★★ 変更点1：引数にログファイルパスを追加 (デフォルトは空) ★★★
    bool Solver(size_t max_iter = 10000, const std::filesystem::path& logname = "") 
    {
        size_t message_iter = 1000;
        double tol = 1e-10;
        Eigen::VectorXd x_old(myVEC.size());
        Eigen::VectorXd x_new(myVEC.size());
        x_old.setZero();

        std::ofstream ofs_intermediate(intermediate_filename);
        
        // ★★★ 追加：ログファイル用のストリームを定義 ★★★
        std::ofstream lout;
        // ログファイル名が指定されていれば、ファイルを開く
        if (!logname.empty()) 
        {
            std::filesystem::create_directories(logname.parent_path());
            lout.open(logname);
        }

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

            // ★★★ 追加：ここからが新しいロジック ★★★
            // loutがファイルを開いている場合（ログを取る場合）
            if (lout.is_open()) 
            {
                double sum_sq = 0.0;
                double prev_y = Y0; // 最初の点は左端の境界条件
                // 内部点の積分
                for (int i = 0; i < x_new.size(); ++i) 
                {
                    double current_y = x_new(i);
                    sum_sq += (prev_y * prev_y + current_y * current_y);
                    prev_y = current_y;
                }
                // 最後のセグメント（最後の内部点と右端の境界）の積分
                sum_sq += (prev_y * prev_y + Y1 * Y1);

                sum_sq *= (dx / 2.0);
                
                // ログファイルに「反復回数 ノルム」を書き出す
                lout << iter << " " << std::fixed << std::setprecision(15) << std::sqrt(sum_sq) << std::endl;
            }
            // ★★★ 追加：ここまで ★★★

            err = (x_new - x_old).norm();
            if (err < tol) break;
            
            x_old = x_new;

            if (iter % message_iter == 0) 
            {
                std::cout << " Iteration " << iter << " : Error = " << err << std::endl;
            }

            if (SaveTimes.count(iter)) 
            {
                std::cout << " -> Saving intermediate result at iteration " << iter << std::endl;
                ofs_intermediate << std::endl << "# iter = " << iter << std::endl;
                ofs_intermediate << Xmin << " " << Y0 << std::endl;
                for(size_t i=0; i < x_new.size(); ++i) 
                {
                    ofs_intermediate << (i+1)*dx << " " << x_new[i] << std::endl;
                }
                ofs_intermediate << Xmax << " " << Y1 << std::endl;
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

        return iter < max_iter;
    }

    void Save(const std::filesystem::path& filename) const 
    {
        std::ofstream ofs(filename);
        if (!ofs) 
        {
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