#include "http/ctp_http.h"
#include "http/ctp_http_errornos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http/ctp_http_parse_request.h"
#include "http/ctp_http_handle_response.h"
#include "http/ctp_http_request_utils.h"

extern int CTP_ERRORNO;
int CTP_SOCKET_ERORRNO = 0;

static void *handle_error(int errorCode, const char *message) {
  CTP_SOCKET_ERORRNO = errorCode;
  fprintf(stderr, "%s", message);
  return NULL;
}

void ctp_listen_requests(CTP_SERVER *server_socket) {
  int clientfd;
  pid_t cpid;
  CTP_HTTP_REQUEST *rq;
  
  if((clientfd = accept(server_socket->socketfd, (struct sockaddr*) server_socket->servaddr, &server_socket->servaddrlen)) < 0) {
    close(clientfd);
    handle_error(CTP_ERRORNO_SOCKET, "Error accepting client connection\n");
  }
  
  if((cpid = fork()) < 0) {
    handle_error(CTP_ERRORNO_FORK, "Error on fork\n");
  }
 
  if(cpid == 0) {
    rq = ctp_handle_http_request(clientfd);
    free(rq);
    _exit(EXIT_SUCCESS);
  }else {
    close(clientfd);
  }
}

CTP_HTTP_REQUEST *ctp_handle_http_request(int clientfd) {
  CTP_HTTP_REQUEST *rq = malloc(sizeof(CTP_HTTP_REQUEST));
  rq->headers.headers = malloc(sizeof(CTP_HTTP_HEADER) * CTP_HEADER_MAX_HEADERS);

  if (!rq) {
    handle_error(CTP_ERRORNO_ALLOC, "Error while alocating request");
    _exit(-1);
  }
  
  char rqMsgBffr[10240];
  read(clientfd, rqMsgBffr, sizeof(rqMsgBffr) - 1);
  printf("Incoming request:");
  // TODO: Parsear direito a requisição rq
  ctp_parse_request(rqMsgBffr, sizeof(rqMsgBffr), rq);
  ctp_send_response(rq->route, clientfd, rq);
  
  return rq;
}

void ctp_send_response(char *fileLocation, int clientfd, CTP_HTTP_REQUEST *rq) {
  int fileSize = 0;
  char *fileBuffer = NULL;
  char *header = NULL;
  char *responseBuffer = NULL;
  char *mediaType;
  ssize_t sent;

  if (ctp_read_file(&fileBuffer, &fileSize, fileLocation) != 0) {
    handle_error(CTP_ERRORNO_GET_FILE, "Error getting file to response\n");
    return;
  }

  ctp_get_mime(fileLocation, &mediaType);

  header = generate_header("HTTP/1.1", "200 OK", mediaType);
  responseBuffer = malloc(strlen(header) + fileSize + 1);
  if (!responseBuffer) {
    handle_error(CTP_ERRORNO_ALLOC, "Error allocating response buffer\n");
    free(header);
    free(fileBuffer);
    return;
  }

  memcpy(responseBuffer, header, strlen(header));
  memcpy(responseBuffer + strlen(header), fileBuffer, fileSize);
  responseBuffer[strlen(header) + fileSize] = '\0';

  sent = send(clientfd, responseBuffer, strlen(header) + fileSize, 0);

  free(header);
  free(fileBuffer);
  free(responseBuffer);
  free(mediaType);
}

