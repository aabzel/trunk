#include "xml_config.h"

#include <string.h>
#include <stdlib.h>

#ifdef HAS_HASHSET
HashSet_t XmlHashSet;
#include "hashset.h"
#endif /*HAS_HASHSET*/

#ifdef HAS_KEEPASS
#include "keepass_config.h"
#endif /*HAS_KEEPASS*/

#ifdef HAS_DOT
#include "dot.h"
#endif /*HAS_DOT*/
#include "log.h"

LifoArray_t XmlLifoArray;
Xml_t XmlItem;

#ifdef HAS_DOT
FILE* dot_file = NULL;
#endif

static char node_name[100] = "";
void HandleTag(void* cookie, const char* tag_name) {
    LOG_PARN(XML, "TagHandler: [%s]", tag_name);
    if(tag_name[0] != '?') {
        uint32_t cnt = 0;
        bool res = false;
#ifdef HAS_HASHSET
        res = hashset_push((HashSet_t* const)&XmlHashSet, tag_name, strlen(tag_name));
        if(false==res) {
            XmlItem.err_cnt++;
        }
        cnt = hashset_check(&XmlHashSet, (uint8_t*) tag_name, (uint32_t) strlen(tag_name));
#endif /*HAS_HASHSET*/
        snprintf(node_name, sizeof(node_name), "%s_%u", tag_name, cnt);
#ifdef HAS_XML_2_DOT
        fprintf(dot_file, "%s [label=%s] [shape=box]" CRLF, node_name, tag_name);
        Array_t parent_node;
        res = lifo_arr_peek(&XmlLifoArray, &parent_node);
        if (res) {
            fprintf(dot_file, "%s->%s" CRLF, parent_node.pArr, node_name);
        }
#endif /*HAS_XML_2_DOT*/

        char *new_name =strdup(node_name);
        if (new_name) {
            Array_t node = {.size =0,.pArr=NULL,};
            node.pArr = new_name;
            node.size = strlen(node_name);
            res = lifo_arr_push(&XmlLifoArray, node);
            if (false==res) {
                XmlItem.err_cnt++;
            }
        } else {
            XmlItem.err_cnt++;
            LOG_ERROR(XML, "MallocErrFor: [%s]", node_name);
            res = false;
        }
#ifdef HAS_KEEPASS
        int ret;
        ret = strcmp("String", tag_name);
        if(0 == ret) {
            is_string_node = true;
        }
        ret = strcmp("Key", tag_name);
        if(0 == ret) {
            is_key_node = true;
        }
        ret = strcmp("Value", tag_name);
        if(0 == ret) {
            is_value_node = true;
        }
#endif
    }
}

void HandleTagEnd(void* cookie, const char* tag_end) {
    LOG_PARN(XML, "    TagEndHandler: [%s]", tag_end);
    // strcpy(CurParent,"");
    Array_t node;
    bool res = false;
    res = lifo_arr_pull(&XmlLifoArray, &node);
    if(res){
        if(node.pArr){
            free(node.pArr);
        }
    }
#ifdef HAS_KEEPASS
    int ret = strcmp("Entry", tag_end);
    if(0 == ret) {
        KeePassItem.cur_entry++;
    }
    ret = strcmp("String", tag_end);
    if(0 == ret) {
        is_string_node = false;
        is_title_node = false;
        is_user_name_node = false;
        is_password_node = false;
    }
    ret = strcmp("Key", tag_end);
    if(0 == ret) {
        is_key_node = false;
    }
    ret = strcmp("Value", tag_end);
    if(0 == ret) {
        is_value_node = false;
    }
#endif
}

void HandleParameter(void* cookie, const char* parameter) {
    LOG_PARN(XML, "parameterHandler: [%s]", parameter);
#ifdef HAS_XML_2_DOT
    bool res;
    Array_t parent_node;
    res = lifo_arr_peek(&XmlLifoArray, &parent_node);
    if(res) {
        fprintf(dot_file, "%s->%s" CRLF, parent_node.pArr, parameter);
    }
#endif
}

void HandleContent(void* cookie, const char* content) {
    LOG_PARN(XML, "contentHandler: [%s]", content);
    static uint32_t cont_cnt = 0;
    cont_cnt++;
#ifdef HAS_XML_2_DOT
    bool res;
    fprintf(dot_file, "cont_%u [label=\"%s\"] [shape=box]" CRLF, cont_cnt, content);

    Array_t parent_node;
    res = lifo_arr_peek(&XmlLifoArray, &parent_node);
    if(res) {
        fprintf(dot_file, "%s->cont_%u" CRLF, parent_node.pArr, cont_cnt);
    }
#endif

#ifdef HAS_KEEPASS
    int ret = 0;
    if(is_string_node) {
        if(is_key_node) {
            ret = strcmp("Title", content);
            if(!ret) {
                is_title_node = true;
            }
            ret = strcmp("Password", content);
            if(!ret) {
                is_password_node = true;
            }
            ret = strcmp("UserName", content);
            if(!ret) {
                is_user_name_node = true;
            }
        }
        if(is_value_node) {
            if(is_title_node) {
                if(strlen(content)<TITLE_SIZE){
                    strncpy(KeePassItem.entry[KeePassItem.cur_entry].title, content, TITLE_SIZE-1);
                    KeePassItem.entry[KeePassItem.cur_entry].valid = true;
                }else{
                    LOG_ERROR(XML,"TitleTooLong [%s] Max:%u byte",content,TITLE_SIZE);
                }
                is_title_node = false;
            }
            if(is_user_name_node) {
                if(strlen(content)<USER_NAME_SIZE){
                    strncpy(KeePassItem.entry[KeePassItem.cur_entry].user_name, content, USER_NAME_SIZE-1);
                    KeePassItem.entry[KeePassItem.cur_entry].valid = true;
                }else{
                    LOG_ERROR(XML,"UserNameTooLong [%s] Max %u Byte", content, USER_NAME_SIZE);
                }
                is_user_name_node = false;
            }
            if(is_password_node) {
                memset(KeePassItem.entry[KeePassItem.cur_entry].PassWord.base64 ,0x00,PASSWORD_SIZE);
                if(strlen(content)<PASSWORD_SIZE){
                    strncpy(KeePassItem.entry[KeePassItem.cur_entry].PassWord.base64, content, PASSWORD_SIZE-1);
                    KeePassItem.entry[KeePassItem.cur_entry].PassWord.base64[PASSWORD_SIZE-1] =0x00;
                    KeePassItem.entry[KeePassItem.cur_entry].valid = true;
                }else{
                    LOG_ERROR(XML,"Base46PassTooLong [%s] Max %u Byte", content, PASSWORD_SIZE);
                }
                is_password_node = false;
            }
        }
    }
#endif
}

void HandleAttribute(void* cookie, const char* attribute) {
    LOG_PARN(XML, "attributeHandler: [%s]", attribute);
    static uint32_t attr_cnt = 0;
    attr_cnt++;
#ifdef HAS_XML_2_DOT
    bool res;
    Array_t parent_node;
    fprintf(dot_file,"attr_%u [label=[%s]][shape=box]", attr_cnt,attribute);
    res = lifo_arr_peek(&XmlLifoArray, &parent_node);
    if(res) {
        fprintf(dot_file,"%s->attr_%u %s", parent_node.pArr,attr_cnt);
    }
#endif
}
