#ifndef CTP_HTTP_MIMES_H_
#define CTP_HTTP_MIMES_H_

#include <string.h>
#include "http/ctp_http.h"
#include "helpers/ctp_helpers.h"

void ctp_get_mime(char *file, char **output);

int ctp_get_method(char *methodStr);

int ctp_get_header(CTP_HTTP_REQUEST_HEADERS *headers, char* key, char **value);

int ctp_get_protocol(char *protocolStr);

#endif
