//server:
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#define PORT 8000
#define MAX_SIZE 100
int main()
{
char k1[MAX_SIZE];
char k2[MAX_SIZE];
int kfd, ret_val;
int n;
socklen_t addr_len;
struct sockaddr_in kaddr;
kfd = socket(AF_INET, SOCK_DGRAM, 0);
kfd = socket(AF_INET, SOCK_STREAM, 0);
memset(&kaddr, 0, sizeof(kaddr));
kaddr.sin_family = AF_INET;
kaddr.sin_addr.s_addr = htonl(INADDR_ANY);
kaddr.sin_port = htons(PORT);
connect(kfd, (struct sockaddr *)&kaddr, sizeof(kaddr));
while (1)
{
printf("Enter message for server: \n");
fgets(k1, MAX_SIZE, stdin);
if (k1[0] == '#')
break;
n = strlen(k1) + 1;
send(kfd, k1, n, 0);n = recv(kfd, k2, MAX_SIZE, 0);
printf("recived msg form server:%s\n", k2);
}
return 0;
}
