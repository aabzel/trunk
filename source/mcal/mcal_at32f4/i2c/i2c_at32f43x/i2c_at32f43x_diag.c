#include "i2c_at32f43x_diag.h"

#include <stdio.h>
#include <string.h>

#include "data_utils.h"
#include "i2c_mcal.h"
#include "mcal_types.h"

// Table 11-8 I2C register map and reset values
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
        .name = "I2C_CLKCTRL",
    },
    {
        .valid = true,
        .offset = 0x14,
        .name = "I2C_TIMEOUT",
    },
    {
        .valid = true,
        .offset = 0x18,
        .name = "I2C_STS",
    },
    {
        .valid = true,
        .offset = 0x1C,
        .name = "I2C_CLR",
    },
    {
        .valid = true,
        .offset = 0x20,
        .name = "I2C_PEC",
    },
    {
        .valid = true,
        .offset = 0x24,
        .name = "I2C_RXDT",
    },
    {
        .valid = true,
        .offset = 0x28,
        .name = "I2C_TXDT",
    },
};

uint32_t i2c_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(I2cReg);
    return cnt;
}

const char* I2cAt32f43xRegStsToStr(const I2cAt32F43xRegSts_t* const Node) {
    static char text[250] = "";
    if(Node) {
        strcpy(text, "");
        if(Node->stopf) {
            snprintf(text, sizeof(text), "%s,stopf", text);
        }
        if(Node->tdis) {
            snprintf(text, sizeof(text), "%s,tdis", text);
        }
        if(Node->tdbe) {
            snprintf(text, sizeof(text), "%s,tdbe", text);
        }
        if(Node->tmout) {
            snprintf(text, sizeof(text), "%s,tmout", text);
        }
        if(Node->alertf) {
            snprintf(text, sizeof(text), "%s,alertf", text);
        }
        if(Node->ackfailf) {
            snprintf(text, sizeof(text), "%s,ackfailf", text);
        }
        if(Node->pecerr) {
            snprintf(text, sizeof(text), "%s,pecerr", text);
        }
        if(Node->arlost) {
            snprintf(text, sizeof(text), "%s,arlost", text);
        }
        if(Node->ouf) {
            snprintf(text, sizeof(text), "%s,ouf", text);
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
        if(Node->tcrld) {
            snprintf(text, sizeof(text), "%s,tcrld", text);
        }
        if(Node->busyf) {
            snprintf(text, sizeof(text), "%s,busyf", text);
        }
        if(Node->buserr) {
            snprintf(text, sizeof(text), "%s,buserr", text);
        }
        if(Node->sdir) {
            snprintf(text, sizeof(text), "%s,sdir", text);
        }
    }
    return text;
}
