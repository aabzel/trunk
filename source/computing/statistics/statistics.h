#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdbool.h>
#include <stdint.h>

#include "statistics_types.h"

extern RandomVariable_t RandomVariable;


bool statistics_calc_bar_chart(RandomVariable_t* const Node);
bool statistics_load(const char* const file_name,uint32_t column );
bool statistics_expected_value(RandomVariable_t* const Node);
bool statistics_standard_deviation(RandomVariable_t* const Node);


#endif /*STATISTICS_H*/
