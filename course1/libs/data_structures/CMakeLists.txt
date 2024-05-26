

add_library(data_structures
        bitset/bitset.c
        ../base/base.c
        ../base/base.h
        vector/vector.c
        vector/vector.h
        vector/main.c
        vector/vectorVoid.h
        vector/vectorVoid.c
        matrix/matrix.c
        matrix/matrix.h
)

target_link_libraries(data_structures algorithms)