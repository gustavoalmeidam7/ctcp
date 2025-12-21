#ifndef CTP_HTTP_H_
#define CTP_HTTP_H_

#include "ctp_base_includes.h"
#include "http/ctp_http_errornos.h"

#include "ctp_server.h"
#include "http/ctp_http_consts.h"

extern int CTTP_SOCKET_ERRORNO;

typedef struct CTP_HTTP_HEADER{
  char *key;
  char *value;
}CTP_HTTP_HEADER;

typedef struct CTP_HTTP_REQUEST_HEADERS {
  CTP_HTTP_HEADER *headers;

  int headersSize;
} CTP_HTTP_REQUEST_HEADERS;


typedef struct CTP_HTTP_REQUEST{
  CTP_HTTP_REQUEST_HEADERS headers;

  int method;
  int protocol;
  
  char *route;
}CTP_HTTP_REQUEST;

void ctp_listen_requests(CTP_SERVER *server_socket);

CTP_HTTP_REQUEST *ctp_handle_http_request(int clientfd);

void ctp_send_response(char *file, int clientfd, CTP_HTTP_REQUEST *rq);

#endif
