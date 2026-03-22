#include "ctp_arg_parser.h"
#include "http/ctp_http.h"
#include "ctp_server.h"

#include <stdio.h>

extern int CTP_ERRORNO;

int main(int argc, char **argv) {
  PCTP_SERVER server;

  ctp_parse_args(argc, argv);

  server = create_server(AF_INET, SOCK_STREAM, 0, programArgs->host, programArgs->port);
  
  if(listen(server->socketfd, 3) < 0) {
    fprintf(stderr, "Error while listening");
    return (EXIT_FAILURE);
  }

  while(1) {
    ctp_listen_requests(server);
  }
  
  close(server->socketfd);

  return 0;
}

