#ifndef _HTC_HTTP_MIMES_H_
#define _HTC_HTTP_MIMES_H_

#include <string.h>
#include "http/htc_http.h"

void htc_get_mime(char *file, char **output);

int htc_get_method(char *methodStr);

int htc_get_header(HTC_HTTP_REQUEST_HEADERS *headers, char* key, char **value);

int htc_get_protocol(char *protocolStr);

#endif
