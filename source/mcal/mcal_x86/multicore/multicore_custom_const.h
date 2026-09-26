#ifndef MULTICORE_CUSTOM_CONST_H
#define MULTICORE_CUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

/*see SCM_CORE_HOLD field descriptions*/
#define SCM_CORE_HOLD_MASK_CPU1_CORE_HOLD (0x00000002UL)
#define SCM_CORE_HOLD_MASK_CPU2_CORE_HOLD (0x00000004UL)

/*CPU1 SW Reset Control*/
typedef enum {
	Cx_SWRST_CPU_RESET = 1,/*Writing 1 to this field will issue a CPU1 reset*/
	Cx_SWRST_CPU_UNDEF = 0,/**/
}Cx_SWRST_t;




/* Write Permission*/
typedef enum {
    MC_WR_PERM_ALL_CPU    =0     , /*000b - All CPUs are allowed to access*/
    MC_WR_PERM_CPU0    =1 , /*001b - Only CPU0 is allowed to access*/
    MC_WR_PERM_CPU1=2, /*010b - Only CPU1 is allowed to access*/
    MC_WR_PERM_CPU2=3, /*011b - Only CPU2 is allowed to access*/
    MC_WR_PERM_NO_CPU    =4     , /*Others - No CPU is allowed to access*/
}MiltiCoreWritePermission_t;



/*
  RW
  This field controls CPUx CPU_WAIT signal.
  If assert core will not execute code.
 */
typedef enum {
	CPUx_CORE_NOT_HOLD_RELEASED = 0,  /* 0b - CPUx is not held and released*/
	CPUx_CORE_HOLD_NOT_RUNNING  = 1,  /* 1b - CPUx is held and not running*/
	CPUx_CORE_HOLD_UNDEF = 2,         /* */
}CPUx_CORE_HOLD_t;


/*
RW CPU1 Release Register
 */
typedef enum {
	Cx_RELEASE_RELEASE  = 1,  /* 1b Writing 1 to release CPU1. */
	Cx_RELEASE_UNDEF = 0,         /* */
}Cx_RELEASE_t;



#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_CUSTOM_CONST_H */
