#include "mik32_hal_gpio.h"

/** Р”Р»СЏ РѕР±С…РѕРґР° Р±Р°РіР° РњРљ, С‡С‚РµРЅРёРµ РёР· СЂРµРіРёСЃС‚СЂР° IRQ_LINE_MUX РІСЃРµРіРґР° РІРѕР·РІСЂР°С‰Р°РµС‚ 0
 *  \note Р�СЃРїРѕР»СЊР·СѓРµС‚СЃСЏ РІ С„СѓРЅРєС†РёСЏС… HAL_GPIO_InitInterruptLine Рё HAL_GPIO_DeInitInterruptLine
 */
volatile uint32_t current_irq_line_mux = 0;

/**
 * @brief Р�РЅРёС†РёР°Р»РёР·Р°С†РёСЏ РјРѕРґСѓР»СЏ GPIO_x РІ СЃРѕРѕС‚РІРµС‚СЃС‚РІРёРё СЃ СѓРєР°Р·Р°РЅРЅС‹РјРё РїР°СЂР°РјРµС‚СЂР°РјРё РІ GPIO_Init.
 * @param GPIO_x РїРѕСЂС‚ GPIO_x, РіРґРµ x РјРѕР¶РµС‚ Р±С‹С‚СЊ (0, 1, 2).
 * @param GPIO_Init СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃС‚СЂСѓРєС‚СѓСЂСѓ GPIO_InitTypeDef, РєРѕС‚РѕСЂР°СЏ СЃРѕРґРµСЂР¶РёС‚ РёРЅС„РѕСЂРјР°С†РёСЋ Рѕ РєРѕРЅС„РёРіСѓСЂР°С†РёРё РґР»СЏ СѓРєР°Р·Р°РЅРЅРѕРіРѕ РјРѕРґСѓР»СЏ GPIO.
 * @return СЃС‚Р°С‚СѓСЃ HAL.
 * @warning С„СѓРЅРєС†РёСЏ РЅРµ РІРєР»СЋС‡Р°РµС‚ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РІС‹Р±СЂР°РЅРЅРѕРіРѕ РјРѕРґСѓР»СЏ GPIO. Р’РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РјРѕР¶РЅРѕ, РЅР°РїСЂРёРјРµСЂ, СЃ РїРѕРјРѕС‰СЊСЋ РјР°РєСЂРѕСЃР° @ref __HAL_PCC_GPIO_2_CLK_ENABLE.
 */
HAL_StatusTypeDef HAL_GPIO_Init(GPIO_TypeDef *GPIO_x, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t *port_cfg = 0;
    uint32_t *port_ds = 0;
    uint32_t *port_pupd = 0;

    uint32_t position = 0;
    uint32_t current_pin = 0;

    switch ((uint32_t)GPIO_x)
    {
    case (uint32_t)GPIO_0:
        port_cfg = (uint32_t *)&(PAD_CONFIG->PORT_0_CFG);
        port_ds = (uint32_t *)&(PAD_CONFIG->PORT_0_DS);
        port_pupd = (uint32_t *)&(PAD_CONFIG->PORT_0_PUPD);
        break;
    case (uint32_t)GPIO_1:
        port_cfg = (uint32_t *)&(PAD_CONFIG->PORT_1_CFG);
        port_ds = (uint32_t *)&(PAD_CONFIG->PORT_1_DS);
        port_pupd = (uint32_t *)&(PAD_CONFIG->PORT_1_PUPD);
        break;
    case (uint32_t)GPIO_2:
        port_cfg = (uint32_t *)&(PAD_CONFIG->PORT_2_CFG);
        port_ds = (uint32_t *)&(PAD_CONFIG->PORT_2_DS);
        port_pupd = (uint32_t *)&(PAD_CONFIG->PORT_2_PUPD);
        break;

    default:
        return HAL_ERROR;
        break;
    }
    
    while (((GPIO_Init->Pin) >> position) != 0)
    {
        current_pin = GPIO_Init->Pin & (1 << position);

        if (current_pin)
        {
            *port_cfg = (*port_cfg & (~PAD_CONFIG_PIN_M(position))) | PAD_CONFIG_PIN(position, GPIO_Init->Mode & 0b11);

            if ((GPIO_Init->Mode == HAL_GPIO_MODE_GPIO_INPUT) || (GPIO_Init->Mode == HAL_GPIO_MODE_GPIO_OUTPUT))
            {
                if (GPIO_Init->Mode == HAL_GPIO_MODE_GPIO_INPUT)
                {
                    GPIO_x->DIRECTION_IN = 1 << position;
                }
                else
                {
                    GPIO_x->DIRECTION_OUT = 1 << position;
                }
            }

            *port_ds = (*port_ds & (~PAD_CONFIG_PIN_M(position))) | PAD_CONFIG_PIN(position, GPIO_Init->DS);
            *port_pupd = (*port_pupd & (~PAD_CONFIG_PIN_M(position))) | PAD_CONFIG_PIN(position, GPIO_Init->Pull);
        }

        position++;
    }

    return HAL_OK;
}

