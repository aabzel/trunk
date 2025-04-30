
#ifndef XML_CONFIG_H
#define XML_CONFIG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_LIFO
#include "lifo_array.h"
#endif

#include "xml.h"
#include "xml_types.h"

#ifdef HAS_HASHSET
#include "hashset.h"
#endif

#ifdef HAS_LIFO
extern LifoArray_t XmlLifoArray;
#endif

#ifdef HAS_HASHSET
extern HashSet_t XmlHashSet;
#endif

extern Xml_t XmlItem;

void HandleTag(void* cookie, const char* tag_name);
void HandleTagEnd(void* cookie, const char* tag_end);
void HandleParameter(void* cookie, const char* parameter);
void HandleContent(void* cookie, const char* content);
void HandleAttribute(void* cookie, const char* attribute);

#ifdef __cplusplus
};
#endif

#endif /* XML_CONFIG_H */
