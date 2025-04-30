#ifndef RDS_DEPEN_H
#define RDS_DEPEN_H


#ifndef HAS_CONNECTIVITY
#error "+HAS_CONNECTIVITY"
#endif


#ifndef HAS_FM_TUNER
#error "+HAS_FM_TUNER"
#endif

#ifndef HAS_PROTOCOLS
#error "+HAS_PROTOCOLS"
#endif

#ifndef HAS_RDS
#error "+HAS_RDS"
#endif


#ifdef __cplusplus
}
#endif

#endif /* RDS_DEPEN_H */
