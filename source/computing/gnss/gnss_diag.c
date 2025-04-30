#include "gnss_diag.h"

// http://traveleu.ru/map/GPSconverter.htm
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "std_includes.h"
#include "num_to_str.h"
#include "float_utils.h"
#include "utils_math.h"
#include "gnss_utils.h"
#include "log_utils.h"
#include "log.h"

//Check here
//https://dominoc925-pages.appspot.com/mapplets/cs_ecef.html
bool print_wgs84_coordinate(Wgs84Coordinate_t Wgs84Coordinate, bool one_line) {
    bool res = true;
    if(false == one_line) {
        cli_printf("x: %f m" CRLF, Wgs84Coordinate.x_cm/100.0);
        cli_printf("y: %f m" CRLF, Wgs84Coordinate.y_cm/100.0);
        cli_printf("z: %f m" CRLF, Wgs84Coordinate.z_cm/100.0);
        cli_printf("acc: %f m" CRLF, Wgs84Coordinate.acc_cm/100.0);
    }
    cli_printf("XYZ %f %f %f m Acc:%f m" CRLF,
              Wgs84Coordinate.x_cm/100.0,
              Wgs84Coordinate.y_cm/100.0,
              Wgs84Coordinate.z_cm/100.0,
              Wgs84Coordinate.acc_cm/100.0 );

    return res;
}

bool print_coordinate(char* prefix ,GnssCoordinate_t coordinate, bool one_line) {
    bool res = true;
    if(false == one_line) {
        if(prefix){
            cli_printf("%s" CRLF, prefix);
        }
        cli_printf("phi : %f " CRLF, coordinate.phi);
        cli_printf("lambda: %f " CRLF, coordinate.lambda);
    }
    if(prefix){
        cli_printf("%s %f %f" CRLF, prefix, coordinate.phi, coordinate.lambda);
    }else{
        cli_printf(" %f %f" CRLF, coordinate.phi, coordinate.lambda);
    }

    return res;
}

char* coordinate2str(void* value) {
    static char str[100] = "";
    GnssCoordinate_t dot={0,0};
    memcpy(&dot,value,sizeof(GnssCoordinate_t));
    if(value) {
        snprintf(str, sizeof(str), "%f;%f", dot.phi, dot.lambda);
    }
    return str;
}

const char* GnssCoordinateToStr(const GnssCoordinate_t* const Node){
    static char str[100] = "";
    if(Node) {
    	bool res = is_valid_gnss_coordinates(*Node);
    	if(res){
            snprintf(str, sizeof(str), "%6.3f;%6.3f", Node->phi, Node->lambda);
    	}else{
            strcpy(str, "Inval");
    	}
    }
    return str;
}

bool print_velocity(GnssVelocity_t velocity) {
    bool res = true;
    cli_printf("v_north: %f cm/s" CRLF, velocity.velocity_north);
    cli_printf("v_east: %f cm/s" CRLF, velocity.velocity_east);
    cli_printf("v_down: %f cm/s" CRLF, velocity.velocity_down);
    cli_printf("speed: %f cm/s" CRLF, velocity.speed);

    cli_printf("speed_ground: %f cm/s" CRLF, velocity.speed_ground);
    cli_printf("speed: %f +/-%f cm/s" CRLF, velocity.speed, velocity.accuracy_speed);
    cli_printf("course: %f +/-%f" CRLF, velocity.heading, velocity.accuracy_course);
    return res;
}

