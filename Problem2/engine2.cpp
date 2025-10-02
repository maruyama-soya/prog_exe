#include "engine.hpp"

void ENGINE::print()
{
    std::cout << name << "の回転数は" << i << std::endl;
}

int main()
{
    // ENGINEクラスのオブジェクトを作成
    ENGINE e1;
    e1.name = "V8エンジン";
    e1.i = 3000;

    // print関数を呼び出す
    e1.print();

    return 0;
}