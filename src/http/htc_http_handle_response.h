#ifndef _HTC_HTTP_HANDLE_RESPONSE_H_
#define _HTC_HTTP_HANDLE_RESPONSE_H_

#include "http/htc_http_errornos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned int HTC_RESPONSE_ERRORNO;

char *generate_header(char *protocol, char *statusCode, char *contentType);

int htc_read_file(char **file, int *fileSize, char *fileLocation);

#endif

