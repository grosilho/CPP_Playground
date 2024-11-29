#include <Matrices/RG/RG.hpp>
#include <iostream>

int main()
{
    using namespace LinAlg::Matrices::RG;
    Matrixd m1 = Zero<double>(3, 3);
    Matrixd m2 = Constant<double>(3, 3, 1.);
    Matrixd m3 = Identity<double>(3);

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;
}
