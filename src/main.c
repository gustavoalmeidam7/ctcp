#include "ctp_arg_parser.h"
#include "ctp_program_args.h"
#include "http/ctp_http.h"
#include "ctp_server.h"

#include <stdio.h>

extern int CTP_ERRORNO;

int main(int argc, char **argv) {
  PCTP_SERVER server;

   CTP_HTTP_SERVER_ARGS *args;

  ctp_parse_args(argc, argv, &args);

  server = create_server(args->ipv6, args->host, args->port);

  if (!server) {
    exit(-1);
  }
  
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