/**
 * @brief Р�РЅРёС†РёР°Р»РёР·Р°С†РёСЏ РјРѕРґСѓР»СЏ GPIO_x.
 * @param GPIO_x РїРѕСЂС‚ GPIO_x, РіРґРµ x РјРѕР¶РµС‚ Р±С‹С‚СЊ (0, 1, 2).
 * @param pin РјР°СЃРєР° РІС‹РІРѕРґРѕРІ РїРѕСЂС‚Р° GPIO_x, Рє РєРѕС‚РѕСЂС‹Рј РїСЂРёРјРµРЅСЏСЋС‚СЃСЏ СѓРєР°Р·Р°РЅРЅС‹Рµ РЅР°СЃС‚СЂРѕР№РєРё.
 * @param mode СЂРµР¶РёРј РІС‹РІРѕРґР°.
 * @param pull СЂРµР¶РёРј РїРѕРґС‚СЏР¶РєРё РІС‹РІРѕРґР°.
 * @param driveStrength РїРµСЂРµС‡РёСЃР»РµРЅРёРµ СЂРµР¶РёРјРѕРІ РЅР°РіСЂСѓР·РѕС‡РЅРѕР№ СЃРїРѕСЃРѕР±РЅРѕСЃС‚Рё.
 * @return РЎС‚Р°С‚СѓСЃ HAL.
 */
HAL_StatusTypeDef HAL_GPIO_PinConfig(GPIO_TypeDef *GPIO_x, HAL_PinsTypeDef pin,
		HAL_GPIO_ModeTypeDef mode, HAL_GPIO_PullTypeDef pull, HAL_GPIO_DSTypeDef driveStrength)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
    GPIO_InitStruct.DS = driveStrength;
    return HAL_GPIO_Init(GPIO_x, &GPIO_InitStruct);
}

/**
 * @brief РЎС‡РёС‚Р°С‚СЊ С‚РµРєСѓС‰РµРµ СЃРѕСЃС‚РѕСЏРЅРёРµ РІС‹РІРѕРґРѕРІ РїРѕСЂС‚Р° GPIO_x.
 * @param GPIO_x РїРѕСЂС‚ GPIO_x, РіРґРµ x РјРѕР¶РµС‚ Р±С‹С‚СЊ (0, 1, 2).
 * @param pin РјР°СЃРєР° РІС‹РІРѕРґРѕРІ РїРѕСЂС‚Р° GPIO_x, СЃ РєРѕС‚РѕСЂС‹С… СЃС‡РёС‚С‹РІР°РЅРёРµ Р·РЅР°С‡РµРЅРёРµ.
 * @return @ref GPIO_PIN_HIGH РµСЃР»Рё СЃ РѕРґРЅРѕРіРѕ РёР»Рё Р±РѕР»СЊС€Рµ РІС‹РІРѕРґРѕРІ, СѓРєР°Р·Р°РЅРЅС‹С… РІ pin, СЃС‡РёС‚Р°Р»Р°СЃСЊ 1. Р�РЅР°С‡Рµ @ref GPIO_PIN_LOW.
 */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIO_x, HAL_PinsTypeDef pin)
{
    GPIO_PinState bitStatus;

    if ((GPIO_x->SET & pin) != (uint32_t)GPIO_PIN_LOW)
    {
        bitStatus = GPIO_PIN_HIGH;
    }
    else
    {
        bitStatus = GPIO_PIN_LOW;
    }
    return bitStatus;
}

