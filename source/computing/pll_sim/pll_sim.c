#include "pll_sim.h"

#include <math.h>

/*PLL_SIM receiver invariant component*/
#include "vector_math.h"
#include "pll_sim_diag.h"
#include "fir.h"
#include "log.h"
#include "code_generator.h"
#include "clock_divider.h"
#include "clock_divider.h"

COMPONENT_GET_NODE(PllSim, pll_sim)
COMPONENT_GET_CONFIG(PllSim, pll_sim)

bool pll_sim_divider_set(uint8_t num, uint32_t divider) {
    bool res= false;
    PllSimHandle_t* Node = PllSimGetNode( num);
    if(Node) {
        res = fir_reset_one(Node->fir_num);
        Node->divider = divider;
        Node->SfbOld.i = 0;
        Node->SfbOld.q = 0;
        res = true;
    }
    return res;
}


double pll_sim_phase_detector(IqSample_t* const Lo, IqSample_t* const Fb){
    double phase_error_deg = 0.0;
    double phase_error_abs_deg = 0.0;
    Vector_t v1={ .dx=Lo->i,.dy=Lo->q, .dz=0.0,};
    Vector_t v2={ .dx=Fb->i,.dy=Fb->q, .dz=0.0,};
    phase_error_deg =  calc_angle_between_vectors_deg(&v1, &v2);
    phase_error_abs_deg = phase_error_deg;
   // phase_error_abs_deg = fabs(phase_error_deg);
    LOG_PARN(PLL_SIM, "PhaseErr:%f,Abs:%f Deg", phase_error_deg,phase_error_abs_deg);
    //phase_error_deg =  calc_angle_between_vectors_naiv_deg(&v1, &v2); // err
    return phase_error_abs_deg;
}

double sign_v(double value) {
	double sign_val = 0.0;
    if(0.0 <= value) {
        sign_val = 1.0;
    } else if(value < 0.0) {
        sign_val = -1.0;
    } else {
    }

    return sign_val;
}
#if 0
#define IIR_A  0.99 /*0  < a  <1*/
//#define IIR_A  0.001 /*0  < a  <1*/
static bool iir_proc_in_out(uint8_t num,  double x_n, double* vco_in_deg){
    bool res = true;
    static double y_m_1=0.0;
    double y_n=0.0;

    y_n=-IIR_A*y_m_1+x_n;
    y_m_1=y_n;

    * vco_in_deg=y_n;
    return res;
}
#endif

