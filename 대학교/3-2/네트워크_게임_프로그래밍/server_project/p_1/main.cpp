#include "../Common.h"
#include <iostream>

const char* CheckEndian()
{
    unsigned int x = 0x12345678;      // 임의의 정수
    unsigned char* p = (unsigned char*)&x;

    if (*p == 0x78)
        return "Little Endian";
    else
        return "Big Endian";
}

int main(void)
{
    printf("[알림] 현재 호스트의 바이트 정렬 방식은 %s 입니다.\n", CheckEndian());
    return 0;
}
