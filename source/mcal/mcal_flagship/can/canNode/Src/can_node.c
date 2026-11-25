/*
 * CAN_node.c
 *
 *  Created on: Sep 11, 2023
 *      Author: karbovskiy
 *  Modified on: Oct 6, 2025
 *      Author: karbovskiy
 */


/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#ifdef UART_CLI
#include "debug_print.h"
#endif
#include "can.h"
#if defined( XCP_ON_CAN ) && ( _EXPAND( XCP_ON_CAN ) != 1 )
#include "XCP_on_CAN.h"
#endif
#if defined( UDS_ON_CAN ) && ( _EXPAND( UDS_ON_CAN ) != 1 )
#include "UDS_on_CAN.h"
#endif
#include "can_error.h"
#include "can_packets.h"
#include "can_node.h"
#include <string.h>



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern FLEXCAN_HandleType hCan0;
extern J1939tp_t J1939tp0;
extern canTxSlots_t canTxSlots0;

extern FLEXCAN_HandleType hCan3;
#ifdef HAS_J1939
extern J1939tp_t J1939tp3;
#endif /*HAS_J1939*/
extern canTxSlots_t canTxSlots3;

extern FLEXCAN_HandleType hCan4;
#ifdef HAS_J1939
extern J1939tp_t J1939tp4;
#endif /*HAS_J1939*/
extern canTxSlots_t canTxSlots4;



/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/  

#define FLEXCAN_IRQS			{FlexCAN0_IRQn, FlexCAN1_IRQn, FlexCAN2_IRQn, FlexCAN3_IRQn, FlexCAN4_IRQn, FlexCAN5_IRQn, FlexCAN6_IRQn, FlexCAN7_IRQn, FlexCAN8_IRQn, FlexCAN9_IRQn}



/* ---------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

static void CAN_Handler( canNode_t *pNode );
__WEAK void CAN_RxCallback( FLEXCAN_HandleType *pHandle, FLEXCAN_RxMsgType *pRxMsg );
__WEAK void CAN_FifoIssueCallback( FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue );
#ifdef HAS_J1939
__WEAK int32_t canJ1939RxHandler( FLEXCAN_RxMsgType *pRxMsg );
#endif
__WEAK int32_t canCustomRxHandler( canNode_t* const pNode, FLEXCAN_RxMsgType const * const pRxHeader );
__WEAK int32_t canBootRxHandler( FLEXCAN_RxMsgType const * const pRxMsg );


/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern canTxSlots_t canTxSlots0 ;
extern canTxSlots_t canTxSlots1 ;
extern canTxSlots_t canTxSlots2 ;
extern canTxSlots_t canTxSlots3 ;
extern canTxSlots_t canTxSlots4 ;
extern canTxSlots_t canTxSlots5 ;
extern canTxSlots_t canTxSlots6 ;
extern canTxSlots_t canTxSlots7 ;
extern canTxSlots_t canTxSlots8 ;
extern canTxSlots_t canTxSlots9 ;

canNodes_t canNodes =
{
#if ( CAN_NODE0_IS_USED > 0 )
	.n0 =
	{
		.hcan = &hCan0,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp0,
#endif
		.pTxSlots = &canTxSlots0,
	},
#endif
#if ( CAN_NODE1_IS_USED > 0 )
	.n1 =
	{
		.hcan = &hCan1,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp1,
#endif
		.pTxSlots = &canTxSlots1,
	},
#endif
#if ( CAN_NODE2_IS_USED > 0 )
	.n2 =
	{
		.hcan = &hCan2,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp2,
#endif
		.pTxSlots = &canTxSlots2,
	},
#endif
#if ( CAN_NODE3_IS_USED > 0 )
	.n3 =
	{
		.hcan = &hCan3,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp3,
#endif
		.pTxSlots = &canTxSlots3,
	},
#endif
#if ( CAN_NODE4_IS_USED > 0 )
	.n4 =
	{
		.hcan = &hCan4,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp4,
#endif
		.pTxSlots = &canTxSlots4,
	},
#endif
#if ( CAN_NODE5_IS_USED > 0 )
	.n5 =
	{
		.hcan = &hCan5,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp5,
#endif
		.pTxSlots = &canTxSlots5,
	},
#endif
#if ( CAN_NODE6_IS_USED > 0 )
	.n6 =
	{
		.hcan = &hCan6,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp6,
#endif
		.pTxSlots = &canTxSlots6,
	},
#endif
#if ( CAN_NODE7_IS_USED > 0 )
	.n7 =
	{
		.hcan = &hCan7,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp7,
#endif
		.pTxSlots = &canTxSlots7,
	},
#endif
#if ( CAN_NODE8_IS_USED > 0 )
	.n8 =
	{
		.hcan = &hCan8,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp8,
#endif
		.pTxSlots = &canTxSlots8,
	},
#endif
#if ( CAN_NODE9_IS_USED > 0 )
	.n9 =
	{
		.hcan = &hCan9,
#ifdef HAS_J1939
		.pJ1939tp = &J1939tp9,
#endif
		.pTxSlots = &canTxSlots9,
	},
#endif
};



/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

__WEAK
FLEXCAN_ErrorType CAN_NodeInit( canNode_t* pNode, uint32_t baudrate )
{
	FLEXCAN_HandleType *hcan = pNode->hcan;

	static const uint8_t s_aFlexCanEnhancedElementNums[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_ENHANCED_FIFO_ELEMENT_MAX_PTRS;
	const uint32_t enhancedElementNums = s_aFlexCanEnhancedElementNums[hcan->eInstance];

	FLEXCAN_FifoFilterType FifoFilters[enhancedElementNums];
	uint32_t fifofiltersAmount = 0;

#if ( XCP_ON_CAN > 0 )
	/* Configure a filter for the XCP exchange */
	FifoFilters[fifofiltersAmount++] = XCP_RxFilterSet();
