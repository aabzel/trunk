#ifndef CSV_DIAG_H
#define CSV_DIAG_H

#include "csv_types.h"

bool CsvNodeDiag(CsvFsm_t *const Node);
bool csv_print(char *const text,char separator, Order_t order);
const char* CsvNodeToStr(const CsvFsm_t* const Node);
const char* CsvInputToStr(const CsvInput_t input);
const char* CsvStateToStr(const CsvState_t state);

#endif
