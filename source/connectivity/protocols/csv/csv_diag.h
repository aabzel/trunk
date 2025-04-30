#ifndef CSV_DIAG_H
#define CSV_DIAG_H

#include "csv_types.h"

bool CsvNodeDiag(CsvFsm_t *const Node);
bool csv_print(char *const text,char separator, Order_t order);
const char* CsvNode2Str(CsvFsm_t *const Node);
const char* CsvInput2Str(CsvInput_t input);
const char* CsvState2Str(CsvState_t state);

#endif
