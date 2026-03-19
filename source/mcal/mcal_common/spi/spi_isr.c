#include "spi_isr.h"

#include "spi_mcal.h"

static bool SpiCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        res = true;
    }
    return res;
}

static bool SpiTxCpltCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiCallBackLL(Node);

        Node->tx_cnt++;
        Node->tx_done = true;
        res = true;
    }
    return res;
}

static bool SpiRxCpltCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiCallBackLL(Node);

        Node->rx_cnt++;
        Node->rx_done = true;
        res = true;
    }
    return res;
}

static bool SpiTxRxCpltCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiRxCpltCallBackLL(Node);
        SpiTxCpltCallBackLL(Node);
        Node->txrx_cnt++;
        Node->txrx_done = true;
        res = true;
    }
    return res;
}

static bool SpiMoveStartCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        /*SpiMoveStartCallBackLL is not ISR*/
        Node->start_cnt++;
        Node->start_done = true;
        res = true;
    }
    return res;
}

/*
 Some microcontrollers (FC7300x) do not have separate interrupts for receiving or transmitting.
 Just one move-done interrupt.
 There you need to explicitly indicate to the interrupt what is happening by bypassing a RAM variable.
 */
static bool SpiIsrProcOperation(SpiHandle_t* const Node) {
    bool res = false;
    switch(Node->operation) {
    case INTERFACE_OPERATION_IDLE:
        /*There is an interruption that we didn't even expect.*/
        Node->error_done = true;
        Node->error_cnt++;
        res = false;
        break;
    case INTERFACE_OPERATION_RECEPTION:
        res = SpiRxCpltCallBackLL(Node);
        break;
    case INTERFACE_OPERATION_SEND:
        res = SpiTxCpltCallBackLL(Node);
        break;
    case INTERFACE_OPERATION_RECEPTION_AND_TRANSMISSION:
        res = SpiTxRxCpltCallBackLL(Node);
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool SpiMoveCpltCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiCallBackLL(Node);
        Node->move_cnt++;
        Node->move_done = true;
        res = SpiIsrProcOperation(Node);
    }
    return res;
}

static bool SpiErrorCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiCallBackLL(Node);

        Node->error_cnt++;
        Node->error_done = true;
        res = true;
    }
    return res;
}

static bool SpiTxHalfCpltCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiCallBackLL(Node);

        Node->tx_half_cnt++;
        Node->tx_half_done = true;
        res = true;
    }
    return res;
}

static bool SpiRxHalfCpltCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiCallBackLL(Node);

        Node->rx_half_cnt++;
        Node->rx_half_done = true;
        res = true;
    }
    return res;
}

static bool SpiTxRxHalfCpltCallBackLL(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiTxHalfCpltCallBackLL(Node);
        SpiRxHalfCpltCallBackLL(Node);
        res = true;
    }
    return res;
}

// Hi level API

bool SpiCallBackMoveStart(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiMoveStartCallBackLL(Node);
    }
    return res;
}

bool SpiCallBackError(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiErrorCallBackLL(Node);
    }
    return res;
}

bool SpiCallBackTxHalfCplt(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiTxHalfCpltCallBackLL(Node);
    }
    return res;
}

bool SpiCallBackTxCplt(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiTxCpltCallBackLL(Node);
    }
    return res;
}

bool SpiCallBackRxHalfCplt(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiRxHalfCpltCallBackLL(Node);
    }
    return res;
}

bool SpiCallBackRxCplt(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiRxCpltCallBackLL(Node);
    }
    return res;
}

bool SpiCallBackTxRxHalfCplt(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiTxRxHalfCpltCallBackLL(Node);
    }
    return res;
}

bool SpiCallBackTxRxCplt(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiTxRxCpltCallBackLL(Node);
    }
    return res;
}

bool SpiCallBackMoveCplt(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        res = SpiMoveCpltCallBackLL(Node);
    }
    return res;
}
