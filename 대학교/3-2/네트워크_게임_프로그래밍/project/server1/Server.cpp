#include <winsock2.h>

#define SERVERPORT 9000
#define BUFSIZE 512
int main() {
	int retval;
	
	//扩加 檬扁拳
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 1;
	}

	//家南 积己
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

}