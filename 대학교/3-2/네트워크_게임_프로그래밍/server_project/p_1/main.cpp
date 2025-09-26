#include "../Common.h"
#include <iostream>

const char* CheckEndian()
{
    unsigned int x = 0x12345678;      // ������ ����
    unsigned char* p = (unsigned char*)&x;

    if (*p == 0x78)
        return "Little Endian";
    else
        return "Big Endian";
}

int main(void)
{
    printf("[�˸�] ���� ȣ��Ʈ�� ����Ʈ ���� ����� %s �Դϴ�.\n", CheckEndian());
    return 0;
}
