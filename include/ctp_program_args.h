#ifndef CTP_PROGRAMS_ARGS_H_
#define CTP_PROGRAMS_ARGS_H_

#include "ctp_base_includes.h"
#include "getopt.h"
#include <bits/getopt_ext.h>
#include <stdio.h>
#include <stdlib.h>

#define CTP_DEFAULT_HTTP_SERVER_HOST "127.0.0.1"
#define CTP_DEFAULT_HTTP_SERVER_PORT 8080
#define CTP_DEFAULT_HTTP_SERVER_PATH "."
#define CTP_DEFAULT_HTTP_SERVER_IPV6 false

typedef struct CTP_HTTP_SERVER_ARGS{
  char *host;
  char *path;
  unsigned int port;
  bool ipv6;
}CTP_HTTP_SERVER_ARGS, *PCTP_HTTP_SERVER_ARGS;

extern CTP_HTTP_SERVER_ARGS *programArgs;

static struct option long_options[] = {
    {"help", no_argument,       0, 'h'},
    {"host", required_argument, 0,  0 },
    {"port", required_argument, 0, 'p'},
    {"path", required_argument, 0, 'P'},
    {"ipv6", no_argument      , 0,  0 },
    {0, 0, 0, 0}
};

#endif
