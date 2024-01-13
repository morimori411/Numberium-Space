#include "Common.h"

int64_t common::dist(int32_t x1, int32_t y1, int32_t x2, int32_t y2){
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}