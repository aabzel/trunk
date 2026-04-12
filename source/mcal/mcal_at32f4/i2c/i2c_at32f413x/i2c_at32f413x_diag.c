#include "i2c_at32f413x_diag.h"

#include <stdio.h>
#include <string.h>

#include "data_utils.h"
#include "i2c_mcal.h"
#include "mcal_types.h"

const Reg32_t I2cReg[] = {
    {
        .valid = true,
        .offset = 0x00,
        .name = "I2C_CTRL1",
    },
    {
        .valid = true,
        .offset = 0x04,
        .name = "I2C_CTRL2",
    },
    {
        .valid = true,
        .offset = 0x08,
        .name = "I2C_OADDR1",
    },
    {
        .valid = true,
        .offset = 0x0C,
        .name = "I2C_OADDR2",
    },
    {
        .valid = true,
        .offset = 0x10,
        .name = "I2C_DT",
    },
    {
        .valid = true,
        .offset = 0x14,
        .name = "I2C_STS1",
    },
    {
        .valid = true,
        .offset = 0x18,
        .name = "I2C_STS2",
    },
    {
        .valid = true,
        .offset = 0x1C,
        .name = "I2C_CLKCTRL",
    },
    {
        .valid = true,
        .offset = 0x20,
        .name = "I2C_TMRISE",
    },
};

uint32_t i2c_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(I2cReg);
    return cnt;
}

const char* I2cAt32f413xRegSts1ToStr(const I2cAt32F413xRegSts1_t* const Node) {
    static char text[150] = "";
    if(Node) {
        strcpy(text, "");
        if(Node->stopf) {
            snprintf(text, sizeof(text), "%s,stopf", text);
        }
        if(Node->tmout) {
            snprintf(text, sizeof(text), "%s,tmout", text);
        }
        if(Node->alertf) {
            snprintf(text, sizeof(text), "%s,alertf", text);
        }
        if(Node->tdbe) {
            snprintf(text, sizeof(text), "%s,tdbe", text);
        }
        if(Node->pecerr) {
            snprintf(text, sizeof(text), "%s,pecerr", text);
        }
        if(Node->arlost) {
            snprintf(text, sizeof(text), "%s,arlost", text);
        }
        if(Node->buserr) {
            snprintf(text, sizeof(text), "%s,buserr", text);
        }
        if(Node->ouf) {
            snprintf(text, sizeof(text), "%s,ouf", text);
        }
        if(Node->ackfail) {
            snprintf(text, sizeof(text), "%s,ackfail", text);
        }
        if(Node->rdbf) {
            snprintf(text, sizeof(text), "%s,rdbf", text);
        }
        if(Node->addrhf) {
            snprintf(text, sizeof(text), "%s,addrhf", text);
        }
        if(Node->tdc) {
            snprintf(text, sizeof(text), "%s,tdc", text);
        }
        if(Node->addr7f) {
            snprintf(text, sizeof(text), "%s,addr7f", text);
        }
        if(Node->startf) {
            snprintf(text, sizeof(text), "%s,startf", text);
        }
    }
    return text;
}

const char* I2cAt32f413xRegSts2ToStr(const I2cAt32F413xRegSts2_t* const Node) {
    static char text[150] = "";
    if(Node) {
        strcpy(text, "");
        if(Node->trmode) {
            snprintf(text, sizeof(text), "%s,trmode", text);
        }
        if(Node->busyf) {
            snprintf(text, sizeof(text), "%s,busyf", text);
        }
        if(Node->dirf) {
            snprintf(text, sizeof(text), "%s,dirf", text);
        }
        if(Node->gcaddrf) {
            snprintf(text, sizeof(text), "%s,gcaddrf", text);
        }
        if(Node->devaddrf) {
            snprintf(text, sizeof(text), "%s,devaddrf", text);
        }
        if(Node->hostaddrf) {
            snprintf(text, sizeof(text), "%s,hostaddrf", text);
        }
        if(Node->addr2f) {
            snprintf(text, sizeof(text), "%s,addr2f", text);
        }
        if(Node->pecval) {
            snprintf(text, sizeof(text), "%s,pecval", text);
        }
    }
    return text;
}
