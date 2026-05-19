#ifndef _HTC_HTTP_PARSE_REQUEST_H_
#define _HTC_HTTP_PARSE_REQUEST_H_

#include "http/htc_http.h"

#include "stdio.h"

void htc_parse_request(char *request, int requestSize, HTC_HTTP_REQUEST *rq);

#endif
