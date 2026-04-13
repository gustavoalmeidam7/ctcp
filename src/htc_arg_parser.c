#include "htc_arg_parser.h"
#include "htc_program_args.h"

void htc_parse_args(int argc, char **argv, HTC_HTTP_SERVER_ARGS **programArgs) {
    int opt;
    int option_index = 0;
    const char *option_name;
        
    *programArgs = malloc(sizeof(HTC_HTTP_SERVER_ARGS));
    
    if (!(*programArgs)) {
        fprintf(stderr, "Error alocating resources");
        exit(-1);
    }

    (*programArgs)->host = HTC_DEFAULT_HTTP_SERVER_HOST;
    (*programArgs)->path = HTC_DEFAULT_HTTP_SERVER_PATH;
    (*programArgs)->port = HTC_DEFAULT_HTTP_SERVER_PORT;
    (*programArgs)->ipv6 = HTC_DEFAULT_HTTP_SERVER_IPV6;

    while ((opt = getopt_long(argc, argv,
                              "hp:P:",
                              long_options,
                              &option_index)) != -1) {

        switch (opt) {
            case 0:
                option_name = long_options[option_index].name;

                if (strcmp(option_name, "host") == 0) {
                    (*programArgs)->host = strdup(optarg);
                } 
                else if (strcmp(option_name, "ipv6") == 0) {
                   (*programArgs)->ipv6 = true;
                }
                else {
                    printf("Option not found! try --help\n");
                    exit(-1);
                }
                break;
            case 'h':
                printf(
                   "-p port\n"
                   "-P path\n"
                   "-host host\n"
                   "-ipv6 sets to ipv6\n");
                exit(0);
                break;

            case 'p':
                if (atoi(optarg) < 1) {
                    fprintf(stderr, "Invalid port: %s (must be in rage of 1 and 65535)\n", optarg);
                    exit(1);
                }
                
                (*programArgs)->port = atoi(optarg);
                break;
        
            case 'P':
                (*programArgs)->path = strdup(optarg);
                break;

            default:
                printf("Option not found! try --help\n");
                exit(-1);
        }
    }
}
