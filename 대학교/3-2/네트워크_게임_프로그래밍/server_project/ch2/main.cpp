#include "../Common.h"
#include <iostream>

int main(int argc, char* argv[])
{
	BYTE low = 2; // 0x02
	BYTE high = 2; // 0x02

	WORD version = (WORD)high << 8 | low; // 왼쪽으로 두칸 밀어주고

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(version, &wsa) != 0)
		return 1;
	printf("[알림] 윈속 초기화 성공\n");

	std::cout << "wVersion : " << std::hex << wsa.wVersion << std::endl;
	std::cout << "wHighVersion : " << wsa.wHighVersion << std::endl;
	std::cout << "szDescription : " << std::dec << wsa.szDescription << std::endl;
	std::cout << "szSystemStatus : " << wsa.szSystemStatus << std::endl;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[알림] 소켓 생성 성공\n");

	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}