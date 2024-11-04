#include <cassert>

import LinAlg;

int
matrix_size (int, char **)
{
    LinAlg::Matrix<double> m (3, 4);
    assert (m.rows () == 3 && m.cols () == 4);
    assert (m.size ().first == 3);
    assert (m.size ().second == 4);

    return 0;
}
