#ifndef CTP_HTTP_PARSE_REQUEST_H_
#define CTP_HTTP_PARSE_REQUEST_H_

#include "http/ctp_http.h"

void ctp_parse_request(char *request, int requestSize, CTP_HTTP_REQUEST *rq);

#endif
