#ifndef HTC_ARG_PARSER_H_
#define HTC_ARG_PARSER_H_

#include "core/htc_program_args.h"
#include "unistd.h"

void htc_parse_args(int argc, char **argv, HTC_HTTP_SERVER_ARGS **programArgs);

#endif
