#include <LinAlg/Matrix/Matrix.hpp>
#include <iostream>

int main()
{
    [[maybe_unused]] LinAlg::Matrix<double> m(3, 3);
    std::cout << "Compilation test passed" << std::endl;
}
