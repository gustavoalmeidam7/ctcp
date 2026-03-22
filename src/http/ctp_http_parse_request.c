#include "http/ctp_http_parse_request.h"
#include "http/ctp_http_request_utils.h"

int parse_mrp(CTP_HTTP_REQUEST *rq, char *request) {
  char *requestBfr = strdup(request);
  char *mrpBfr;
  char *restRequest = requestBfr;
  char *restMrp;

  char *mrp = strtok_r(restRequest, "\r\n", &restRequest);
  mrpBfr = strdup(mrp);
  restMrp = mrpBfr;

  char *method   = strtok_r(restMrp, " ", &restMrp);
  char *route    = strtok_r(restMrp, " ", &restMrp);
  char *protocol = strtok_r(restMrp, "\r\n", &restMrp);

  if (!method || !route || !protocol) {
    return -1;
  }

  rq->method   = ctp_get_method(method);
  rq->route    = strdup(route);
  rq->protocol = ctp_get_protocol(protocol);

  printf("\nMethod: %d : '%s'\nRoute: '%s'\nProtocol: %d : '%s'\n", rq->method, method, rq->route, rq->protocol, protocol);

  free(requestBfr);
  free(mrpBfr);

  return 0;
}

int parse_headers(CTP_HTTP_REQUEST_HEADERS *headers, char *request) {
  char *requestBfr = strdup(request);

  int maxHeadersSize = 8192; //8kb

  char *startHeaders = strstr(requestBfr, "\r\n");
  char *endHeaders = strstr(requestBfr, "\r\n\r\n");

  char *token;

  if (endHeaders - startHeaders >= maxHeadersSize) {
    free(requestBfr);
    return -1;
  }

  token = strtok(startHeaders, "\r\n");
  int endIndex = endHeaders - startHeaders;
  int curIndex = 0;

  for(int headerI = 0;;headerI++) {
    curIndex = token - startHeaders;
    if(token == NULL || curIndex >= endIndex) {
      break;
    }

    char *bfr = strdup(token);
    char *del = strstr(token, ": ");

    headers->headers[headerI].value = strdup(&del[2]);

    bfr[del - bfr] = '\0';
    
    headers->headers[headerI].key = strdup(bfr);

    headers->headersSize++;

    printf("HEADER: %s: %s\n", headers->headers[headerI].key, headers->headers[headerI].value);

    token = strtok(NULL, "\r\n");

    free(bfr);
  }

  free(requestBfr);
  return 0;
}

void ctp_parse_request(char *request, int requestSize, CTP_HTTP_REQUEST *rq) {
  char *originalRequest = strdup(request);

  parse_mrp(rq, originalRequest);

  if(parse_headers(&rq->headers, originalRequest) == 0) {
    printf("Header quantity: %d\n\n", rq->headers.headersSize);
  }

  free(originalRequest);
  
  return;
}