#define SECTOR_WIDTH_DEG 44.0
char* BearingDeg2Str(double value) {
    char *name="?";
    bool res = false;
    bool spot_dir = false;

    if(false==spot_dir){
        res= is_double_equal_absolute(value, 0.0, SECTOR_WIDTH_DEG);
        if(res){
            name="N";
            spot_dir = true;
        }
    }

    if(false==spot_dir){
        res= is_double_equal_absolute(value, 45.0, SECTOR_WIDTH_DEG);
        if(res){
            name="NE";
            spot_dir = true;
        }
    }

    if(false==spot_dir){
        res= is_double_equal_absolute(value, 180.0, SECTOR_WIDTH_DEG);
        if(res){
            name="S";
            spot_dir = true;
        }
    }
    if(false==spot_dir){
        res= is_double_equal_absolute(value, -180.0, SECTOR_WIDTH_DEG);
        if(res){
            name="S";
            spot_dir = true;
        }
    }
    if(false==spot_dir){
        res= is_double_equal_absolute(value, 90.0, SECTOR_WIDTH_DEG);
        if(res){
            name="E";
            spot_dir = true;
        }
    }
    if(false==spot_dir){
        res= is_double_equal_absolute(value, 135.0, SECTOR_WIDTH_DEG);
        if(res){
            name="SE";
            spot_dir = true;
        }
    }
    if(false==spot_dir){
        res= is_double_equal_absolute(value, -90.0, SECTOR_WIDTH_DEG);
         if(res){
             name="W";
             spot_dir = true;
         }
    }
    if(false==spot_dir){
        res= is_double_equal_absolute(value, -135.0, SECTOR_WIDTH_DEG);
         if(res){
             name="SW";
             spot_dir = true;
         }
    }
    if(false==spot_dir){
        res= is_double_equal_absolute(value, -45.0, SECTOR_WIDTH_DEG);
        if(res){
            name="NW";
            spot_dir = true;
        }
    }
    return name;
}

const char* SignalTypeToStr(SignalType_t sig_type){
	const char* name="?";
	switch(sig_type){
	case SIGNAL_SIN: name="SIN";break;
	case SIGNAL_COS: name="COS";break;
	default: break;
	}
    return name;
}

const char*  EscortInfoToStr(const GnssEscortInfo_t* const Node){
    static char str[100] = "";
    if(Node){
    	strcpy(str,"");
        //double time_s =( (double)Node->time_sample)/((double)Node->adc_sample_rate_hz);
        snprintf(str, sizeof(str), "PRN:%d,",  Node->prn );
        snprintf(str, sizeof(str), "%sTime:%s s,", str, DoubleToStr(Node->time_s) );
        snprintf(str, sizeof(str), "%sPhase:%4d Sam,",str, Node->prn_phase_sample );
        snprintf(str, sizeof(str), "%sDopp:%4.1f Hz,",str, Node->doppler_offset_hz );
        snprintf(str, sizeof(str), "%sCorr:%4d,", str, Node->correlation_value );
        snprintf(str, sizeof(str), "%sNH:%4.1f,", str, Node->noncoherent);
        snprintf(str, sizeof(str), "%sNHF:%4.1f,", str, Node->filt_noncoherent);

    }
    return str;
}

const char* SdrCorrToStr(const SdrCorrRes_t* const Node){
    static char str[100] = "";
    if(Node){
    	strcpy(str,"");
        snprintf(str, sizeof(str), "%sAbs:%5d,", str, Node->abs );
        snprintf(str, sizeof(str), "%sArgD:%4d,", str, (int16_t) rad_2_deg(Node->arg) );
        snprintf(str, sizeof(str), "%sI:%5d,", str, Node->correlation_i );
        snprintf(str, sizeof(str), "%sQ:%5d", str, Node->correlation_q );
    }
    return str;
}

const char* SdrEplToStr(const SdrEPL_t* const Node){
    static char str[150] = "";
    if(Node){
    	strcpy(str,"");
        snprintf(str, sizeof(str), "%sE:%s,", str,SdrCorrToStr(&Node->Early));
        snprintf(str, sizeof(str), "%sP:%s,", str,SdrCorrToStr(&Node->Present));
        snprintf(str, sizeof(str), "%sL:%s,", str,SdrCorrToStr(&Node->Late));

    }
    return str;
}
