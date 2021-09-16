#include <stdio.h>
#include <winsock.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")

// The purpose of this program is to serve a requested file to the client
int main(void) {
	WSADATA wsa;
	SOCKET listen_socket, client_socket;
	struct sockaddr_in server_address;
	char recvbuf[512];
	char file_data[512];
	int buflen=512, file_name, sent_data, filedescriptor;
	FILE *file_ptr;

	WSAStartup(MAKEWORD(2,2),&wsa);
	printf("WSAStartup done\n");

	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	printf("Socket Created\n");

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons( 27015 );

	bind(listen_socket, (struct sockaddr*)&server_address, sizeof(server_address));
	printf("Socket bound\n");

	listen(listen_socket, 0);
	client_socket = accept(listen_socket, NULL, NULL);
	printf("Client connected\n");

	file_name = recv(client_socket, recvbuf, buflen, 0);
	filedescriptor = open(recvbuf, O_RDONLY);
	printf("File requested: %s\n", recvbuf);
	
	// Open and iterate through requested file here
	
	if (file_name > 0) {
		while (read(filedescriptor, file_data, 511) > 0) {
				printf("DATA SENT: %s", file_data);
				send(client_socket, file_data, (int)strlen(file_data), 0);
				shutdown(client_socket, SD_SEND);
		}
	} 

	printf("Connection closed\n");
	closesocket(client_socket);
	closesocket(listen_socket);
	WSACleanup();
	return 0;
}
