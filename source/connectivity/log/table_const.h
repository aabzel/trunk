#ifndef TABLE_CONST_H
#define TABLE_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#define SIMPLE_TABLES

#ifdef SIMPLE_TABLES
#define TABLE_TOP_LEFT "+"
#define TABLE_TOP_RIGHT "+"
#define TABLE_TOP_SEPARATOR "+"
#define TABLE_TOP_FILL "-"

#define TABLE_SEP_LEFT "+"
#define TABLE_SEP_RIGHT "+"
#define TABLE_SEP_SEPARATOR "+"
#define TABLE_SEP_FILL "-"

#define TABLE_BTM_LEFT "+"
#define TABLE_BTM_RIGHT "+"
#define TABLE_BTM_SEPARATOR "+"
#define TABLE_BTM_FILL "-"

#define TABLE_LEFT "|"
#define TABLE_RIGHT "|"
#define TABLE_SEPARATOR "|"
#define T_SEP "|"
#define TSEP TABLE_SEPARATOR
#define TABLE_FILL " "
#else
#define TABLE_TOP_LEFT "ÃƒÂ¢Ã¢â‚¬Â¢Ã¢â‚¬ï¿½"
#define TABLE_TOP_RIGHT "ÃƒÂ¢Ã¢â‚¬Â¢Ã¢â‚¬â€�"
#define TABLE_TOP_SEPARATOR "ÃƒÂ¢Ã¢â‚¬Â¢Ã‚Â¤"
#define TABLE_TOP_FILL "ÃƒÂ¢Ã¢â‚¬Â¢Ã¯Â¿Â½"

#define TABLE_SEP_LEFT "ÃƒÂ¢Ã¢â‚¬Â¢Ã…Â¸"
#define TABLE_SEP_RIGHT "ÃƒÂ¢Ã¢â‚¬Â¢Ã‚Â¢"
#define TABLE_SEP_SEPARATOR "ÃƒÂ¢Ã¢â‚¬ï¿½Ã‚Â¼"
#define TABLE_SEP_FILL "ÃƒÂ¢Ã¢â‚¬ï¿½Ã¢â€šÂ¬"

#define TABLE_BTM_LEFT "ÃƒÂ¢Ã¢â‚¬Â¢Ã…Â¡"
#define TABLE_BTM_RIGHT "ÃƒÂ¢Ã¢â‚¬Â¢Ã¯Â¿Â½"
#define TABLE_BTM_SEPARATOR "ÃƒÂ¢Ã¢â‚¬Â¢Ã‚Â§"
#define TABLE_BTM_FILL "ÃƒÂ¢Ã¢â‚¬Â¢Ã¯Â¿Â½"

#define TABLE_LEFT "ÃƒÂ¢Ã¢â‚¬Â¢Ã¢â‚¬Ëœ"
#define TABLE_RIGHT "ÃƒÂ¢Ã¢â‚¬Â¢Ã¢â‚¬Ëœ"
#define TABLE_SEPARATOR "ÃƒÂ¢Ã¢â‚¬ï¿½Ã¢â‚¬Å¡"
#define TABLE_FILL " "
#endif


#ifdef __cplusplus
}
#endif

#endif /* TABLE_CONST_H */
