#ifndef SERVER_H_
#define SERVER_H_

#include "ctp_base_includes.h"

#include "stdbool.h"

typedef struct CTP_SERVER {
  int socketfd;
  
  int domain;
  int protocol;
  int type;

  struct sockaddr_in *servaddr;
  socklen_t servaddrlen;
}CTP_SERVER, *PCTP_SERVER;

extern int CTP_ERRORNO;

// Create socket with setsockopt reuse address 
CTP_SERVER *create_server(bool ipv6, char *address, int port);

#endif

