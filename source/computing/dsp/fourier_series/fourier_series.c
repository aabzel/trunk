#include "fourier_series.h"

#ifdef HAS_COMPLEX
#include <complex.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_PLANETARIUM
#include "planetarium.h"
#endif
#include "dft.h"
#include "log.h"
#include "complex_diag.h"
#include "calendar.h"
#include "csv.h"
#include "file_api.h"
#include "utils_math.h"
#include "time_diag.h"
#include "win_utils.h"
#include "time_mcal.h"
#include "timer_utils.h"

FourierSeriesHandle_t* FourierSeriesGetNode(uint8_t num) {
    FourierSeriesHandle_t* FourierSeriesNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = fourier_series_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == FourierSeriesItem[i].num) {
            if(FourierSeriesItem[i].valid) {
                FourierSeriesNode = &FourierSeriesItem[i];
                break;
            }
        }
    }
    return FourierSeriesNode;
}

const FourierSeriesConfig_t* FourierSeriesGetConfNode(uint8_t num) {
    const FourierSeriesConfig_t* FourierSeriesConfNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = fourier_series_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == FourierSeriesConfig[i].num) {
            if(FourierSeriesConfig[i].valid) {
                FourierSeriesConfNode = &FourierSeriesConfig[i];
                break;
            }
        }
    }
    return FourierSeriesConfNode;
}

static bool fourier_series_init_one(uint8_t num){
    bool res = false;
    LOG_WARNING(FOURIER_SERIES,"Init %u", num);
    FourierSeriesHandle_t* Node = FourierSeriesGetNode(  num);
    if(Node){
        Node->y=NULL;
        res = true;
    }else{
        LOG_ERROR(FOURIER_SERIES,"%u LackOfNode", num);
    }
    return res;
}

bool fourier_series_init(void){
    bool res = false;
    set_log_level(FOURIER_SERIES,LOG_LEVEL_DEBUG);
    uint32_t i = 0;
    uint32_t ok = 0;
    uint32_t cnt = fourier_series_get_cnt();
    LOG_WARNING(FOURIER_SERIES,"Init Cnt %u", cnt);
    for(i = 1; i <= cnt; i++) {
        res=fourier_series_init_one(i);
        if(res){
            ok++;
        }
    }

    if(ok) {
        res = true;
    }else{
        res = false;
    }
    return res;
}

bool dft_low_pass(double complex* X, FourierSeriesHandle_t* Node, double sampling_period_s, uint8_t order){
    bool res = false;
    LOG_INFO(FOURIER_SERIES, "N:%u  Order:%d SamplePeriod:%f s",Node->line_cnt,  order, sampling_period_s);

    double argument=0.0;
    double amplitude=0.0;
    double frequency=0.0;
    double period_s=0.0;
    double time_s=0.0;
    uint32_t t = 0;
    uint32_t k = 0;

    for(t=0;t<Node->line_cnt;t++) {
        Node->y_lp[t] = cabs(X[0])/2;
    }

    for(k=1;k<=order;k++) {
        frequency=((double)k)/(((double)Node->line_cnt)*sampling_period_s);
        amplitude=cabs(X[k]);
        argument=carg(X[k])+ M_PI/2.0;
        if(0.0<frequency){
            period_s = 1.0/frequency;
        } else {
            period_s = 999999999;
        }
        LOG_INFO(FOURIER_SERIES, "Order k:%u Amplitude:%f Argument:%f Rad Freq %f Hz Period %f s",k, amplitude, argument, frequency, SEC_2_HOUR(period_s));
        for(t=0; t<Node->line_cnt; t++) {
            //Node->y_lp[t] += amplitude*sin(    Node->x[t]*2.0*M_PI*frequency + argument );
            // time_s= Node->x[t];
            time_s = sampling_period_s*((double)t);
            //Node->y_lp[t] += amplitude*cos(   time_s*2.0*M_PI*frequency + argument );
            Node->y_lp[t] += amplitude*sin(   time_s*2.0*M_PI*frequency + argument );
        }
        res = true;
    }
    return res;
}

bool signals_save(char* file_name, FourierSeriesHandle_t* Node){
    bool res = false;
    FILE* file_prt = NULL;
    file_prt = fopen(file_name, "w");
    if(file_prt){
        LOG_INFO(FOURIER_SERIES,"File [%s] OpenOk",file_name);
        uint32_t t=0;
        for(t=0;t<Node->line_cnt;t++){
            int ret;
            ret=fprintf(file_prt, "%u,%u,%f,%f\n",  ((uint32_t) (((double)t)*Node->sampling_period_s) )  ,((uint32_t) Node->x[t]),Node->y[t],Node->y_lp[t]);
            if(ret<0){
                LOG_ERROR(FOURIER_SERIES,"Err");
            }
        }
        fclose(file_prt);
        res = true;
    } else {
        LOG_ERROR(FOURIER_SERIES,"File [%s] OpenErr",file_name);
    }
    return res;
}