#endif


#if ( UDS_ON_CAN > 0 )
	/* Configure UDS physical addressing response packet */
	udsResponseMsgInit();

	/* Configure filters for the UDS physical and functional addressing exchange */
	FifoFilters[fifofiltersAmount++] = UDS_RxFilterSet( N_TA_T_PHY );
	FifoFilters[fifofiltersAmount++] = UDS_RxFilterSet( N_TA_T_FUNC );
#endif

#ifdef HAS_J1939
	/* Configure a filter for the j1939 request message */
	const J1939_ID_t id_rqst =
	{
		.P = 0,						// any priority
		.PF = 0xEA,					// RQST only
		.PS = J1939_ECU_ADDR,		// fixed PS (destination address equal to ECU address)
		.SA = 0,					// any SA
	};
	const J1939_ID_t mask_rqst =
	{
		.P = 0,						// any priority
		.PF = 0xFF,					// RQST only
		.PS = 0xFF,					// fixed PS (destination address equal to ECU address)
		.SA = 0,					// any SA
	};
	FifoFilters[fifofiltersAmount++] = J1939ID_RxFilterSet( id_rqst, mask_rqst );


	/* Configure a filter for the j1939 transport protocol management messages */
	const J1939_ID_t id_tp =
	{
		.P = 0,						// any priority
		.PF = 0xEB & 0xEC,			// TPCM and TPDT
		.PS = 0xFF,					// broadcast only
		.SA = 0,					// any SA
	};
	const J1939_ID_t mask_tp =
	{
		.P = 0,						// any priority
		.PF = 0xF8,					// TPCM and TPDT
		.PS = 0xFF,					// broadcast only
		.SA = 0,					// any SA
	};
	FifoFilters[fifofiltersAmount++] = J1939ID_RxFilterSet( id_tp, mask_tp );


	/* Configure a filter for the j1939 group extension management messages */
	const J1939_ID_t id_ge =
	{
		.P = 0,						// any priority
		.PF = 0xF0,					// PDU2 only (240-255)
		.PS = 0,					// any PS
		.SA = 0,					// any SA
	};
	const J1939_ID_t mask_ge =
	{
		.P = 0,						// any priority
		.PF = 0xF0,					// PDU2 only (240-255)
		.PS = 0,					// any PS
		.SA = 0,					// any SA
	};
	FifoFilters[fifofiltersAmount++] = J1939ID_RxFilterSet( id_ge, mask_ge );


	/* Configure a filter for the j1939 messages filtered by destination address */
	const J1939_ID_t id_da =
	{
		.P = 0,						// any priority
		.PF = 0,					// any PF
		.PS = J1939_ECU_ADDR,		// fixed PS (destination address equal to ECU address)
		.SA = 0,					// any SA
	};
	const J1939_ID_t mask_da =
	{
		.P = 0,						// any priority
		.PF = 0,					// any PF
		.PS = 0xFF,					// fixed PS (destination address equal to ECU address)
		.SA = 0,					// any SA
	};
	FifoFilters[fifofiltersAmount++] = J1939ID_RxFilterSet( id_da,  mask_da );


	/* Configure a filter for the j1939 broadcast packets */
	const J1939_ID_t id_bc =
	{
		.P = 0,						// any priority
		.PF = 0,					// any PF
		.PS = 0xFF,					// fixed PS (broadcast)
		.SA = 0,					// any SA
	};
	const J1939_ID_t mask_bc =
	{
		.P = 0,						// any priority
		.PF = 0,					// any PF
		.PS = 0xFF,					// fixed PS (broadcast)
		.SA = 0,					// any SA
	};
	FifoFilters[fifofiltersAmount++] = J1939ID_RxFilterSet( id_bc, mask_bc );
