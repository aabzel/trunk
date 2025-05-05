
#ifndef AUTO_VERSION_H
#define AUTO_VERSION_H

#include <stdbool.h>
//#include <stdint.h>

#include "auto_version_diag.h"
#include "auto_version_config.h"
#include "auto_version_types.h"

bool auto_version_proc_line(AutoVersionHandle_t* Node, char* file_line);
bool auto_version_proc_headr( const char* const file_name);
bool auto_version_init(void);
bool auto_version_proc(void);

#endif /* AUTO_VERSION_H */
