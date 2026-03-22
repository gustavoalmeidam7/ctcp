#include "helpers/ctp_helpers.h"

void to_lower(char *str) {
  for(int i = 0; i < strlen(str); i++) {
    if((int) str[i] > 64 && (int) str[i] < 91) {
      str[i] = (char) str[i] + 32;
    }
  }
}
