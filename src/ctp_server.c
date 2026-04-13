#include "ctp_server.h"
#include <netinet/in.h>

int CTP_ERRORNO = 0;

static void handle_error(unsigned short int error_code, const char *log_statment) {
  CTP_ERRORNO= error_code;
  // Change to a log proper log function
  fprintf(stderr, "%s", log_statment);
}

CTP_SERVER *create_server(bool ipv6, char *address, int port){
  CTP_SERVER *serverfd;

  if (ipv6) {
    #define CTP_IPV6
  }
  
  #ifdef CTP_IPV6
  struct sockaddr_in6 *servaddr;
  #define CTP_SOCKADDR sockaddr_in6
  #else
  struct sockaddr_in *servaddr;
  #define CTP_SOCKADDR sockaddr_in
  #endif
  
  socklen_t servaddrlen;
  int opt = 1;

  serverfd = malloc(sizeof(CTP_SERVER));
  servaddr = (struct CTP_SOCKADDR*) malloc(sizeof(struct CTP_SOCKADDR));
  servaddrlen = sizeof(struct sockaddr_in);

  bool isServerInitialized = serverfd && servaddr;
     
  if(!isServerInitialized) {
    handle_error(1, "Error alocating the server\n");

    free(serverfd);
    free(servaddr);
    
    return NULL;
  }
  
  serverfd->domain      = (ipv6) ? AF_INET6 : AF_INET;
  serverfd->protocol    = 0;
  serverfd->type        = SOCK_STREAM;
  serverfd->servaddrlen = servaddrlen;
  
  #ifdef CTP_IPV6
    serverfd->servaddr.ipv6 = servaddr;
  #else
    serverfd->servaddr.ipv4 = servaddr;
  #endif
 
  serverfd->socketfd    = socket(
    serverfd->domain,
    serverfd->type,
    serverfd->protocol
  );

  memset(servaddr, 0, sizeof(struct CTP_SOCKADDR));

  #ifdef CTP_IPV6
  inet_pton(serverfd->domain, address, &(servaddr->sin6_addr));
  servaddr->sin6_port        = htons(port);
  servaddr->sin6_family      = serverfd->domain;
  #else
  inet_pton(serverfd->domain, address, &(servaddr->sin_addr));
  servaddr->sin_port        = htons(port);
  servaddr->sin_family      = serverfd->domain;
  #endif
  
  bool isSocketWorking = setsockopt(serverfd->socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == 0;

  bool isBinded = bind(serverfd->socketfd,(struct sockaddr *) servaddr, sizeof(struct CTP_SOCKADDR)) == 0;
  
  if(!isSocketWorking && !isBinded) {
      handle_error(3, "Error binding socket\n");
      return NULL;
  }

  return serverfd;
}

