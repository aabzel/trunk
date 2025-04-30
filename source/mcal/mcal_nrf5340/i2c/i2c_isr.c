#include "i2c_isr.h"

#include "i2c_types.h"
#include "i2c_drv.h"

static bool i2c_twim_evt_handler(I2cHandle_t* Node, nrfx_twim_evt_t const* p_event, void* p_context) {
	bool res = false;
    if(Node) {
        Node->it_cnt++;
        switch(p_event->type) {
        case NRFX_TWIM_EVT_DONE:
            Node->done_cnt++;
            Node->done_it = true;
            break;
        case NRFX_TWIM_EVT_ADDRESS_NACK:
            Node->error_cnt++;
            Node->error_nack_cnt++;
            break;
        case NRFX_TWIM_EVT_DATA_NACK:
            Node->error_cnt++;
            Node->error_data_cnt++;
            break;
        case NRFX_TWIM_EVT_OVERRUN:
            Node->error_cnt++;
            Node->error_overrun_cnt++;
            break;
        case NRFX_TWIM_EVT_BUS_ERROR:
            Node->error_cnt++;
            Node->error_bus_cnt++;
            break;
        }

        switch(p_event->xfer_desc.type) {
        case NRFX_TWIM_XFER_TX:
            if(p_event->xfer_desc.primary_length && p_event->xfer_desc.address) {
                Node->tx_cnt++;
                Node->tx_int=true;
            }
            break; ///< TX transfer.
        case NRFX_TWIM_XFER_RX:
            if(p_event->xfer_desc.primary_length && p_event->xfer_desc.address) {
                Node->rx_cnt++;
                Node->rx_int=true;;
            }
            break; ///< RX transfer.
        case NRFX_TWIM_XFER_TXRX: {
            Node->rx_cnt++;
            Node->tx_cnt++;
            Node->rx_int=true;;
            Node->tx_int=true;;
        }

        break; ///< TX transfer followed by RX transfer with repeated start.
        case NRFX_TWIM_XFER_TXTX:
            // Node->tx_cnt+=2;
            break; ///< TX transfer followed by TX transfer with repeated start.
        }
        res = true;
    }
    return res;
}

static void i2c_twim_evt_handler1(nrfx_twim_evt_t const* p_event, void* p_context) {
    I2cHandle_t* Node = I2cGetNode(1);
    if(Node) {
    	i2c_twim_evt_handler(Node, p_event, p_context) ;
    }
}

static void i2c_twim_evt_handler2(nrfx_twim_evt_t const* p_event, void* p_context) {
    I2cHandle_t* Node = I2cGetNode(2);
    if(Node) {
    	i2c_twim_evt_handler(Node, p_event, p_context) ;
    }
}

static void i2c_twim_evt_handler3(nrfx_twim_evt_t const* p_event, void* p_context) {
    I2cHandle_t* Node = I2cGetNode(3);
    if(Node) {
    	i2c_twim_evt_handler(Node, p_event, p_context) ;
    }
}

static void i2c_twim_evt_handler4(nrfx_twim_evt_t const* p_event, void* p_context) {
    I2cHandle_t* Node = I2cGetNode(4);
    if(Node) {
    	i2c_twim_evt_handler(Node, p_event, p_context) ;
    }
}


nrfx_twim_evt_handler_t I2cNum2IsrHandler(uint8_t num){
	nrfx_twim_evt_handler_t fun=NULL;
	switch(num){
	case 1: fun=i2c_twim_evt_handler1; break;
	case 2: fun=i2c_twim_evt_handler2; break;
	case 3: fun=i2c_twim_evt_handler3; break;
	case 4: fun=i2c_twim_evt_handler4; break;
	default:
		//LOG_ERROR(I2C,"UndefErr %u",num);
        break;
	}
	return fun;
}

