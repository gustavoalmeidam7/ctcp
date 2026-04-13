#ifndef SERVER_H_
#define SERVER_H_

#include "ctp_base_includes.h"

#include <stdio.h>

typedef union CTP_SERVADDR_UNION {
  struct sockaddr_in6 *ipv6;
  struct sockaddr_in  *ipv4;
} CTP_SERVADDR_UNION;

typedef struct CTP_SERVER {
  int socketfd;
  
  int domain;
  int protocol;
  int type;

  CTP_SERVADDR_UNION servaddr;
  bool isIpv6;
  socklen_t servaddrlen;
}CTP_SERVER, *PCTP_SERVER;

extern int CTP_ERRORNO;

// Create socket with setsockopt reuse address 
CTP_SERVER *create_server(bool ipv6, char *address, int port);

#endif

