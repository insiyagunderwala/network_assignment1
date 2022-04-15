//client:
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#define PORT 8000
#define MAXSZ 100
char* toggle(char s1[]){
char* ret_str=s1;
for(int i=0; i<strlen(s1); i++){
if(ret_str[i]>='A' && ret_str[i]<='Z')
ret_str[i]=ret_str[i]+32;
else if(ret_str[i]>='a' && ret_str[i]<='z')
ret_str[i]=ret_str[i]-32;
}
return ret_str;
}int main(){
int kfd, newkfd, n;
char msg[MAXSZ];
int clientAddrLen;
socklen_t client;
struct sockaddr_in cc_addr, kaddr;
char buf[10000];
kfd = socket(AF_INET, SOCK_STREAM, 0); int opt = 1;
if(setsockopt(kfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
{
perror("setsocket");
exit(EXIT_FAILURE);
} memset(&kaddr, 0, sizeof(kaddr));
kaddr.sin_family = AF_INET;
kaddr.sin_addr.s_addr = htonl(INADDR_ANY);
kaddr.sin_port = htons(PORT); bind(kfd, (struct sockaddr *)&kaddr, sizeof(kaddr));
printf("socket bound to port 8000\n");
listen(kfd, 5); while (1){
clientAddrLen = sizeof(cc_addr);
newkfd = accept(kfd, (struct sockaddr *)&cc_addr, &clientAddrLen);
while (1){
int n;
n = recv(newkfd, msg, MAXSZ, 0);
if (n == 0){
close(newkfd);
break;
}
msg[n] = 0;
printf("message recieved from the client: %s\n", msg);
char *toggled = toggle(msg);
send(newkfd, msg, n, 0);
}
}
return 0;
}
