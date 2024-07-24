#include    <iostream>
#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<netinet/in.h>
#include    "error.h"
#include	<unistd.h>
#include	<string.h>
#include    <arpa/inet.h>

#define	bzero(ptr,n)		memset(ptr, 0, n)

#define	SA	struct sockaddr

int inet_pton(int family, const char *strptr, void *addrptr);
int inet_aton(const char *cp, struct in_addr *ap);

int main(int argc, char **argv){
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    if( argc != 2){err_quit("usage : a.out <IPaddress>"); }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){err_sys("sock error");}
    else std::cout<<"Sock : OK"<<std::endl;

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(123);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sockfd, (SA*)&servaddr,sizeof(servaddr)) < 0) err_sys("connect error");
    else std::cout<<"connect : OK"<<std::endl;

    while((n = read(sockfd,recvline, MAXLINE)) > 0){
        recvline[n] = 0; // завершающий нуль
        if(fputs(recvline,stdout) == EOF) err_sys("fputs error");
        else std::cout<<"fputs : OK"<<std::endl;
        
    }
    if(n < 0) err_sys("read error");
    else std::cout<<"read : OK"<<std::endl;


    exit(0);
}

int inet_pton(int family, const char *strptr, void *addrptr){
    if (family == AF_INET) {
    	struct in_addr  in_val;

        if (inet_aton(strptr, &in_val)) {
            memcpy(addrptr, &in_val, sizeof(struct in_addr));
            return (1);
        }
		return(0);
    }
	errno = EAFNOSUPPORT;
    return (-1);
}
int inet_aton(const char *cp, struct in_addr *ap){
    int dots = 0;
    u_long acc = 0, addr = 0;

    do {
	char cc = *cp;

	switch (cc) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	    acc = acc * 10 + (cc - '0');
	    break;

	case '.':
	    if (++dots > 3) {
		return 0;
	    }
	    /* Fall through */

	case '\0':
	    if (acc > 255) {
		return 0;
	    }
	    addr = addr << 8 | acc;
	    acc = 0;
	    break;

	default:
	    return 0;
	}
    } while (*cp++) ;

    /* Normalize the address */
    if (dots < 3) {
	addr <<= 8 * (3 - dots) ;
    }

    /* Store it if requested */
    if (ap) {
	ap->s_addr = htonl(addr);
    }

    return 1;    
}