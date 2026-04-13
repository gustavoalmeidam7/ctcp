#ifndef CTP_ARG_PARSER_H_
#define CTP_ARG_PARSER_H_

#include "ctp_program_args.h"
#include "unistd.h"

void ctp_parse_args(int argc, char **argv, CTP_HTTP_SERVER_ARGS **programArgs);

#endif