/**
 * @brief Р—Р°РґР°С‚СЊ Р»РѕРіРёС‡РµСЃРєРёР№ СѓСЂРѕРІРµРЅСЊ РІС‹С…РѕРґРЅРѕРіРѕ СЃРёРіРЅР°Р»Р° РґР»СЏ СѓРєР°Р·Р°РЅРЅС‹С… РІС‹РІРѕРґРѕРІ РїРѕСЂС‚Р° GPIO_x.
 * @param GPIO_x РїРѕСЂС‚ GPIO_x, РіРґРµ x РјРѕР¶РµС‚ Р±С‹С‚СЊ (0, 1, 2).
 * @param pin РјР°СЃРєР° РІС‹РІРѕРґРѕРІ РїРѕСЂС‚Р° GPIO_x, Рє РєРѕС‚РѕСЂС‹Рј РїСЂРёРјРµРЅСЏСЋС‚СЃСЏ СѓРєР°Р·Р°РЅРЅС‹Рµ РЅР°СЃС‚СЂРѕР№РєРё.
 * @param pinState Р·РЅР°С‡РµРЅРёРµ СЃРѕСЃС‚РѕСЏРЅРёРµ РІС‹РІРѕРґР°, РІ РєРѕС‚РѕСЂРѕРµ Р±СѓРґСѓС‚ СѓСЃС‚Р°РЅРѕРІР»РµРЅС‹ СѓРєР°Р·Р°РЅРЅС‹Рµ РІС‹РІРѕРґС‹.
 *                  Р­С‚РѕС‚ РїР°СЂР°РјРµС‚СЂ РґРѕР»Р¶РµРЅ Р±С‹С‚СЊ РѕРґРЅРёРј РёР· Р·РЅР°С‡РµРЅРёР№:
 * 		                - @ref GPIO_PIN_LOW РЅРёР·РєРёР№ РІС‹С…РѕРґРЅРѕР№ СѓСЂРѕРІРµРЅСЊ
 * 		                - @ref GPIO_PIN_HIGH РІС‹СЃРѕРєРёР№ РІС‹С…РѕРґРЅРѕР№ СѓСЂРѕРІРµРЅСЊ
 */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIO_x, HAL_PinsTypeDef pin, GPIO_PinState pinState)
{
    if (pinState == GPIO_PIN_LOW)
    {
        GPIO_x->CLEAR = pin;
    }
    else
    {
        GPIO_x->SET = pin;
    }
}

/**
 * @brief РџРµСЂРµРєР»СЋС‡РёС‚СЊ Р»РѕРіРёС‡РµСЃРєРёР№ СѓСЂРѕРІРµРЅСЊ РІС‹С…РѕРґРЅРѕРіРѕ СЃРёРіРЅР°Р»Р° РґР»СЏ СѓРєР°Р·Р°РЅРЅС‹С… РІС‹РІРѕРґРѕРІ РїРѕСЂС‚Р° GPIO_x.
 * @param GPIO_x РїРѕСЂС‚ GPIO_x, РіРґРµ x РјРѕР¶РµС‚ Р±С‹С‚СЊ (0, 1, 2).
 * @param pin РјР°СЃРєР° РІС‹РІРѕРґРѕРІ РїРѕСЂС‚Р° GPIO_x, Рє РєРѕС‚РѕСЂС‹Рј РїСЂРёРјРµРЅСЏСЋС‚СЃСЏ СѓРєР°Р·Р°РЅРЅС‹Рµ РЅР°СЃС‚СЂРѕР№РєРё.
 */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIO_x, HAL_PinsTypeDef pin)
{
    GPIO_x->OUTPUT ^= pin;
}

