#include "t2.h"
#include <cstring>

namespace Utilities {

    void RemoveDups(char* str) {
        size_t size = strlen(str);
        if (size <= 1) {
            return;
        }

        size_t idx = 1;
        for (size_t i = 1; i < size; i++) {
            if (str[i] != str[idx - 1]) {
                str[idx++] = str[i];
            }
        }
        str[idx] = '\0';
    }

}