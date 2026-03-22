#ifndef CTP_BASE_INCLUDE_H_
#define CTP_BASE_INCLUDE_H_

#include <stdio.h>
#include <string.h>

#ifdef __linux__
  #include <sys/socket.h>
  
  #include <netinet/in.h>
  
  #include <unistd.h>
  #include <stdlib.h>
  #include <sys/types.h>
  #include <arpa/inet.h>
#endif

#endif
