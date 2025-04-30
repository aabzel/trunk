#include "modulator_diag.h"

#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

bool modulator_print_samples(Modulator_t* Node) {
    bool res = false;
    LOG_WARNING(MODULATOR,"Print %u Samples", Node->sample_cnt);
    if(Node){
        uint32_t s = 0;
        static const table_col_t cols[] = {
            {5, "No"}, {12, "UpTime"},  {12, "SampleDec"},  };
        double up_time_s = 0.0;
        LOG_INFO(MODULATOR, "SampleCnt: %u", Node->sample_cnt);
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        for(s = 0; s < Node->sample_cnt; s++) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);
            up_time_s = ((double)(s + 1))/((double)Node->sampling_frequency_hz);
            cli_printf(" %10.8f " TSEP, up_time_s);
            cli_printf(" %10d " TSEP, Node->samples[s]);
            cli_printf(" 0x%08x " TSEP, Node->samples[s]);

            cli_printf(CRLF);
            res = true;
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}
