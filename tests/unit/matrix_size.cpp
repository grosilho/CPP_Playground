#include <LinAlg/LinAlg.hpp>
#include <cassert>
int
matrix_size (int, char **)
{
    LinAlg::Matrix m (3, 4);
    assert (m.rows () == 3 && m.cols () == 4);
    assert (m.size ().first == 3);
    assert (m.size ().second == 4);

    return 0;
}
