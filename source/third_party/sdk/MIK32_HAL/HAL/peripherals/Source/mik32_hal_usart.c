#include "mik32_hal_usart.h"

/*******************************************************************************
 * @brief Р�РЅРёС†РёР°Р»РёР·Р°С†РёСЏ Р»РёРЅРёР№ GPIO РјРѕРґСѓР»СЏ USART
 * @param setting СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ РЅР°СЃС‚СЂРѕРµРє РјРѕРґСѓР»СЏ USART
 * @return none
 */
__attribute__((weak)) void HAL_USART_MspInit(USART_HandleTypeDef* setting)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0}; 

    if (setting->Instance == UART_0)
    {
        __HAL_PCC_UART_0_CLK_ENABLE();
        /* TXD */
        if (setting->transmitting) GPIO_InitStruct.Pin |= GPIO_PIN_6;
        /* RXD */
        if (setting->receiving) GPIO_InitStruct.Pin |= GPIO_PIN_5;
        /* RTS */
        if (setting->Modem.rts) GPIO_InitStruct.Pin |= GPIO_PIN_8;
        /* CTS */
        if (setting->Modem.cts) GPIO_InitStruct.Pin |= GPIO_PIN_7;
        GPIO_InitStruct.Mode = HAL_GPIO_MODE_SERIAL;
        GPIO_InitStruct.Pull = HAL_GPIO_PULL_NONE;
        HAL_GPIO_Init(GPIO_0, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = 0;
        /* XCK */
        if (setting->mode == USART_MODE_SYNCHRONOUS) GPIO_InitStruct.Pin |= GPIO_PIN_5;
        /* DDIS */
        if (setting->Modem.ddis) GPIO_InitStruct.Pin |= GPIO_PIN_6;
        /* DTR */
        if (setting->Modem.dtr) GPIO_InitStruct.Pin |= GPIO_PIN_12;
        /* DCD */
        if (setting->Modem.dcd) GPIO_InitStruct.Pin |= GPIO_PIN_13;
        /* DSR */
        if (setting->Modem.dsr) GPIO_InitStruct.Pin |= GPIO_PIN_14;
        /* RI */
        if (setting->Modem.ri) GPIO_InitStruct.Pin |= GPIO_PIN_15;
        GPIO_InitStruct.Mode = HAL_GPIO_MODE_TIMER_SERIAL;
        GPIO_InitStruct.Pull = HAL_GPIO_PULL_NONE;
        HAL_GPIO_Init(GPIO_1, &GPIO_InitStruct);
    }

    if (setting->Instance == UART_1)
    {
        __HAL_PCC_UART_1_CLK_ENABLE();
        /* TXD */
        if (setting->transmitting) GPIO_InitStruct.Pin |= GPIO_PIN_9;
        /* RXD */
        if (setting->receiving) GPIO_InitStruct.Pin |= GPIO_PIN_8;
        /* RTS */
        if (setting->Modem.rts) GPIO_InitStruct.Pin |= GPIO_PIN_11;
        /* CTS */
        if (setting->Modem.cts) GPIO_InitStruct.Pin |= GPIO_PIN_10;
        GPIO_InitStruct.Mode = HAL_GPIO_MODE_SERIAL;
        GPIO_InitStruct.Pull = HAL_GPIO_PULL_NONE;
        HAL_GPIO_Init(GPIO_1, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = 0;
        /* XCK */
        if (setting->mode == USART_MODE_SYNCHRONOUS) GPIO_InitStruct.Pin |= GPIO_PIN_6;
        // /* DDIS */
        if (setting->Modem.ddis) GPIO_InitStruct.Pin |= GPIO_PIN_7;
        /* DTR */
        if (setting->Modem.dtr) GPIO_InitStruct.Pin |= GPIO_PIN_0;
        /* DCD */
        if (setting->Modem.dcd) GPIO_InitStruct.Pin |= GPIO_PIN_1;
        /* DSR */
        if (setting->Modem.dsr) GPIO_InitStruct.Pin |= GPIO_PIN_2;
        /* RI */
        if (setting->Modem.ri) GPIO_InitStruct.Pin |= GPIO_PIN_3;
        GPIO_InitStruct.Mode = HAL_GPIO_MODE_TIMER_SERIAL;
        GPIO_InitStruct.Pull = HAL_GPIO_PULL_NONE;
        HAL_GPIO_Init(GPIO_2, &GPIO_InitStruct);
    }
}


/*******************************************************************************
 * @brief Р�РЅРёС†РёР°Р»РёР·Р°С†РёСЏ РјРѕРґСѓР»СЏ USART
 * @param setting СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ РЅР°СЃС‚СЂРѕРµРє РјРѕРґСѓР»СЏ USART
 * @return HAL_OK or HAL_ERROR
 */
HAL_StatusTypeDef HAL_USART_Init(USART_HandleTypeDef* setting)
{
    __HAL_USART_Disable(setting);
    HAL_USART_MspInit(setting);
    /* CONTROL1 */
    uint32_t control1 = 0;
    if (setting->frame & 0b01)      control1 |= UART_CONTROL1_M0_M;
    if (setting->frame & 0b10)      control1 |= UART_CONTROL1_M1_M;
    if (setting->parity_bit)        control1 |= UART_CONTROL1_PCE_M;
    if (setting->parity_bit_inversion) control1 |= UART_CONTROL1_PS_M;
    if (setting->Interrupt.peie)    control1 |= UART_CONTROL1_PEIE_M;
    if (setting->Interrupt.txeie)   control1 |= UART_CONTROL1_TXEIE_M;
    if (setting->Interrupt.tcie)    control1 |= UART_CONTROL1_TCIE_M;
    if (setting->Interrupt.rxneie)  control1 |= UART_CONTROL1_RXNEIE_M;
    if (setting->Interrupt.idleie)  control1 |= UART_CONTROL1_IDLEIE_M;
    //Save data
    setting->Instance->CONTROL1 = control1;
    /* CONTROL2 */
    uint32_t control2 = 0;
    if (setting->bit_direction)     control2 |= UART_CONTROL2_MSBFIRST_M;
    if (setting->data_inversion)    control2 |= UART_CONTROL2_DATAINV_M;
    if (setting->tx_inversion)      control2 |= UART_CONTROL2_TXINV_M;
    if (setting->rx_inversion)      control2 |= UART_CONTROL2_RXINV_M;
    if (setting->swap)              control2 |= UART_CONTROL2_SWAP_M;
    if (setting->lbm)               control2 |= UART_CONTROL2_LBM_M;
    if (setting->stop_bit)          control2 |= UART_CONTROL2_STOP_1_M;
    if (setting->mode)              control2 |= UART_CONTROL2_CLKEN_M;
    if (setting->xck_mode & 0b10)   control2 |= UART_CONTROL2_CPOL_M;
    if (setting->xck_mode & 0b01)   control2 |= UART_CONTROL2_CPHA_M;
    if (setting->last_byte_clock)   control2 |= UART_CONTROL2_LBCL_M;
    if (setting->Interrupt.lbdie)   control2 |= UART_CONTROL2_LBDIE_M;
    //Save data
    setting->Instance->CONTROL2 = control2;
    /* CONTROL3 */
    uint32_t control3 = 0;
    if (setting->overwrite)         control3 |= UART_CONTROL3_OVRDIS_M;
    if (setting->Modem.cts)         control3 |= UART_CONTROL3_CTSE_M;
    if (setting->rts_mode)          control3 |= UART_CONTROL3_RTSE_M;
    if (setting->dma_tx_request)    control3 |= UART_CONTROL3_DMAT_M;
    if (setting->dma_rx_request)    control3 |= UART_CONTROL3_DMAR_M;
    if (setting->channel_mode)      control3 |= UART_CONTROL3_HDSEL_M;
    if (setting->tx_break_mode)     control3 |= UART_CONTROL3_BKRQ_M;
    if (setting->Interrupt.ctsie)   control3 |= UART_CONTROL3_CTSIE_M;
    if (setting->Interrupt.eie)     control3 |= UART_CONTROL3_EIE_M;
    setting->Instance->CONTROL3 = control3;
    /* MODEM */
    if (setting->Modem.dtr)         setting->Instance->MODEM |= UART_MODEM_DTR_M;

    /* Baudrate */
    setting->Instance->DIVIDER =( (HAL_PCC_GetSysClockFreq() / (PM->DIV_AHB+1) / (PM->DIV_APB_P+1)) /
        setting->baudrate )  -1 ;
    if (setting->Instance->DIVIDER < 16) return HAL_ERROR;
    
    /* Enable receiving & transmitting */
    if (setting->transmitting)      setting->Instance->CONTROL1 |= UART_CONTROL1_TE_M;
    if (setting->receiving)         setting->Instance->CONTROL1 |= UART_CONTROL1_RE_M;
    __HAL_USART_Enable(setting);

    /* Wait for module is ready */
    if (setting->transmitting)
        while(!HAL_USART_Read_TransmitEnableAck(setting));
    if (setting->receiving)
        while(!HAL_USART_Read_ReceiveEnableAck(setting));
    return HAL_OK;
}

/*******************************************************************************
 * @brief Р¤СѓРЅРєС†РёСЏ РїРµСЂРµРґР°С‡Рё 1 Р±Р°Р№С‚Р° РґР°РЅРЅС‹С… С‡РµСЂРµР· РёРЅС‚РµСЂС„РµР№СЃ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @param data 1 Р±Р°Р№С‚ РѕС‚РїСЂР°РІР»СЏРµРјС‹С… РґР°РЅРЅС‹С…
 * @return none
 */
bool HAL_USART_Transmit(USART_HandleTypeDef* local, char data, uint32_t timeout)
{
    if (timeout == USART_TIMEOUT_DEFAULT)
    {
        /* DIVIDER = Freq_APB_P / Baudrate, one bit periode = 1000000 / Baudrate us */
        //timeout = (local->Instance->DIVIDER * 1000 / (HAL_PCC_GetSysClockFreq()/(PM->DIV_AHB+1)/(PM->DIV_APB_P+1)/1000UL));
        timeout = 1000000UL / local->baudrate;
        uint32_t div = 2;
        switch (local->frame)
        {
            case UART_FRAME_7BIT: div += 7; break;
            case UART_FRAME_8BIT: div += 8; break;
            case UART_FRAME_9BIT: div += 9; break;
            default:  break;
        }
        switch (local->stop_bit)
        {
            case UART_STOP_BIT_1: div += 1; break;
            case UART_STOP_BIT_2: div += 2; break;
            default:  break;
        }
        timeout *= div;
    }
    HAL_USART_WriteByte(local, data);
    uint32_t time_stamp = HAL_Micros();
    while (!HAL_USART_TXC_ReadFlag(local))
    {
        if (HAL_Micros() - time_stamp > timeout) return false;
    }
    return true;
}

/*******************************************************************************
 * @brief Р¤СѓРЅРєС†РёСЏ РїРµСЂРµРґР°С‡Рё РјР°СЃСЃРёРІР° РґР°РЅРЅС‹С… С‡РµСЂРµР· РёРЅС‚РµСЂС„РµР№СЃ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @param buffer СѓРєР°Р·Р°С‚РµР»СЊ РЅР° РЅР°С‡Р°Р»Рѕ РјР°СЃСЃРёРІР°
 * @param len РґР»РёРЅР° РјР°СЃСЃРёРІР°
 * @return none
 */
bool HAL_USART_Write(USART_HandleTypeDef* local, char* buffer, uint32_t len, uint32_t timeout)
{
    bool n_error = true;
    for (uint32_t i=0; i<len; i++)
    {
        n_error &= HAL_USART_Transmit(local, buffer[i], timeout);
    }
    return n_error;
}

/*******************************************************************************
 * @brief Р¤СѓРЅРєС†РёСЏ РїРµСЂРµРґР°С‡Рё СЃС‚СЂРѕРєРё С‡РµСЂРµР· РёРЅС‚РµСЂС„РµР№СЃ USART. РЎС‚СЂРѕРєР° РѕР±СЏР·Р°С‚РµР»СЊРЅРѕ
 * РґРѕР»Р¶РЅР° РѕРєР°РЅС‡РёРІР°С‚СЊСЃСЏ СЃРёРјРІРѕР»РѕРј '\0'.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @param str СѓРєР°Р·Р°С‚РµР»СЊ РЅР° РЅР°С‡Р°Р»Рѕ СЃС‚СЂРѕРєРё
 * @return none
 */
bool HAL_USART_Print(USART_HandleTypeDef* local, char* str, uint32_t timeout)
{
    uint32_t i = 0;
    bool n_error = true;
    while (str[i] != '\0')
    {
        n_error &= HAL_USART_Transmit(local, str[i], timeout);
        i += 1;
    }
    return n_error;
}

/*******************************************************************************
 * @brief Р¤СѓРЅРєС†РёСЏ РїСЂРёРµРјР° 1 Р±Р°Р№С‚Р° РґР°РЅРЅС‹С… РїРѕ РёРЅС‚РµСЂС„РµР№СЃСѓ USART. Р¤СѓРЅРєС†РёСЏ РІРєР»СЋС‡Р°РµС‚ РІ
 * СЃРµР±СЏ С†РёРєР» РѕР¶РёРґР°РЅРёСЏ РїСЂРёРµРјР° РґР°РЅРЅС‹С… Рё С‡С‚РµРЅРёРµ РїРѕР»СѓС‡РµРЅРЅС‹С… РґР°РЅРЅС‹С….
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @param buf СѓРєР°Р·Р°С‚РµР»СЊ РЅР° РїРµСЂРµРјРµРЅРЅСѓСЋ-РїСЂРёРµРјРЅРёРє
 * @param timeout РјР°РєСЃРёРјР°Р»СЊРЅРѕРµ РІСЂРµРјСЏ С‚СЂР°РЅР·Р°РєС†РёРё (РІ РјРёРєСЂРѕСЃРµРєСѓРЅРґР°С…). РќРµ
 * СЂРµРєРѕРјРµРЅРґСѓРµС‚СЃСЏ РёСЃРїРѕР»СЊР·РѕРІР°РЅРёРµ Р·РЅР°С‡РµРЅРёСЏ USART_TIMEOUT_DEFAULT, С‚Р°Рє РєР°Рє РѕРЅРѕ РЅРµРЅР°РјРЅРѕРіРѕ
 * РїСЂРµРІС‹С€Р°РµС‚ РґР»РёРЅСѓ РѕРґРЅРѕР№ С‚СЂР°РЅР·Р°РєС†РёРё РїРѕ РІСЂРµРјРµРЅРё
 * @return Р•СЃР»Рё true, С‚СЂР°РЅР·Р°РєС†РёСЏ СѓСЃРїРµС€РЅР°, РµСЃР»Рё false - РѕС€РёР±РєР° timeout
 */
bool HAL_USART_Receive(USART_HandleTypeDef* local, char* buf, uint32_t timeout)
{
    if (timeout == USART_TIMEOUT_DEFAULT)
    {
        /* DIVIDER = Freq_APB_P / Baudrate, one bit periode = 1000000 / Baudrate us */
        //timeout = (local->Instance->DIVIDER * 1000 / (HAL_PCC_GetSysClockFreq()/(PM->DIV_AHB+1)/(PM->DIV_APB_P+1)/1000UL));
        timeout = 1000000UL / local->baudrate;
        uint32_t div = 2;
        switch (local->frame)
        {
            case UART_FRAME_7BIT: div += 7; break;
            case UART_FRAME_8BIT: div += 8; break;
            case UART_FRAME_9BIT: div += 9; break;
            default:  break;
        }
        switch (local->stop_bit)
        {
            case UART_STOP_BIT_1: div += 1; break;
            case UART_STOP_BIT_2: div += 2; break;
        }
        timeout *= div;
    }
    uint32_t time_stamp = HAL_Micros();
    while(!HAL_USART_RXNE_ReadFlag(local))
    {
        if (HAL_Micros() - time_stamp > timeout) return false;
    }
    *buf = HAL_USART_ReadByte(local);
    return true;
}

/*******************************************************************************
 * @brief Р¤СѓРЅРєС†РёСЏ РїСЂРёРµРјР° РјР°СЃСЃРёРІР° РґР°РЅРЅС‹С… РїРѕ РёРЅС‚РµСЂС„РµР№СЃСѓ USART.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @param buffer СѓРєР°Р·Р°С‚РµР»СЊ РЅР° РЅР°С‡Р°Р»Рѕ РјР°СЃСЃРёРІР°
 * @param len РґР»РёРЅР° РјР°СЃСЃРёРІР°
 * @return none
 */
bool HAL_USART_Read(USART_HandleTypeDef* local, char* buffer, uint32_t len, uint32_t timeout)
{
    bool n_error = true;
    for (uint32_t i=0; i<len; i++)
    {
        n_error &= HAL_USART_Receive(local, buffer+i, timeout);
    }
    return n_error;
}


/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° РіРѕС‚РѕРІРЅРѕСЃС‚Рё РїСЂРёРµРјР° РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true, РµСЃР»Рё С„Р»Р°Рі СѓСЃС‚Р°РЅРѕРІР»РµРЅ; false - РµСЃР»Рё СЃР±СЂРѕС€РµРЅ
 */
bool HAL_USART_Read_ReceiveEnableAck(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_REACK_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° РіРѕС‚РѕРІРЅРѕСЃС‚Рё РїРµСЂРµРґР°С‡Рё РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true, РµСЃР»Рё С„Р»Р°Рі СѓСЃС‚Р°РЅРѕРІР»РµРЅ; false - РµСЃР»Рё СЃР±СЂРѕС€РµРЅ
 */
bool HAL_USART_Read_TransmitEnableAck(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_TEACK_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ СЃРѕСЃС‚РѕСЏРЅРёСЏ Р»РёРЅРёРё CTS РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true, РµСЃР»Рё Р»РёРЅРёСЏ Р°РєС‚РёРІРЅР° (0); false - РµСЃР»Рё РЅРµ Р°РєС‚РёРІРЅР° (1)
 */
bool HAL_USART_CTS_ReadLevel(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_CTS_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° РёР·РјРµРЅРµРЅРёСЏ СЃРѕСЃС‚РѕСЏРЅРёСЏ Р»РёРЅРёРё CTS РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true, РµСЃР»Рё РёР·РјРµРЅРµРЅРёРµ СѓСЂРѕРІРЅСЏ РїСЂРѕРёР·РѕС€Р»Рѕ СЃРѕ РІСЂРµРјРµРЅРё РїРѕСЃР»РµРґРЅРµРіРѕ СЃР±СЂРѕСЃР°;
 * false - РµСЃР»Рё РёР·РјРµРЅРёСЏ РЅРµ Р±С‹Р»Рѕ
 */
bool HAL_USART_CTS_ReadToggleFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_CTSIF_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° С„РёРєСЃР°С†РёРё break-СЃРѕСЃС‚РѕСЏРЅРёСЏ РЅР° Р»РёРЅРёРё RX РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true, break-СЃРѕСЃС‚РѕСЏРЅРёРµ Р·Р°С„РёРєСЃРёСЂРѕРІР°РЅРѕ; false - РµСЃР»Рё РЅРµ Р±С‹Р»Рѕ
 */
bool HAL_USART_RX_ReadBreakFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_LBDF_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° TXРЎ ("РїРµСЂРµРґР°С‡Р° Р·Р°РІРµСЂС€РµРЅР°") РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_TXC_ReadFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_TC_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° TXE ("СЂРµРіРёСЃС‚СЂ РїРµСЂРµРґР°С‚С‡РёРєР° РїСѓСЃС‚") РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_TXE_ReadFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_TXE_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° RXNE ("СЂРµРіРёСЃС‚СЂ РїСЂРёРµРјРЅРёРєР° РЅРµ РїСѓСЃС‚") РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_RXNE_ReadFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_RXNE_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° IDLE РјРѕРґСѓР»СЏ USART.
 * Р¤Р»Р°Рі IDLE СѓСЃС‚Р°РЅР°РІР»РёРІР°РµС‚СЃСЏ РїСЂРё РѕС‚СЃСѓС‚СЃС‚РІРёРё Р°РєС‚РёРІРЅРѕСЃС‚Рё РЅР° Р»РёРЅРёРё RX РІ С‚РµС‡РµРЅРёРµ 8
 * Р±РёС‚РѕРІС‹С… С‚Р°РєС‚РѕРІ РїСЂРё СѓСЃС‚Р°РЅРѕРІР»РµРЅРЅРѕРј С„Р»Р°РіРµ RXNE.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_IDLE_ReadFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_IDLE_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° ORE РјРѕРґСѓР»СЏ USART.
 * Р¤Р»Р°Рі ORE СѓСЃС‚Р°РЅР°РІР»РёРІР°РµС‚СЃСЏ РїСЂРё РїРѕРїС‹С‚РєРµ РїРµСЂРµР·Р°РїРёСЃРё РїСЂРёРЅСЏС‚С‹С… РїРѕ RX РґР°РЅРЅС‹С….
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_ReceiveOverwrite_ReadFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_ORE_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° NF РјРѕРґСѓР»СЏ USART.
 * Р¤Р»Р°Рі NF СѓСЃС‚Р°РЅР°РІР»РёРІР°РµС‚СЃСЏ РїСЂРё РѕР±РЅР°СЂСѓР¶РµРЅРёРё Р»РѕР¶РЅС‹С… РїРµСЂРµРєР»СЋС‡РµРЅРёР№ РЅР° Р»РёРЅРёРё RX.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_NF_ReadFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_NF_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° FE РјРѕРґСѓР»СЏ USART.
 * Р¤Р»Р°Рі FE СѓСЃС‚Р°РЅР°РІР»РёРІР°РµС‚СЃСЏ РїСЂРё РѕР±РЅР°СЂСѓР¶РµРЅРёРё РѕС€РёР±РѕРє РІ СЃС‚РѕРї-Р±РёС‚Рµ (Р±РёС‚Р°С…).
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_StopBitError_ReadFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_FE_M) == 0) return false;
    else return true;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° PE РјРѕРґСѓР»СЏ USART.
 * Р¤Р»Р°Рі PE СѓСЃС‚Р°РЅР°РІР»РёРІР°РµС‚СЃСЏ РїСЂРё РѕР±РЅР°СЂСѓР¶РµРЅРёРё РѕС€РёР±РѕС‡РЅРѕРіРѕ Р±РёС‚Р° С‡РµС‚РЅРѕСЃС‚Рё.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_ParityError_ReadFlag(USART_HandleTypeDef* local)
{
    if ((local->Instance->FLAGS.dword & UART_FLAGS_PE_M) == 0) return false;
    else return true;
}


/*******************************************************************************
 * @brief РћС‚РїСЂР°РІРєР° 1 Р±Р°Р№С‚Р° РґР°РЅРЅС‹С… (РёСЃРїРѕР»СЊР·СѓРµС‚СЃСЏ РІ С„СѓРЅРєС†РёРё xprintf)
 * @param c 1 Р±Р°Р№С‚ РѕС‚РїСЂР°РІР»СЏРµРјС‹С… РґР°РЅРЅС‹С…
 * @return none
 */
void __attribute__((weak)) xputc(char c)
{
	//HAL_USART_Transmit(UART_0, c, USART_TIMEOUT_DEFAULT);
    UART_0->TXDATA = c;
    uint32_t time_stamp = HAL_Micros();
    while ((UART_0->FLAGS.dword & UART_FLAGS_TC_M) == 0)
    {
        if (HAL_Micros() - time_stamp > USART_TIMEOUT_DEFAULT) break;
    }
}


/*******************************************************************************
 * @brief РЈРїСЂР°РІР»РµРЅРёРµ Р»РёРЅРёРµР№ DTR ("РіРѕС‚РѕРІ Рє РїСЂРёРµРјСѓ") РјРѕРґСѓР»СЏ USART.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @param en Enable or Disable
 * @return none
 */
void HAL_USART_Set_DTR(USART_HandleTypeDef* local, MIK32_HAL_CTRL en)
{
    if (en) local->Instance->MODEM |= UART_MODEM_DTR_M;
    else local->Instance->MODEM &= ~UART_MODEM_DTR_M;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ СЃРѕСЃС‚РѕСЏРЅРёСЏ Р»РёРЅРёРё DCD ("РѕР±РЅР°СЂСѓР¶РµРЅРёРµ РЅРµСЃСѓС‰РµР№") РјРѕРґСѓР»СЏ USART.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_DCD_Status(USART_HandleTypeDef* local)
{
    if (local->Instance->MODEM & UART_MODEM_DCD_M) return true;
    else return false;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° РёР·РјРµРЅРµРЅРёСЏ СЃРѕСЃС‚РѕСЏРЅРёСЏ Р»РёРЅРёРё DCD ("РѕР±РЅР°СЂСѓР¶РµРЅРёРµ РЅРµСЃСѓС‰РµР№")
 * РјРѕРґСѓР»СЏ USART.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_DCD_ReadToggleFlag(USART_HandleTypeDef* local)
{
    if (local->Instance->MODEM & UART_MODEM_DCDIF_M) return true;
    else return false;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ СЃРѕСЃС‚РѕСЏРЅРёСЏ Р»РёРЅРёРё RI ("Р·РІРѕРЅРѕРє РЅР° С‚РµР»РµС„РѕРЅРЅРѕР№ Р»РёРЅРёРё") РјРѕРґСѓР»СЏ USART.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_RI_Status(USART_HandleTypeDef* local)
{
    if (local->Instance->MODEM & UART_MODEM_RI_M) return true;
    else return false;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° РёР·РјРµРЅРµРЅРёСЏ СЃРѕСЃС‚РѕСЏРЅРёСЏ Р»РёРЅРёРё RI ("Р·РІРѕРЅРѕРє РЅР° С‚РµР»РµС„РѕРЅРЅРѕР№
 * Р»РёРЅРёРё") РјРѕРґСѓР»СЏ USART.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_RI_ReadToggleFlag(USART_HandleTypeDef* local)
{
    if (local->Instance->MODEM & UART_MODEM_RIIF_M) return true;
    else return false;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ СЃРѕСЃС‚РѕСЏРЅРёСЏ Р»РёРЅРёРё DSR ("РёСЃС‚РѕС‡РЅРёРє РґР°РЅРЅС‹С… РіРѕС‚РѕРІ") РјРѕРґСѓР»СЏ USART
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_DSR_Status(USART_HandleTypeDef* local)
{
    if (local->Instance->MODEM & UART_MODEM_DSR_M) return true;
    else return false;
}

/*******************************************************************************
 * @brief Р§С‚РµРЅРёРµ С„Р»Р°РіР° РёР·РјРµРЅРµРЅРёСЏ СЃРѕСЃС‚РѕСЏРЅРёСЏ Р»РёРЅРёРё DSR ("РёСЃС‚РѕС‡РЅРёРє РґР°РЅРЅС‹С… РіРѕС‚РѕРІ")
 * РјРѕРґСѓР»СЏ USART.
 * @param local СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ-РґРµСЃРєСЂРёРїС‚РѕСЂ РјРѕРґСѓР»СЏ USART
 * @return true РёР»Рё false
 */
bool HAL_USART_DSR_ReadToggleFlag(USART_HandleTypeDef* local)
{
    if (local->Instance->MODEM & UART_MODEM_DSRIF_M) return true;
    else return false;
}
