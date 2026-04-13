#include "htc_arg_parser.h"
#include "htc_program_args.h"
#include "http/htc_http.h"
#include "http/htc_http_server.h"

#include <stdio.h>

extern int HTC_ERRORNO;

int main(int argc, char **argv) {
  HTC_SERVER *server;

  HTC_HTTP_SERVER_ARGS *args;

  htc_parse_args(argc, argv, &args);

  server = htc_new_http_server(args->ipv6, args->host, args->port);

  if (!server) {
    exit(-1);
  }
  
  if(listen(server->socketfd, 3) < 0) {
    fprintf(stderr, "Error while listening");
    return (EXIT_FAILURE);
  }

  while(1) {
    htc_listen_requests(server);
  }
  
  htc_close_server(server);

  return 0;
}

