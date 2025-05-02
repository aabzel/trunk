#ifndef STORAGE_DIAG_H
#define STORAGE_DIAG_H

#include <stddef.h>

#include "std_includes.h"
#include "storage_types.h"


const char* StorageMemoryFrameHeaderToStr(const StorageMemoryFrameHeader_t* const Header);
const char* StorageFrameHeaderToStr(const StorageFrameHeader_t* const Header );
const char* StorageAccessToStr(const StorageAccess_t access);
const char* StorageTypeToStr(StorageType_t type);
const char* DataToValueStr(const uint8_t*const buff, size_t size, StorageType_t type );
bool DataToValStrBuff(const  uint8_t* const buff, size_t value_len,
		              StorageType_t type, char* const  out_str, size_t str_size) ;
#endif /* STORAGE_DIAG_H */
