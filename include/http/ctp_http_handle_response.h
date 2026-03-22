#ifndef CTP_HTTP_HANDLE_RESPONSE_H_
#define CTP_HTTP_HANDLE_RESPONSE_H_

#include "http/ctp_http_errornos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned int CTP_RESPONSE_ERRORNO;

char *generate_header(char *protocol, char *statusCode, char *contentType);

int ctp_read_file(char **file, int *fileSize, char *fileLocation);

#endif

