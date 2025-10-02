#pragma once
#include <iostream>
#include <string> // std::string を使うために追加

class ENGINE
{
public:
    int i;            // 回転数
    std::string name; // エンジン名

    // コンストラクタ
    ENGINE() 
    {
        i = 0;
        name = "noname-engine";
        std::cout << name << " created" << std::endl;
    }

    // print関数の宣言
    void print();
}; // ← クラス定義の最後にセミコロンを追加