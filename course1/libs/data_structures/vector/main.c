#include "vectorVoid.h"
#include "vector.h"
#include <stdio.h>

int main()
{
    vector t = createVector((size_t)4);
    free(t.data);
    return 0;
}
