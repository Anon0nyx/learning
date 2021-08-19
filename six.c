#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Winsock library

int main(void) {
	WSADATA wsa;
	SOCKET listen_socket;
	struct sockaddr_in server_address;

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
		printf("Failed. Error Code: %d", WSAGetLastError());
		return 1;
	}
	printf("WSAStartup successful\n");

	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_socket == INVALID_SOCKET) {
		printf("Socket failed to be created");
		return 1;
	}
	printf("Socket created successfully\n");

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(27015);
	
	int foo;
	foo = bind(listen_socket, (struct sockaddr*)&server_address, sizeof(server_address));
	if (foo == SOCKET_ERROR) {
		printf("Bind failed");
		closesocket(listen_socket);
		return 1;
	}
	printf("Socket bound successfully\n");

	listen(listen_socket, 0);
	printf("Waiting for client to connect\n");
	SOCKET conn_sock = accept(listen_socket, NULL, NULL);
	if (conn_sock == INVALID_SOCKET) {
		printf("Accept failed");
		return 1;
	} else 
		printf("Client connected\n");
	
	// Variables for data receiving
	char recvbuf[512];
	int data, sent_data;
	int recvbuflen = 512;
	do {
		data = recv(conn_sock, recvbuf, recvbuflen, 0);
		if (data > 0) {
			printf("Bytes received: %d\n", data);

			// Ech this buffer back to the sender
			char sendbuf[512] = "Hello, Friend. - Server";
			sent_data = send(conn_sock, sendbuf, data, 0);
			if (sent_data == SOCKET_ERROR) {
				printf("Send failed: %d\n", WSAGetLastError());
				closesocket(conn_sock);	
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", sent_data);
		} else if (data == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(conn_sock);
			WSACleanup();
			return 1;
		}
	} while (data > 0);	
	
	printf("DATA RECEIVED FROM CLIENT: %s\n", recvbuf);
	
	closesocket(conn_sock);
	closesocket(listen_socket);
	WSACleanup();
	printf("WSACleanup finshed");

	return 0;
}
