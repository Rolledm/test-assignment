#include "t1.h"

#include <iostream>

namespace Utilities {

    std::string bin(int num) {
        bool isNegative = false;
        if (num < 0) {
            num *= -1;
            isNegative = true;
        }
        
        int bitsNumber = 1;
        int max = 1;
        while (max <= num) {
            bitsNumber++;
            max <<= 1;
        }

        int maxBitsNumber = 8;
        while (bitsNumber > maxBitsNumber) {
            maxBitsNumber <<= 1;
        }

        std::string s;
        s.reserve(maxBitsNumber);
        
        for (int i = 0; i < maxBitsNumber - bitsNumber + 1; i++) {
            s += isNegative ? '1' : '0';
        }

        max >>= 1;
        while (num > 0) {
            if (num >= max) {
                s += (isNegative ? '0' : '1');
                num -= max;
            } else {
                s += (isNegative ? '1' : '0');
            }
            max >>= 1;
            bitsNumber--;
        }

        for (int i = 0; i < bitsNumber - 1; i++) {
            s += isNegative ? '1' : '0';
        }
        return s;
    }

}