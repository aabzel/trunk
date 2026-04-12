#include "can_isr.h"

#include "can_mcal.h"

bool can_isr_ll(CanHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->isr_done = true;
        Node->isr_cnt++;
        res = true;
    }
    return res;
}

bool can_isr(uint32_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->isr_done = true;
        Node->isr_cnt++;
        res = true;
    }
    return res;
}

bool can_isr_tx_done_ll(CanHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->tx_done = true;
        Node->tx_cnt++;
        res = true;
    }
    return res;
}

bool can_isr_tx_done(uint32_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_isr_tx_done_ll(Node);
    }
    return res;
}

bool can_isr_rx_done_ll(CanHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->rx_done = true;
        Node->rx_cnt++;
        res = true;
    }
    return res;
}

bool can_isr_rx_done(uint32_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_isr_rx_done_ll(Node);
    }
    return res;
}

bool can_isr_error_ll(CanHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->error = true;
        Node->error_cnt++;
        res = true;
    }
    return res;
}

bool can_isr_error(uint32_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_isr_error_ll(Node);
    }
    return res;
}
