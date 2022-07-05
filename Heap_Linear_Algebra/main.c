#include "vector.h"
#include "matrix.h"

int main(int argc, char *argv[]) {
    struct Matrix *mat = mat_new(4, 4);
    mat_scl(mat, '+', 3.0f);
    struct Matrix *mat2 = mat_new(4, 4);
    mat_scl(mat2, '-', 3.0f);
    mat_dot(mat, mat2);
    mat_out(mat);
    mat_delete(mat);
    return 0;
}
