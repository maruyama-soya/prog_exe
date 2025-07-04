// OSD-2.cpp の修正
#include <iostream>
#include <filesystem>
#include "osd-2.hpp"

int main(){
    std::filesystem::path myPath=getenv("HOME");
    myPath/= "OneDrive - Kyoto University/M1前期/プログラミング演習/prog_exe/Problem4/data";
    std::cout << "Using Folder[" << myPath << "]" << std::endl;
    IC_Solver ode(myPath);
    ode.N=10000;
    ode.Solve("C1N10000.dat");
    ode.N=1000;
    ode.Solve("C1N1000.dat");
    ode.N=100;
    ode.Solve("C1N100.dat");
    ode.N=10;
    ode.Solve("C1N10.dat");
    ode.N=5;
    ode.Solve("C1N5.dat");
    ode.N=3;
    ode.Solve("C1N3.dat");
    
    return 0;
}