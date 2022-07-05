#include "vec.h"

int main(int argc, char *argv[]) {
    struct Vector *vec = vec_new();
    for (int i=0; i<10; i++) {
        vec_rpush(vec, (float) i);
    }
    vec_out(vec);
    vec_cnstr(vec);
    vec_out(vec);
    vec_delete(vec);
    return 0;
}
