#include "http/htc_http_request_utils.h"
#include <strings.h>

void htc_get_mime(char *file, char **output) {
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

int htc_get_method(char *methodStr) {
  char *methodCmp = strdup(methodStr);
  
  if (strcasecmp(methodCmp, "get") == 0){
    return HTC_HTTP_METHOD_GET;
  } else if (strcasecmp(methodCmp, "post") == 0){
    return HTC_HTTP_METHOD_POST;
  } else if (strcasecmp(methodCmp, "options") == 0){
    return HTC_HTTP_METHOD_OPTIONS;
  } else {
    return HTC_HTTP_METHOD_UNKNOWN;
  }

  free(methodCmp);
}

int htc_get_protocol(char *protocolStr) {
  char *protocolCmp = strdup(protocolStr);

  if (strcasecmp(protocolCmp, "http/1.1") == 0){
    return HTC_HTTP_PROTOCOL_HTTP_1_1;
  } else {
    return HTC_HTTP_PROTOCOL_UNDEFINED;
  }

  free(protocolCmp);
}

int htc_get_header(HTC_HTTP_REQUEST_HEADERS *headers, char* key, char **value){
  char *kkey = strdup(key);

  for(int i = 0; i < headers->headersSize;i++) {
    char *toCompare = strdup(headers->headers[i].key);

    if (strcasecmp(kkey, toCompare) == 0) {
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