#define OUT_FILE_NAME "OutFile.csv"
#define SAMPLING_PERIOD_S 20
bool fourier_series_calc_coefficient(uint8_t num, uint8_t order, const char* const  file_name){
    bool res = false;
    FourierSeriesHandle_t* Node = FourierSeriesGetNode(  num);

    Node->line_cnt= file_line_cnt(file_name);
    if(Node->line_cnt) {
        Node->sampling_period_s = SAMPLING_PERIOD_S;
        LOG_INFO(FOURIER_SERIES,"File [%s] Contains %d lines",file_name,  Node->line_cnt);
        Node->y = (double* ) malloc(sizeof(double)*Node->line_cnt+100);
        Node->x = (double* ) malloc(sizeof(double)*Node->line_cnt+100);
        Node->y_lp = (double* ) malloc(sizeof(double)*Node->line_cnt+100);
        if(Node->y && Node->x){
            memset(&Node->y[0],0,sizeof(double)*(Node->line_cnt));
            memset(&Node->x[0],0,sizeof(double)*(Node->line_cnt));
            LOG_INFO(FOURIER_SERIES,"MallocOK %u byte",  sizeof(double)*Node->line_cnt);
        }else{
            LOG_ERROR(FOURIER_SERIES,"MallocErr %u byte",  sizeof(double)*Node->line_cnt);
        }
    }

    FILE* file_prt = NULL;
    file_prt = fopen(file_name, "r");
    if(file_prt) {
        LOG_INFO(FOURIER_SERIES,"File [%s] OpenOk",file_name);
        int line_cnt = 1;
        while (NULL != fgets(Node->line, sizeof(Node->line), file_prt)) {
            LOG_PARN(FOURIER_SERIES,"%u:[%s]",line_cnt, Node->line);
            res = csv_parse_double(Node->line, 5, &Node->value_x);
            if (res) {
                Node->x[line_cnt-1] = Node->value_x;
            }

            res = csv_parse_double(Node->line, 1, &Node->value);
            if (res) {
                LOG_PARN(FOURIER_SERIES,"CSVparseOk [%s] Value:%f",Node->line,Node->value);
                Node->y[line_cnt-1] = Node->value;
            } else {
                LOG_ERROR(FOURIER_SERIES,"CSVparseErr [%s]",Node->line);
            }
            line_cnt++;
            res = true;
            cli_printf("\rLine:%u",line_cnt);
        }
        fclose(file_prt);
        LOG_INFO(FOURIER_SERIES,"File [%s] %u Lines",file_name,line_cnt);
        LOG_INFO(FOURIER_SERIES,"File [%s] CloseOk",file_name);
        double complex *Spectr=NULL;
        uint32_t complex_size =sizeof(double complex);
        LOG_INFO(FOURIER_SERIES,"ComplexSize [%u] Byte",complex_size);
        Spectr= malloc(   complex_size*Node->line_cnt);
        if (Spectr) {
            res = dft_calc((SampleType_t*) Node->y, Node->line_cnt, Spectr, Node->line_cnt, SAMPLING_PERIOD_S);
            res = complex_array_print(Spectr, Node->line_cnt, SAMPLING_PERIOD_S, 30);

            if(Node->y_lp){
                res = dft_low_pass(Spectr, Node, SAMPLING_PERIOD_S, order);
                sprintf(Node->out_file_name,OUT_FILE_NAME);
                res = signals_save(Node->out_file_name, Node);
                uint32_t idx= array_double_max_index(Node->y_lp , Node->line_cnt);
                uint32_t noon_offset_s = idx*SAMPLING_PERIOD_S;
                LOG_INFO(FOURIER_SERIES,"TimeOfMaxLit x[%u]=%f =%u s= %f Hour",
                        idx,
                        Node->x[idx],
                        noon_offset_s,
                        SEC_2_HOUR(noon_offset_s)
                        );
                struct tm time_date_noon={0};
                res= SecondsToTimeDate(  noon_offset_s, &time_date_noon);
                if(res) {
                    res= print_time( &time_date_noon);
                    double lambda_deg=0.0;
                    struct tm time_cur;
                    res=time_get_cur(&time_cur);
                    time_date_noon.tm_isdst = time_cur.tm_isdst;
                    time_date_noon.tm_mday = time_cur.tm_mday;
                    time_date_noon.tm_mon = time_cur.tm_mon;
                    time_date_noon.tm_year = time_cur.tm_year;
                    time_date_noon.tm_wday = time_cur.tm_wday;
                    time_date_noon.tm_yday = time_cur.tm_yday;
#ifdef HAS_PLANETARIUM
                    res= calc_lambda(&time_date_noon, &lambda_deg);
                    if(res) {
                        LOG_INFO(FOURIER_SERIES,"lambda %f deg", lambda_deg);
                    }
#endif
                    char CmdCommand[200]="";
                    sprintf(CmdCommand,"PlotGraph.py %s %u %f",OUT_FILE_NAME,noon_offset_s,lambda_deg);
                    LOG_INFO(FOURIER_SERIES,"ExeCmd [%s]", CmdCommand);

                    res = win_cmd_run(CmdCommand);

                    //system(CmdCommand);
                }
                /**/
            }

        } else {
              LOG_ERROR(FOURIER_SERIES,"MallocForSpectrErr %u byte", complex_size*Node->line_cnt);
        }
    }else{
        LOG_ERROR(FOURIER_SERIES,"File [%s] OpenErr",file_name);
    }
    return res;
}