#endif


#if ( ALLOW_PRIMARY_BOOT_CMD > 0 )
	/* Configure a filter for the primary boot activation command */
	FifoFilters[fifofiltersAmount++] = StdID_RxFilterSet( BOOT_CAN_RX_ID1, 0x7FF ); // at least one boot Rx ID required
#ifdef BOOT_CAN_RX_ID2
	FifoFilters[fifofiltersAmount++] = StdID_RxFilterSet( BOOT_CAN_RX_ID2, 0x7FF ); // set filter as 2nd boot Rx ID
#endif
#ifdef BOOT_CAN_RX_ID3
	FifoFilters[fifofiltersAmount++] = StdID_RxFilterSet( BOOT_CAN_RX_ID3, 0x7FF ); // set filter as 3rd boot Rx ID
#endif
#ifdef BOOT_CAN_RX_ID4
	FifoFilters[fifofiltersAmount++] = StdID_RxFilterSet( BOOT_CAN_RX_ID4, 0x7FF ); // set filter as 4th boot Rx ID
#endif
#endif

    /* Primary, the part of mailboxes are reserved for the legacy FIFO */
    uint32_t fifoFilterElements = 0;
    int32_t anyStdFilter = -1;
    for ( size_t i = 0; i < fifofiltersAmount; i++ )
    {
    	if ( FLEXCAN_ID_STD == FifoFilters[i].eRxFrameType )
    	{
    		fifoFilterElements += 1U;
    		anyStdFilter = i;
    	} //if
    	else
    	{
    		fifoFilterElements += 2U;
    	} //else
    } //for

	/* FIFO filter elements must me aligned to 2 */
	if( fifoFilterElements % 2 != 0 )
	{
		// use standard Id for cap
		FifoFilters[fifofiltersAmount++] = FifoFilters[anyStdFilter];
		fifoFilterElements += 1U;
	} //if

	/* check the FIFO filter elements limitation */
	if( fifoFilterElements >= enhancedElementNums )
	{
#ifdef UART_CLI
		Board_Debug_Print( _VALUE_TO_STR(CLI_RD) "CAN%u filters configuration is invalid\r\n", hcan->eInstance );
#endif
		return FLEXCAN_E_INVALID_PARAM;
	} //if

	hcan->tStatus.eStatusSeq = FLEXCAN_SEQUENCE_DEINIT;
	hcan->tSettings.pRxBuf = &(pNode->rxMsg);
	hcan->tSettings.pWakeMsg = NULL;
	hcan->tSettings.pErrorNotify = CAN_ErrorCallback;
	hcan->tSettings.pFifoIssueNotify = CAN_FifoIssueCallback;
	hcan->tSettings.pTxNotify = CAN_TxCallback;
	hcan->tSettings.pRxNotify = CAN_RxCallback;
	hcan->tSettings.pWakeNotify = NULL;

    FLEXCAN_InitType tInitCfg;
    tInitCfg.bListenOnly = 0U;
    tInitCfg.bEnErrInt = 1U;
    tInitCfg.bEnBusOffInt = 1U;
    tInitCfg.bEnBusOffDoneInt = 1U;
    tInitCfg.bEnWarningInt = 1U;

    tInitCfg.tRxFifoFilterCfg.bEnFifo = ( fifofiltersAmount > 0 ) ? 1U : 0U;

    /* enhanced FIFO */
    tInitCfg.tRxFifoFilterCfg.eFifoType = FLEXCAN_ENHANCED_FIFO;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bEnFifoDMA = 0U;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bDataAvaliableInt = 1U;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.u8FifoWaterMark = 0U;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bWaterMarkInt = 0U;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bOverflowInt = 1U;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bUnderflowInt = 0U;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.eFifoDataLength = FLEXCAN_DATAWIDTH_8;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt = fifofiltersAmount;
    tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList = FifoFilters;

    tInitCfg.bEnFd = false;

    static const uint8_t  s_aFlexCanMbNums[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_MB_NUM_PTRS;
    uint32_t MbNum = s_aFlexCanMbNums[hcan->eInstance];

    FLEXCAN_MbSettingType MailBoxSetting[MbNum];

    size_t mbIndex = 0U;

    /* Secondary, the mailboxes are assigned to the RX messages */
    // no non-FIFO Rx filters provided

    /* Finally, all remained mailboxes are assigned to the TX messages */
	if ( mbIndex >= MbNum )
	{
#ifdef UART_CLI
		Board_Debug_Print( _VALUE_TO_STR(CLI_YL) "CAN%u Warning: all MB are occupied by Rx filters\r\n", hcan->eInstance );
#endif
	} //if

    for ( ; mbIndex < MbNum; mbIndex++ )
    {
    	MailBoxSetting[mbIndex].bIsTxMB = 1U;
    	MailBoxSetting[mbIndex].bEnMBInt = 1U;
    }

    tInitCfg.tMbCfg.pMBList = MailBoxSetting;
    tInitCfg.tMbCfg.u8MBCnt = MbNum;

    /* pretended network */
    tInitCfg.tPnetCfg.bPNetEnable = 0;

    FLEXCAN_ErrorType FLEXCAN_Error = !FLEXCAN_E_OK;

    FLEXCAN_Error = BSP_CAN_LL_ProcessBaud( hcan->eInstance, &tInitCfg, baudrate );
	if ( FLEXCAN_E_OK != FLEXCAN_Error )
	{
#ifdef UART_CLI
		Board_Debug_Print( _VALUE_TO_STR(CLI_RD) "CAN%u Baud init failed = %u\r\n", hcan->eInstance, FLEXCAN_Error );
#endif
		return FLEXCAN_Error;
	}

    /* initial can */
	FLEXCAN_Error = FLEXCAN_Init( hcan, &tInitCfg );
	if ( FLEXCAN_E_OK != FLEXCAN_Error )
	{
#ifdef UART_CLI
		Board_Debug_Print( _VALUE_TO_STR(CLI_RD) "CAN%u Init failed = %u\r\n", hcan->eInstance, FLEXCAN_Error );
#endif
		return FLEXCAN_Error;
	}

	/* Start CAN */
	FLEXCAN_Error = FLEXCAN_Start( hcan );
	if ( FLEXCAN_E_OK != FLEXCAN_Error )
	{
#ifdef UART_CLI
		Board_Debug_Print( _VALUE_TO_STR(CLI_RD) "CAN%u Start failed = %u\r\n", hcan->eInstance, FLEXCAN_Error );
#endif
		return FLEXCAN_Error;
	}

	/* enable global interrupt for pCan */
	static const uint8_t  s_aFlexCanIrqs[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_IRQS;
	__NVIC_EnableIRQ( s_aFlexCanIrqs[hcan->eInstance] );

	return FLEXCAN_E_OK;

} //CAN_NodeInit()



inline void CAN_Step( void )
{
	// a cycle for each CAN node in the <canNodes> structure
	for ( canNode_t* pNode = (canNode_t*)&canNodes;
		  (uintptr_t)pNode < ( (uintptr_t)&canNodes + sizeof(canNodes) );
		  pNode++ )
	{
		CAN_Handler( pNode );
	} //for

} //CAN_Step()



canNode_t* Get_CAN_Node( FLEXCAN_HandleType *hcan )
{
	// a cycle for each CAN node in the <canNodes> structure
	for ( canNode_t* pNode = (canNode_t*)&canNodes;
		  (uintptr_t)pNode < ( (uintptr_t)&canNodes + sizeof(canNodes) );
		  pNode++ )
	{
		if ( hcan == pNode->hcan )
		{
			return pNode;
		} //if
	} //for

	Error_Handler(); // program error detected...
	return NULL;
} //Get_CAN_Node()



// custom extended id filter
inline
FLEXCAN_FifoFilterType ExtID_RxFilterSet( uint32_t const id, uint32_t const mask )
{
	FLEXCAN_FifoFilterType filter = {
		.eRxFrameType = FLEXCAN_ID_EXT,
		.u32RxCanId = id,
		.u32RxCanIdMask = mask,
	};
	return filter;
} //ExtID_RxFilterSet()



// custom standard id filter
inline
FLEXCAN_FifoFilterType StdID_RxFilterSet( uint16_t const id, uint16_t const mask )
{
	FLEXCAN_FifoFilterType filter = {
		.eRxFrameType = FLEXCAN_ID_STD,
		.u32RxCanId = id,
		.u32RxCanIdMask = mask,
	};
	return filter;
} //StdID_RxFilterSet()


#ifdef HAS_J1939
// j1939 custom id filter (via the mask)
inline
FLEXCAN_FifoFilterType J1939ID_RxFilterSet( J1939_ID_t const id, J1939_ID_t const mask )
{
	FLEXCAN_FifoFilterType filter = {
		.eRxFrameType = FLEXCAN_ID_EXT,
		.u32RxCanId = id.Extended,
		.u32RxCanIdMask = mask.Extended,
	};
	return filter;
} //J1939ID_RxFilterSet()
#endif



__WEAK
int32_t canCustomRxHandler( canNode_t* const pNode, FLEXCAN_RxMsgType const * const pRxMsg )
{
	PROCESS_UNUSED_VAR( pNode );
	PROCESS_UNUSED_VAR( pRxMsg );

	return -1;
}


#ifdef HAS_J1939
__WEAK
int32_t canJ1939RxHandler( FLEXCAN_RxMsgType *pRxMsg )
{
	int32_t match = 0;
	if ( CAN_ID_EXT != pRxMsg->eFrameType ) return -1; // filter mismatch

	const J1939_ID_t id = { .Extended = pRxMsg->u32CanId };
	if ( 0xF0 == ( id.PF & 0xF0 ) )
	{
		match = 1; // j1939 group extension match
	} //if
	else if ( J1939_ECU_ADDR == id.PS )
	{
		match = 2; // j1939 destination address match
	} //elif
	else if ( 0xFF == id.PS )
	{
		match = 3; // j1939 broadcast match
	} //elif
	else
	{
		return -1; // filter mismatch
	} //else

	return match; // filter matches

} //canJ1939RxHandler()
#endif



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

static void CAN_Handler( canNode_t *pNode )
{
	canTxHandler( pNode );
#ifdef HAS_J1939
	j1939tpHandler( pNode );
#endif

} //CAN_Handler()



__WEAK
void CAN_RxCallback( FLEXCAN_HandleType *pHandle, FLEXCAN_RxMsgType *pRxMsg )
{
	canNode_t* pNode = Get_CAN_Node( pHandle );
	int32_t matchResult;

#ifdef UART_CLI
	Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Data [%u] : ", pHandle->eInstance, pRxMsg->u32DataLen );
	for ( size_t i = 0; i < pRxMsg->u32DataLen; i++ )
	{
		Board_Debug_Print( "%x ", pRxMsg->aData[i] );
	}
	Board_Debug_Print( "\r\n" );

#if ( XCP_ON_CAN > 0 )
	matchResult = ReceiveXCPmsg( pNode, pRxMsg );
	if ( matchResult >= 0 )
	{
		Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (XCP)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
		return;
	}
#endif

#if ( UDS_ON_CAN > 0 )
	matchResult = ReceiveUDSmsg( pNode, pRxMsg );
	if ( matchResult >= 0 )
	{
		Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (UDS)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
		return;
	}
#endif

	matchResult = canCustomRxHandler( pNode, pRxMsg );
	if ( matchResult >= 0 )
	{
		Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (custom)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
		return;
	}

	matchResult = canJ1939RequestHandler( pNode, pRxMsg );
	if ( matchResult >= 0 )
	{
		Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (J1939 Req)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
		return;
	}

	matchResult = j1939tpGetRxPacket( pNode->pJ1939tp, pRxMsg );
	if ( matchResult >= 0 )
	{
		j1939tpGetRxPacket( pNode->pJ1939tp, pRxMsg );
		Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (J1939 TP)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
		return;
	}

	matchResult = canJ1939RxHandler( pRxMsg );
	if ( matchResult >= 0 )
	{
		switch ( matchResult )
		{

		case 1 :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (J1939 GE)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		case 2 :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (J1939 DA)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		case 3 :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (J1939 BC)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		default :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (J1939)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		} //switch
		return;
	} //if

	matchResult = canBootRxHandler( pRxMsg );
	if ( matchResult >= 0 )
	{
		switch ( matchResult )
		{

		case 1 :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (bootID1)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		case 2 :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (bootID2)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		case 3 :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (bootID3)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		case 4 :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (bootID4)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		default :
		{
			Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (boot)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
			break;
		}

		} //switch
		return;
	} //if

	Board_Debug_Print( _VALUE_TO_STR(CLI_CN) "CAN%u Rx Id = 0x%x (unknown)        \r\n", pHandle->eInstance, pRxMsg->u32CanId );
#else
#if ( XCP_ON_CAN > 0 )
	matchResult = ReceiveXCPmsg( pNode, pRxMsg );
	if ( matchResult >= 0 ) return;
#endif

#if ( UDS_ON_CAN > 0 )
	matchResult = ReceiveUDSmsg( pNode, pRxMsg );
	if ( matchResult >= 0 ) return;
#endif

	matchResult = canCustomRxHandler( pNode, pRxMsg );
	if ( matchResult >= 0 ) return;

#ifdef HAS_J1939
	matchResult = canJ1939RequestHandler( pNode, pRxMsg );
	if ( matchResult >= 0 ) return;

	matchResult = j1939tpGetRxPacket( pNode->pJ1939tp, pRxMsg );
	if ( matchResult >= 0 ) return;

	matchResult = canJ1939RxHandler( pRxMsg );
	if ( matchResult >= 0 ) return;
#endif

	matchResult = canBootRxHandler( pRxMsg );
	if ( matchResult >= 0 ) return;
#endif
} //CAN_RxCallback()


__WEAK
void CAN_FifoIssueCallback( FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue )
{
	PROCESS_UNUSED_VAR( pHandle );
	PROCESS_UNUSED_VAR( pFifoIssue );

} //CAN_FifoIssueCallback()



__WEAK
int32_t canBootRxHandler( FLEXCAN_RxMsgType const * const pRxMsg )
{
	int32_t match = 0;

#if ( ALLOW_PRIMARY_BOOT_CMD > 0 )
	if ( CAN_ID_STD != pRxMsg->eFrameType ) return -1; // filter mismatch

	if ( 0 ) { }
#ifdef BOOT_CAN_RX_ID1
	else if ( BOOT_CAN_RX_ID1 == pRxMsg->u32CanId )
	{
		match = 1; // boot ID1 match
	} //elif
#endif
#ifdef BOOT_CAN_RX_ID2
	else if ( BOOT_CAN_RX_ID2 == pRxMsg->u32CanId )
	{
		match = 2; // boot ID2 match
	} //elif
#endif
#ifdef BOOT_CAN_RX_ID3
	else if ( BOOT_CAN_RX_ID3 == pRxMsg->u32CanId )
	{
		match = 3; // boot ID3 match
	} //elif
#endif
#ifdef BOOT_CAN_RX_ID4
	else if ( BOOT_CAN_RX_ID4 == pRxMsg->u32CanId )
	{
		match = 4; // boot ID4 match
	} //elif
#endif
	else
	{
		return -1; // filter mismatch
	} //else

	// check for the bootloader mode entry command
	if ( 8 == pRxMsg->u32DataLen )
	{
		if ( 0 == strncmp( (char*)pRxMsg->aData, BOOT_ACTIVATION_STR, 8 ) )
		{
			NVIC_SystemReset();
			while ( 1 ) { };
		} //if
	} //if

	return match;
#endif

	return -1;
}
