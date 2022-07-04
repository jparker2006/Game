#include "vec.h"

int main(int argc, char *argv[]) {
    struct Vector *vec = (struct Vector *) malloc(sizeof(struct Vector));
    vector_new(vec);
    for (int i=0; i<10; i++) {
        vector_rpush(vec, (float) i);
    }
    for (int i=0; i<6; i++) {
        vector_rpop(vec);
    }
    vector_print(vec);
    vector_free(vec);
    return 0;
}
