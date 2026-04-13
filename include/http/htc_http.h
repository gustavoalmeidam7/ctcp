#ifndef _HTC_HTTP_H_
#define _HTC_HTTP_H_

#include "htc_base_includes.h"
#include "http/htc_http_errornos.h"
#include "http/htc_http_server.h"

#include "http/htc_http_consts.h"

extern int HTC_SOCKET_ERRORNO;

typedef struct HTC_HTTP_HEADER{
  char *key;
  char *value;
}HTC_HTTP_HEADER;

typedef struct HTC_HTTP_REQUEST_HEADERS {
  HTC_HTTP_HEADER *headers;

  int headersSize;
} HTC_HTTP_REQUEST_HEADERS;


typedef struct HTC_HTTP_REQUEST{
  HTC_HTTP_REQUEST_HEADERS headers;

  int method;
  int protocol;
  
  char *route;
}HTC_HTTP_REQUEST;

void htc_listen_requests(HTC_SERVER *server_socket);

HTC_HTTP_REQUEST *htc_handle_http_request(int clientfd);

void htc_send_response(char *file, int clientfd, HTC_HTTP_REQUEST *rq);

#endif