#define HAS_LO_SIGNAL_SIN 1
#define HAS_FB_SIGNAL_SIN 1
#define PLL_AMP 200.0
bool pll_sim_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(PLL_SIM, "Proc:%u", num);
    PllSimHandle_t* Node = PllSimGetNode(  num);
    if (Node) {
    	LOG_DEBUG(PLL_SIM, "%s", PllSinNodeToStr(Node));

    	Node->up_time_s = ((double)Node->sample_cnt)*Node->sample_time_s;
    	double lo_phase_rad = 0.0;
    	double step_rad = 0.0;
    	step_rad = ((((double)(2.0 * Node->lo_frequency_hz))) * M_PI) / ((double)Node->sample_frequency_hz);
        //phase_s = step * ((double)Node->sample_cnt)+ M_PI; err
        lo_phase_rad = step_rad * ((double)Node->sample_cnt)+ deg_to_rad(0.0);
#ifdef HAS_LO_SIGNAL_SIN
        Node->Lo.i= PLL_AMP*cos(lo_phase_rad);
        Node->Lo.q= PLL_AMP*sin(lo_phase_rad);
#endif

#if SIGNAL_SQUARE
#error erer
            Node->Lo.i= PLL_AMP*sign_v(cos(lo_phase_rad));
            Node->Lo.q= PLL_AMP*sign_v(sin(lo_phase_rad));
#endif

        //Node->phase_err_deg =  -pll_sim_phase_detector(&Node->Lo,&Node->SfbOld);
        Node->phase_err_deg =  pll_sim_phase_detector(&Node->SfbOld,&Node->Lo);

        res = fir_proc_in_out(Node->fir_num,  Node->phase_err_deg, &Node->vco_in_deg);
        if (res) {
#ifdef HAS_PID
#error erer
        	Node->vco_in_diff_deg = Node->vco_in_deg-Node->vco_in_prev_deg;
            Node->out_frequency_hz = Node->vco_p * Node->vco_in_deg+
            		Node->vco_i*Node->vco_in_int_deg+
					Node->vco_d*Node->vco_in_diff_deg; // works in up
#endif
            //Node->vco_in_deg = fabs(Node->vco_in_deg);
            Node->out_frequency_hz = Node->vco_p * Node->vco_in_deg ;// ok ->s

            double out_step_rad = ((((double)(2.0 * Node->out_frequency_hz))) * M_PI) / ((double)Node->sample_frequency_hz);
            double out_phase_rad = out_step_rad * ((double)(Node->sample_cnt)) ;
            Node->sOut.i= PLL_AMP*sign_v(cos(out_phase_rad));
            Node->sOut.q= PLL_AMP*sign_v(sin(out_phase_rad));

            //Node->out_frequency_hz = abs(Node->out_frequency_hz );
            Node->fb_frequency_hz = Node->out_frequency_hz /((double)Node->divider);
            double fb_step_rad = ((((double)(2.0 * Node->fb_frequency_hz))) * M_PI) / ((double)Node->sample_frequency_hz);
            double fb_phase_rad = fb_step_rad * ((double)(Node->sample_cnt)) ;
#ifdef HAS_FB_SIGNAL_SIN
            Node->SfbCur.i= PLL_AMP*(cos(fb_phase_rad));
            Node->SfbCur.q= PLL_AMP*(sin(fb_phase_rad));
#endif

#if SIGNAL_SQUARE
            Node->SfbCur.i= PLL_AMP*sign_v(cos(fb_phase_rad));
            Node->SfbCur.q= PLL_AMP*sign_v(sin(fb_phase_rad));
#endif

#ifdef HAS_PRESICE_CLOCK_DIV
            res = clock_divider_proc_one(1, Node->sOut.i, &Node->SfbCur.i);
            if(false==res){
            	LOG_ERROR(PLL_SIM,"ClockDivErr");
            }
            res = clock_divider_proc_one(2, Node->sOut.q, &Node->SfbCur.q);
            if(false==res){
            	LOG_ERROR(PLL_SIM,"ClockDivErr");
            }
#endif
            Node->vco_in_prev_deg = Node->vco_in_deg;
        }else{
        	LOG_ERROR(PLL_SIM,"FirErr");
        }

        Node->sample_cnt++;

        Node->SfbOld=Node->SfbCur;
    }
    return res;
}

bool pll_sim_init_custom(void) {
	bool res = true ;
	log_level_get_set(PLL_SIM, LOG_LEVEL_INFO  );
	log_level_get_set(FIR, LOG_LEVEL_INFO  );
	return res;
}

bool pll_sim_init_one(uint8_t num) {
    LOG_WARNING(PLL_SIM, "INIT:%u", num);
    bool res = false;
    const PllSimConfig_t* Config = PllSimGetConfig(num);
    if(Config) {
        LOG_WARNING(PLL_SIM, "%s", PllSinConfigToStr(Config));
        PllSimHandle_t* Node = PllSimGetNode(num);
        if(Node) {
            Node->lo_frequency_hz = Config->lo_frequency_hz;
            Node->sample_frequency_hz = Config->sample_frequency_hz;
            Node->divider = Config->divider;
            Node->fir_num = Config->fir_num;
            Node->vco_p = Config->vco_p;
            Node->vco_d = Config->vco_d;
            Node->vco_i = Config->vco_i;
            Node->num = Config->num;
            Node->valid = true;
            Node->sample_cnt = 0;

           	log_level_get_set(FIR, LOG_LEVEL_DEBUG  );
            res= fir_synthesize(Node->fir_num , 100, 2, Config->sample_frequency_hz);



            Node->vco_in_int_deg = 0.0;
            Node->out_frequency_hz = 0.0;
            Node->sample_time_s = 1.0 / ((double)Node->sample_frequency_hz);
            Node->fb_frequency_hz = 0.0;
        	log_level_get_set(FIR, LOG_LEVEL_INFO  );
        	log_level_get_set(PLL_SIM, LOG_LEVEL_DEBUG  );
        	//log_level_get_set(MATH, LOG_LEVEL_INFO  );
            res = true;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(PLL_SIM, PLL_SIM, pll_sim)
COMPONENT_PROC_PATTERT(PLL_SIM, PLL_SIM, pll_sim)
