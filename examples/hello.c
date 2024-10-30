#include <stdio.h>
#include "tagfs/core.h"

int main() {
    printf("TagFS Core Library Version: %s\n", tagfs_get_version());
    return 0;
}