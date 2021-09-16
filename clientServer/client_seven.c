#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(void) {
	WSADATA wsa;
	SOCKET sock;
	struct sockaddr_in server;
	int recvbuflen = 512, result;
	char *sendbuf = "C:\\Users\\dtf82\\OneDrive\\Documents\\school\\tools\\starter_code\\learning\\testfile.txt";
	char recvbuf[512] = "";

	WSAStartup(MAKEWORD(2,2),&wsa);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons( 27015 );
	server.sin_family = AF_INET;

	result = connect(sock, (struct sockaddr*)&server, sizeof(server));

	send(sock, sendbuf, (int)strlen(sendbuf), 0);
	shutdown(sock, SD_SEND);

	printf("File requested: %s\n", sendbuf);
	result = shutdown(sock, SD_SEND);

	// For now print the incoming file to the screen
	// Next step will be to print it to a new file,
	// thus fully downloading the file locally
	do {
		result = recv(sock, recvbuf, recvbuflen, 0);
		if (result > 0)
			printf("%s", recvbuf);
		else if (result == 0)
			printf("Connection Closed");
		else
			printf("File failed to download");
	} while (result > 0);
	/*
	while ((result = recv(sock, recvbuf, recvbuflen, 0)) >= 0) {
		printf("DATA RECEIVED: %s", recvbuf);
	}
	*/
	closesocket(sock);
	WSACleanup();
	return 0;
}
