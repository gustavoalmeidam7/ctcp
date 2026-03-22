#include "ctp_server.h"

#include <sys/socket.h>
#include <stdbool.h>

int CTP_ERRORNO = 0;

static void handle_error(unsigned short int error_code, const char *log_statment) {
  CTP_ERRORNO= error_code;
  // Change to a log proper log function
  fprintf(stderr, "%s", log_statment);
}

CTP_SERVER *create_server(bool ipv6, char *address, int port){
  CTP_SERVER *serverfd = malloc(sizeof(CTP_SERVER));
  struct sockaddr_in *servaddr = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
  socklen_t servaddrlen = sizeof(struct sockaddr_in);
  int opt = 1;

  if(!serverfd) {
    handle_error(1, "Error alocating serverfd: ctp_server.c\n");
    return NULL;
  }

  if(!servaddr) {
    handle_error(1, "Error alocating servaddr: ctp_server.c\n");
    return NULL;
  }

  serverfd->domain      = (ipv6) ? AF_INET6 : AF_INET;
  serverfd->protocol    = 0;
  serverfd->type        = SOCK_STREAM;
  serverfd->servaddr    = servaddr;
  serverfd->servaddrlen = servaddrlen;
 
  serverfd->socketfd    = socket(
    serverfd->domain,
    serverfd->type,
    serverfd->protocol
  );

  memset(servaddr, 0, sizeof(struct sockaddr_in));

  servaddr->sin_addr.s_addr = inet_addr(address);
  servaddr->sin_port        = htons(port);
  servaddr->sin_family      = serverfd->domain;
  
  if(
    setsockopt(
      serverfd->socketfd,
      SOL_SOCKET,
      SO_REUSEADDR,
      &opt,
      sizeof(opt)
    ) < 0) {
      handle_error(2, "Error binding socket on: ctp_server\n");
      return NULL;
  }

  if(
  bind(
    serverfd->socketfd, 
    (struct sockaddr *) servaddr, 
    sizeof(struct sockaddr_in)
  ) < 0) {
      handle_error(3, "Error binding socket on: ctp_server\n");
      return NULL;
  }

  return serverfd;
}

