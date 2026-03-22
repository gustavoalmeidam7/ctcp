#include "http/ctp_http_request_utils.h"

void ctp_get_mime(char *file, char **output) {
  if (strstr(file, ".") == NULL) {
    *output = strdup("text/html");
    return;
  }
  
  char *fileExtention = &strstr(file, ".")[1];

  if (strcmp(fileExtention, "css") == 0){
    *output = strdup("text/css");
  } else if (strcmp(fileExtention, "png") == 0){
    *output = strdup("image/png");
  } else if (strcmp(fileExtention, "svg") == 0){
    *output = strdup("image/svg+xml");
  } else {
    *output = strdup("text/html");
  }
}

int ctp_get_method(char *methodStr) {
  char *methodCmp = strdup(methodStr);
  to_lower(methodStr);

  if (strcmp(methodCmp, "get") == 0){
    return CTP_HTTP_METHOD_GET;
  } else if (strcmp(methodCmp, "post") == 0){
    return CTP_HTTP_METHOD_POST;
  } else if (strcmp(methodCmp, "options") == 0){
    return CTP_HTTP_METHOD_OPTIONS;
  } else {
    return CTP_HTTP_METHOD_UNKNOWN;
  }

  free(methodCmp);
}

int ctp_get_protocol(char *protocolStr) {
  char *protocolCmp = strdup(protocolStr);
  to_lower(protocolCmp);

  if (strcmp(protocolCmp, "http/1.1") == 0){
    return CTP_HTTP_PROTOCOL_HTTP_1_1;
  } else {
    return CTP_HTTP_PROTOCOL_UNDEFINED;
  }

  free(protocolCmp);
}

int ctp_get_header(CTP_HTTP_REQUEST_HEADERS *headers, char* key, char **value){
  char *kkey = strdup(key);
  to_lower(kkey);

  for(int i = 0; i < headers->headersSize;i++) {
    char *toCompare = strdup(headers->headers[i].key);
    to_lower(toCompare);

    if (strcmp(kkey, toCompare) == 0) {
      *value = strdup(headers->headers[i].value);
      free(kkey);
      free(toCompare);
      return i;
    }

    free(toCompare);
  }

  free(kkey);
  return -1;
}

