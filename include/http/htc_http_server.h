#ifndef HTC_SERVER_H_
#define HTC_SERVER_H_

#include "htc_base_includes.h"

#include <stdio.h>

extern int HTC_ERRORNO;

typedef union HTC_SERVADDR_UNION {
  struct sockaddr_in6 *ipv6;
  struct sockaddr_in  *ipv4;
} HTC_SERVADDR_UNION;

typedef struct HTC_SERVER {
  int socketfd;
  
  int domain;
  int protocol;
  int type;

  HTC_SERVADDR_UNION servaddr;
  bool isIpv6;
  socklen_t servaddrlen;
}HTC_SERVER;

// Create socket with setsockopt reuse address 
HTC_SERVER *htc_new_http_server(bool ipv6, char *address, int port);

// Handle server close
void htc_close_server(HTC_SERVER *server);

#endif

