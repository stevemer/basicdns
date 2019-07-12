#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 53

int main(int argc, char const * argv[]) {
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  const char * hello = "Hello from client";
  char buffer[1024] = {0};

  // Creating socket file descriptor.
	// http://man7.org/linux/man-pages/man2/socket.2.html
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Cribbed shamelessly from the internet.
  // Convert IPv4 and IPv6 addresses from text to binary form.
  if (inet_pton(AF_INET, "127.0.0.1", & serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

	// Attempt to connect to the server.
  if (connect(sock, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }

	// Send a simple message.
	// TODO(stevemerritt): Whatever use cases we need beyond this.
  send(sock, hello, strlen(hello), 0);
  printf("Hello message sent\n");
  valread = read(sock, buffer, 1024);
  printf("%s\n", buffer);
  return 0;
}