/** 
 *  @brief Р¤СѓРЅРєС†РёСЏ РёРЅРёС†РёР°Р»РёР·Р°С†РёРё Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 * \param mux РЅР°СЃС‚СЂРѕР№РєР° РјСѓР»СЊС‚РёРїР»РµРєСЃРѕСЂР° Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 * \param mode СЂРµР¶РёРј Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 * @return РЎС‚Р°С‚СѓСЃ HAL.
 * \note РќРѕРјРµСЂ Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ РјРѕР¶РЅРѕ РїРѕР»СѓС‡РёС‚СЊ РїРѕСЃР»Рµ РЅР°СЃС‚СЂРѕР№РєРё РјСѓР»СЊС‚РёРїР»РµРєСЃРѕСЂР°.
 * Р’РІРµРґРёС‚Рµ РІ mux GPIO_MUX_GPIO_X_X, РіРґРµ X - РЅРѕРјРµСЂР° РїРѕСЂС‚Р° Рё РІС‹РІРѕРґР°,
 * Рё РЅР°Р¶РјРёС‚Рµ Ctrl+РџСЂРѕР±РµР»: РїРѕСЏРІСЏС‚СЃСЏ РІР°СЂРёР°РЅС‚С‹ РєРѕРЅСЃС‚Р°РЅС‚ РґР»СЏ РґР°РЅРЅРѕРіРѕ РІС‹РІРѕРґР°,
 * РґР°Р»РµРµ РґРѕСЃС‚Р°С‚РѕС‡РЅРѕ РІС‹Р±СЂР°С‚СЊ РєРѕРЅСЃС‚Р°РЅС‚Сѓ РґР»СЏ РґРѕСЃС‚СѓРїРЅРѕР№ Р»РёРЅРёРё.
 * Р’ mode РІРІРµРґРёС‚Рµ GPIO_INT_MODE Рё РЅР°Р¶РјРёС‚Рµ Ctrl+РџСЂРѕР±РµР»: РїРѕСЏРІСЏС‚СЃСЏ РІР°СЂРёР°РЅС‚С‹ С‚РёРїРѕРІ РїСЂРµСЂС‹РІР°РЅРёР№ РєР°РЅР°Р»Р°.
 */
