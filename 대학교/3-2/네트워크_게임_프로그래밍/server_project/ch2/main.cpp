#include "../Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
	BYTE low = 2; // 0x02
	BYTE high = 2; // 0x02

	WORD version = (WORD)high << 8 | low; // �������� ��ĭ �о��ְ�

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(version, &wsa) != 0)
		return 1;
	printf("[�˸�] ���� �ʱ�ȭ ����\n");

	std::cout << "wVersion : " << std::hex << wsa.wVersion << std::endl;
	std::cout << "wHighVersion : " << wsa.wHighVersion << std::endl;
	std::cout << "szDescription : " << std::dec << wsa.szDescription << std::endl;
	std::cout << "szSystemStatus : " << wsa.szSystemStatus << std::endl;

	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[�˸�] ���� ���� ����\n");

	// ���� �ݱ�
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}