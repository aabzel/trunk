/*
 * config.h
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define ALLOW_PRIMARY_BOOT_CMD		true					// [bool] enables the receiving of the primary bootloader activation command
#define BOOT_CAN_RX_ID1				( 770 )					// primary bootloader CAN standard Id 1
#define BOOT_CAN_RX_ID2				( 2020 )				// primary bootloader CAN standard Id 2
#define BOOT_CAN_RX_ID3				( 6 )					// primary bootloader CAN standard Id 3
#define BOOT_ACTIVATION_STR			"BOOT_CMD"				// primary bootloader activation command

#define XCP_ON_CAN					false					// [bool] specifies XCP on CAN usage
#define UDS_ON_CAN					false					// [bool] specifies UDS on CAN usage



/* ---------------------------------------------------------------------------*/
/* PARAMETERS VALIDATION -----------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#if		defined(BOOT_CAN_RX_ID1) \
	 && ( ( BOOT_CAN_RX_ID1 >= 2047 ) || ( BOOT_CAN_RX_ID1 < 0 ) )
#error INVALID CAN ID1 CONFIGURATION
#endif
#if		defined(BOOT_CAN_RX_ID2) \
	 && ( ( BOOT_CAN_RX_ID2 >= 2047 ) || ( BOOT_CAN_RX_ID2 < 0 ) )
#error INVALID CAN ID2 CONFIGURATION
#endif
#if		defined(BOOT_CAN_RX_ID3) \
	 && ( ( BOOT_CAN_RX_ID3 >= 2047 ) || ( BOOT_CAN_RX_ID3 < 0 ) )
#error INVALID CAN ID3 CONFIGURATION
#endif
#if		defined(BOOT_CAN_RX_ID4) \
	 && ( ( BOOT_CAN_RX_ID4 >= 2047 ) || ( BOOT_CAN_RX_ID4 < 0 ) )
#error INVALID CAN ID4 CONFIGURATION
#endif



#endif /* CONFIG_H_ */
