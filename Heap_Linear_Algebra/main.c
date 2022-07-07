#include "vector.h"
#include "matrix.h"

int main(int argc, char *argv[]) {
    struct Matrix *mat = mat_shearing(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
    mat_out(mat);
    mat_delete(mat);
    return 0;
}
