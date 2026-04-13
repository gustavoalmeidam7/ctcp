#ifndef HTC_PROGRAMS_ARGS_H_
#define HTC_PROGRAMS_ARGS_H_

#include "htc_base_includes.h"
#include "getopt.h"
#include <bits/getopt_ext.h>
#include <stdio.h>
#include <stdlib.h>

#define HTC_DEFAULT_HTTP_SERVER_HOST "127.0.0.1"
#define HTC_DEFAULT_HTTP_SERVER_PORT 8080
#define HTC_DEFAULT_HTTP_SERVER_PATH "."
#define HTC_DEFAULT_HTTP_SERVER_IPV6 false

typedef struct HTC_HTTP_SERVER_ARGS{
  char *host;
  char *path;
  unsigned int port;
  bool ipv6;
}HTC_HTTP_SERVER_ARGS;

extern HTC_HTTP_SERVER_ARGS *programArgs;

static struct option long_options[] = {
    {"help", no_argument,       0, 'h'},
    {"host", required_argument, 0,  0 },
    {"port", required_argument, 0, 'p'},
    {"path", required_argument, 0, 'P'},
    {"ipv6", no_argument      , 0,  0 },
    {0, 0, 0, 0}
};

#endif