HAL_StatusTypeDef HAL_GPIO_InitInterruptLine(HAL_GPIO_Line_Config mux, HAL_GPIO_InterruptMode mode)
{
    int irq_line_num = mux >> GPIO_IRQ_LINE_S;
    mode &= 0b111;
    if (irq_line_num > 7)
        return HAL_ERROR;

    current_irq_line_mux &= ~GPIO_IRQ_LINE_MUX_M(irq_line_num);
    current_irq_line_mux |= GPIO_IRQ_LINE_MUX(mux, irq_line_num);
    GPIO_IRQ->LINE_MUX = current_irq_line_mux;

    if (mode & GPIO_MODE_BIT_LEVEL_M) // GPIO_INT_MODE_HIGH, GPIO_INT_MODE_RISING
    {
        GPIO_IRQ->LEVEL_SET = (1 << irq_line_num); // РЅР°СЂР°СЃС‚Р°СЋС‰РёР№ С„СЂРѕРЅС‚ РёР»Рё Р»РѕРіРёС‡РµСЃРєРёР№ СѓСЂРѕРІРµРЅСЊ 1
    }
    else
    {
        GPIO_IRQ->LEVEL_CLEAR = (1 << irq_line_num); // СЃРїР°РґР°СЋС‰РёР№ С„СЂРѕРЅС‚ РёР»Рё Р»РѕРіРёС‡РµСЃРєРёР№ СѓСЂРѕРІРµРЅСЊ 0
    }

    if (mode & GPIO_MODE_BIT_EDGE_M) // GPIO_INT_MODE_FALLING, GPIO_INT_MODE_RISING, GPIO_INT_MODE_CHANGE
    {
        GPIO_IRQ->EDGE = (1 << irq_line_num); // С‚РёРї РїСЂРµСЂС‹РІР°РЅРёСЏ - СЃРѕР±С‹С‚РёРµ (С„СЂРѕРЅС‚/СЃРїР°Рґ)
    }
    else
    {
        GPIO_IRQ->LEVEL = (1 << irq_line_num); // С‚РёРї РїСЂРµСЂС‹РІР°РЅРёСЏ - Р»РѕРіРёС‡РµСЃРєРёР№ СѓСЂРѕРІРµРЅСЊ
    }

    if (mode & GPIO_MODE_BIT_ANYEDGE_M) // GPIO_INT_MODE_CHANGE
    {
        GPIO_IRQ->ANY_EDGE_SET = (1 << irq_line_num); // СЂР°Р·СЂРµС€РµРЅРѕ РїСЂРµСЂС‹РІР°РЅРёРµ РїРѕ Р»СЋР±РѕРјСѓ С„СЂРѕРЅС‚Сѓ
    }
    else
    {
        GPIO_IRQ->ANY_EDGE_CLEAR = (1 << irq_line_num); // Р·Р°РїСЂРµС‰РµРЅРѕ РїСЂРµСЂС‹РІР°РЅРёРµ РїРѕ Р»СЋР±РѕРјСѓ С„СЂРѕРЅС‚Сѓ
    }

    GPIO_IRQ->ENABLE_SET = (1 << irq_line_num);

    return HAL_OK;
}

/**
 * @brief Р¤СѓРЅРєС†РёСЏ РґРµРёРЅРёС†РёР°Р»РёР·Р°С†РёРё Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ, Р·Р°РїСЂРµС‰Р°РµС‚ РїСЂРµСЂС‹РІР°РЅРёРµ Рё РІРѕР·РІСЂР°С‰Р°РµС‚ РЅР°СЃС‚СЂРѕР№РєРё РїРѕ СѓРјРѕР»С‡Р°РЅРёСЋ РґР»СЏ СѓРєР°Р·Р°РЅРЅРѕР№ Р»РёРЅРё.
 * @param irqLine РЅРѕРјРµСЂ Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 * @return РЎС‚Р°С‚СѓСЃ HAL.
 */
HAL_StatusTypeDef HAL_GPIO_DeInitInterruptLine(HAL_GPIO_Line irqLine)
{
    int irq_line_num = irqLine >> GPIO_IRQ_LINE_S;

    if (irq_line_num > 7)
        return HAL_ERROR;

    GPIO_IRQ->ENABLE_CLEAR = (1 << irq_line_num);

    current_irq_line_mux &= ~GPIO_IRQ_LINE_MUX_M(irq_line_num);
    GPIO_IRQ->LINE_MUX = current_irq_line_mux;

    GPIO_IRQ->LEVEL = (1 << irq_line_num);
    GPIO_IRQ->LEVEL_CLEAR = (1 << irq_line_num);
    GPIO_IRQ->ANY_EDGE_CLEAR = (1 << irq_line_num);

    return HAL_OK;
}

/** 
 * @brief РџРѕР»СѓС‡РёС‚СЊ СЃРѕСЃС‚РѕСЏРЅРёРµ Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 * @param irqLine РЅРѕРјРµСЂ Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 * @return Р’РѕР·РІСЂР°С‰Р°РµС‚ 1 РµСЃР»Рё СЃСЂР°Р±РѕС‚Р°Р»Рѕ РїСЂРµСЂС‹РІР°РЅРёРµ РґР°РЅРЅРѕР№ Р»РёРЅРёРё, РёРЅР°С‡Рµ 0.
 */
