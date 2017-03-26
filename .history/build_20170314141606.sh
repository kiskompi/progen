clear
echo "==================================="

g++ -lboost_filesystem -lboost_system -lboost_program_options -std=c++14 -std=c++11 main.cpp dirbuilder/dirbuilder.hpp FTree/FTree.hpp dirbuilder/dirbuilder.cpp FTree/FTree.cpp

echo "==================================="