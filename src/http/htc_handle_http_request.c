#include "http/htc_http.h"
#include "http/htc_http_errornos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http/htc_http_parse_request.h"
#include "http/htc_http_handle_response.h"
#include "http/htc_http_request_utils.h"

extern int HTC_ERRORNO;
int HTC_SOCKET_ERORRNO = 0;

static void *handle_error(int errorCode, const char *message) {
  HTC_SOCKET_ERORRNO = errorCode;
  fprintf(stderr, "%s", message);
  return NULL;
}

void htc_listen_requests(HTC_SERVER *server_socket) {
  int clientfd;
  pid_t cpid;
  HTC_HTTP_REQUEST *rq;

  #ifdef HTC_IPV6
    if((clientfd = accept(server_socket->socketfd, (struct sockaddr6*) server_socket->servaddr.ipv6, &server_socket->servaddrlen)) < 0) {
  #else
    if((clientfd = accept(server_socket->socketfd, (struct sockaddr*) server_socket->servaddr.ipv4, &server_socket->servaddrlen)) < 0) {
  #endif
    close(clientfd);
    handle_error(HTC_ERRORNO_SOCKET, "Error accepting client connection\n");
  }
  
  if((cpid = fork()) < 0) {
    handle_error(HTC_ERRORNO_FORK, "Error on fork\n");
  }
 
  if(cpid == 0) {
    rq = htc_handle_http_request(clientfd);
    free(rq);
    _exit(EXIT_SUCCESS);
  }else {
    close(clientfd);
  }
}

HTC_HTTP_REQUEST *htc_handle_http_request(int clientfd) {
  HTC_HTTP_REQUEST *rq = malloc(sizeof(HTC_HTTP_REQUEST));
  rq->headers.headers = malloc(sizeof(HTC_HTTP_HEADER) * HTC_HEADER_MAX_HEADERS);

  if (!rq) {
    handle_error(HTC_ERRORNO_ALLOC, "Error while alocating request");
    _exit(-1);
  }
  
  char rqMsgBffr[10240];
  read(clientfd, rqMsgBffr, sizeof(rqMsgBffr) - 1);
  printf("Incoming request:");
  // TODO: Parsear direito a requisição rq
  htc_parse_request(rqMsgBffr, sizeof(rqMsgBffr), rq);
  htc_send_response(rq->route, clientfd, rq);
  
  return rq;
}

void htc_send_response(char *fileLocation, int clientfd, HTC_HTTP_REQUEST *rq) {
  int fileSize = 0;
  char *fileBuffer = NULL;
  char *header = NULL;
  char *responseBuffer = NULL;
  char *mediaType;
  ssize_t sent;

  if (htc_read_file(&fileBuffer, &fileSize, fileLocation) != 0) {
    handle_error(HTC_ERRORNO_GET_FILE, "Error getting file to response\n");
    return;
  }

  htc_get_mime(fileLocation, &mediaType);

  header = generate_header("HTTP/1.1", "200 OK", mediaType);
  responseBuffer = malloc(strlen(header) + fileSize + 1);
  if (!responseBuffer) {
    handle_error(HTC_ERRORNO_ALLOC, "Error allocating response buffer\n");
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