uint32_t HAL_GPIO_LineInterruptState(HAL_GPIO_Line irqLine)
{
    int irq_line_num = irqLine >> GPIO_IRQ_LINE_S;
    return (GPIO_IRQ->INTERRUPT & (1 << (irq_line_num))) != 0;
}

/**
 * @brief Р¤СѓРЅРєС†РёСЏ С‡С‚РµРЅРёСЏ Р»РѕРіРёС‡РµСЃРєРѕРіРѕ СѓСЂРѕРІРЅСЏ РІС‹РІРѕРґР°, РїРѕРґРєР»СЋС‡РµРЅРЅРѕРіРѕ Рє Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 * @param irqLine РЅРѕРјРµСЂ Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 * @return Р›РѕРіРёС‡РµСЃРєРёР№ СѓСЂРѕРІРµРЅСЊ РІС‹РІРѕРґР°.
 */
GPIO_PinState HAL_GPIO_LinePinState(HAL_GPIO_Line irqLine)
{
    int irq_line_num = irqLine >> GPIO_IRQ_LINE_S;
    return (GPIO_PinState)((GPIO_IRQ->STATE & (1 << (irq_line_num))) >> irq_line_num);
}

/** 
 *  @brief Р¤СѓРЅРєС†РёСЏ СЃР±СЂРѕСЃР° СЂРµРіРёСЃС‚СЂР° СЃРѕСЃС‚РѕСЏРЅРёСЏ РїСЂРµСЂС‹РІР°РЅРёР№.
 *  @note РљРѕРіРґР° СЃСЂР°Р±Р°С‚С‹РІР°РµС‚ РїСЂРµСЂС‹РІР°РЅРёРµ РЅР° РѕРґРЅРѕР№ РёР· Р»РёРЅРёРё, РІ СЂРµРіРёСЃС‚СЂРµ INTERRUPT
 *  РІС‹СЃС‚Р°РІР»СЏРµС‚СЃСЏ 1 РІ СЂР°Р·СЂСЏРґРµ, СЃРѕРѕС‚РІРµС‚СЃС‚РІСѓСЋС‰РµРј Р»РёРЅРёРё РїСЂРµСЂС‹РІР°РЅРёСЏ.
 *  РџРѕСЃР»Рµ РѕР±СЂР°Р±РѕС‚РєРё РїСЂРµСЂС‹РІР°РЅРёСЏ РЅРµРѕР±С…РѕРґРёРјРѕ СЃР±СЂРѕСЃРёС‚СЊ РґР°РЅРЅС‹Р№ СЂРµРіРёСЃС‚СЂ
 *  РІ РѕР±СЂР°Р±РѕС‚С‡РёРєРµ РїСЂРµСЂС‹РІР°РЅРёСЏ trap_handler().
 *  Р•СЃР»Рё РїРѕСЃР»Рµ РѕР±СЂР°Р±РѕС‚РєРё РїСЂРµСЂС‹РІР°РЅРёСЏ СЂРµРіРёСЃС‚СЂ РЅРµ Р±С‹Р» СЃР±СЂРѕС€РµРЅ,
 *  РѕР±СЂР°Р±РѕС‚С‡РёРє Р±СѓРґРµС‚ РІС‹Р·РІР°РЅ СЃРЅРѕРІР°, РїСЂРѕРіСЂР°РјРјР° Р±СѓРґРµС‚ Р±РµСЃРєРѕРЅРµС‡РЅРѕ РІС‹Р·С‹РІР°С‚СЊ РѕР±СЂР°Р±РѕС‚С‡РёРє.
 */
void HAL_GPIO_ClearInterrupts()
{
    GPIO_IRQ->CLEAR = 0b11111111;
}
