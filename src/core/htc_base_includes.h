#ifndef HTC_BASE_INCLUDE_H_
#define HTC_BASE_INCLUDE_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __linux__
  #include <sys/socket.h>
  
  #include <netinet/in.h>
  
  #include <unistd.h>
  #include <sys/types.h>
  #include <arpa/inet.h>
#endif

#endif
