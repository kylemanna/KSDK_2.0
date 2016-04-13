/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h"
#include "fsl_lpuart_cmsis.h"
#include "fsl_dma_manager.h"
#include "clock_config.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define Driver_DEMO_LPUART Driver_USART0
#define ECHO_BUFFER_LENGTH 8
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* LPUART user SignalEvent */
void LPUART_SignalEvent_t(uint32_t event);
/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_tipString[] =
    "Lpuart CMSIS dma example\r\nBoard receives 8 characters then sends them out\r\nNow please input:\r\n";
uint8_t g_txBuffer[ECHO_BUFFER_LENGTH] = {0};
uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH] = {0};
volatile bool rxBufferEmpty = true;
volatile bool txBufferFull = false;
volatile bool txOnGoing = false;
volatile bool rxOnGoing = false;
/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t LPUART0_GetFreq(void)
{
    return CLOCK_GetFreq(SYS_CLK);
}

uint32_t LPUART1_GetFreq(void)
{
    return CLOCK_GetFreq(SYS_CLK);
}

uint32_t LPUART2_GetFreq(void)
{
    return CLOCK_GetFreq(SYS_CLK);
}

uint32_t LPUART3_GetFreq(void)
{
    return CLOCK_GetFreq(SYS_CLK);
}

uint32_t LPUART4_GetFreq(void)
{
    return CLOCK_GetFreq(SYS_CLK);
}
void LPUART_SignalEvent_t(uint32_t event)
{
    if (ARM_USART_EVENT_SEND_COMPLETE == event)
    {
        txBufferFull = false;
        txOnGoing = false;
    }

    if (ARM_USART_EVENT_RECEIVE_COMPLETE == event)
    {
        rxBufferEmpty = false;
        rxOnGoing = false;
    }
}
/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_BootClockRUN();
    CLOCK_SetLpuart0Clock(0x1U);

    /* Configure DMA. */
    DMAMGR_Init();
    /* Initialize the DEMO_LPUART */
    Driver_DEMO_LPUART.Initialize(LPUART_SignalEvent_t);
    /*
     * default config when use PowerControl API
     * baudrate = 115200
     * parityMode = kLPUART_ParityDisabled;
     * stopBitCount = kLPUART_OneStopBit;
     * txFifoWatermark = 0;
     * rxFifoWatermark = 0;
     * enableTx = true;
     * enableRx = true;
     */
    Driver_DEMO_LPUART.PowerControl(ARM_POWER_FULL);

    txOnGoing = true;
    Driver_DEMO_LPUART.Send(g_tipString, sizeof(g_tipString) - 1);
    /* Wait send finished */
    while (txOnGoing)
    {
    }

    while (1)
    {
        /* If RX is idle and g_rxBuffer is empty, start to read data to g_rxBuffer. */
        if ((!rxOnGoing) && rxBufferEmpty)
        {
            rxOnGoing = true;
            Driver_DEMO_LPUART.Receive(g_rxBuffer, ECHO_BUFFER_LENGTH);
        }

        /* If TX is idle and g_txBuffer is full, start to send data. */
        if ((!txOnGoing) && txBufferFull)
        {
            txOnGoing = true;
            Driver_DEMO_LPUART.Send(g_txBuffer, ECHO_BUFFER_LENGTH);
        }

        /* If g_txBuffer is empty and g_rxBuffer is full, copy g_rxBuffer to g_txBuffer. */
        if ((!rxBufferEmpty) && (!txBufferFull))
        {
            memcpy(g_txBuffer, g_rxBuffer, ECHO_BUFFER_LENGTH);
            rxBufferEmpty = true;
            txBufferFull = true;
        }
    }
}
