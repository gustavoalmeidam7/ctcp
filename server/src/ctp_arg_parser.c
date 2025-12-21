#include "ctp_arg_parser.h"
#include <bits/getopt_core.h>
#include <stdio.h>
#include <stdlib.h>

PCTP_HTTP_SERVER_ARGS programArgs;

void ctp_parse_args(int argc, char **argv) {
    int opt;
    int option_index = 0;

    if ((programArgs = malloc(sizeof(CTP_HTTP_SERVER_ARGS))) == NULL) {
        fprintf(stderr, "Error alocating resources");
        exit(-1);
    }

    programArgs->host = CTP_DEFAULT_HTTP_SERVER_HOST;
    programArgs->path = CTP_DEFAULT_HTTP_SERVER_PATH;
    programArgs->port = CTP_DEFAULT_HTTP_SERVER_PORT;

    while ((opt = getopt_long(argc, argv,
                              "hpP",    
                              long_options,
                              &option_index)) != -1) {

        switch (opt) {
            case 'h':
                programArgs->host = strdup(optarg);
                break;

            case 'p':
                if (atoi(optarg) < 1) {
                    fprintf(stderr, "Invalid port: %s (must be in rage of 1 and 65535)\n", optarg);
                    exit(1);
                }
                
                programArgs->port = atoi(optarg);
                break;
        
            case 'P':
                programArgs->path = strdup(optarg);
                break;

            default:
                printf("Option not found!\n");
                exit(-1);
        }
    }
}
