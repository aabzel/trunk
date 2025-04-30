#include "sys.h"

#include <stdbool.h>

uint32_t critical_nesting_level = 0U;

bool isFromInterrupt(void) {
  bool res = false;
  return res;
}

void enter_critical(void) {

}

void exit_critical(void) {
 
}
