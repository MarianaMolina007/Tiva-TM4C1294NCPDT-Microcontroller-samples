//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2013-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include "driverlib/timer.h"

uint32_t g_ui32Flags;
char data[20]="";
uint32_t g_ui32SysClock;
bool flag = false;
int8_t counter = 0;
int8_t counterd = 0;
int8_t counterc = 0;
bool increment = true;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

void GPIOIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = GPIOIntStatus(GPIO_PORTJ_BASE, true);
    GPIOIntClear(GPIO_PORTJ_BASE, ui32Status);
    // UARTSend((uint8_t *)"\033[2JpPressed: ", 12); //? \033 equivalente al \n

    if (increment)
    {
        counter++;
        if (counter > 9){
            counterd++;
            counter =0;
        }
        if (counterd > 9){
            counterc++;
            counterd =0;
        }
        if(counterc >9){
            counter = 9;
            counterd = 9;
            counterc = 9;
        }
    }
    else
    {
        counter--;
        if (counter < 0){
            counterd--;
            counter = 9;
        }
        if (counterd < 0){
            counterc--;
            counterd = 9;
        }
        if(counterc < 0){
            counter = 0;
            counterd = 0;
            counterc = 0;
        }
    }
    
    UARTCharPut(UART0_BASE, 'p');
    UARTCharPut(UART0_BASE, ':');
    if (counterc > 0) //? Imprime las centenas
        UARTCharPut(UART0_BASE, (uint8_t)counterc+48);
    if (counterd > 0|| counterc > 0) //? Imprime las decenas
        UARTCharPut(UART0_BASE, (uint8_t)counterd+48);
    UARTCharPut(UART0_BASE, (uint8_t)counter+48);
    UARTCharPut(UART0_BASE, '\n');
    
}

//*****************************************************************************
//
// The interrupt handler for the first timer interrupt.
//
//*****************************************************************************
void
Timer0IntHandler(void)
{
    char cOne, cTwo;

    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Toggle the flag for the first timer.
    //
    HWREGBITW(&g_ui32Flags, 0) ^= 1;

    //
    // Use the flags to Toggle the LED for this timer
    //
    // GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, g_ui32Flags);

    //
    // Update the interrupt status.
    //
    MAP_IntMasterDisable();
    cOne = HWREGBITW(&g_ui32Flags, 0) ? '1' : '0';
    cTwo = HWREGBITW(&g_ui32Flags, 1) ? '1' : '0';

    if (flag)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0xFF);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00);
    }
    flag = !flag;
    MAP_IntMasterEnable();
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************

void
UARTIntHandler(void)
{
    uint32_t ui32Status,pwm_value;
    uint8_t dig1,dig2,dig3,dig4;
    //
    // Get the interrrupt status.
    //
    ui32Status = MAP_UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    MAP_UARTIntClear(UART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    uint8_t ind=0;
    while(MAP_UARTCharsAvail(UART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        //MAP_UARTCharPutNonBlocking(UART0_BASE,
        //                           MAP_UARTCharGetNonBlocking(UART0_BASE));
	data[ind]=MAP_UARTCharGetNonBlocking(UART0_BASE);
        //
        // Blink the LED to show a character transfer is occuring.
        //
        MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);

        //
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        //
        SysCtlDelay(g_ui32SysClock / (1000 * 3));

        //
        // Turn off the LED
        //
        MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
        ind++;
    }
	
    if(data[0]=='P' && data[1]=='W' && data[2]=='M'&& data[3]=='_'){
	dig1=data[4]-48;
	dig2=data[5]-48;
	dig3=data[6]-48;
	dig4=data[7]-48;
	pwm_value=dig1*1000+dig2*100+dig3*10+dig4;	
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, pwm_value);
	}

        if (data[0] == 'L' && data[1] == 'D' && data[2] == '_' && data[3] == 'O' && data[4] == 'N')
    {
        MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0xFF);
    }
    
    if (data[0] == 'L' && data[1] == 'D' && data[2] == '_' && data[3] == 'O' && data[4] == 'F' && data[5] == 'F')
    {
        MAP_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);    
    }
    
    if (data[0] == 'C' && data[1] == 'O' && data[2] == 'U' && data[3] == 'N' && data[4] == 'T' && data[5] == 'E' && data[6] == 'R' && data[7] == ':')
    {
        dig1=data[8]-48;
        dig2=data[9]-48;
        dig3=data[10]-48;
        counterc=dig1;
        counterd=dig2;
        counter=dig3;

        if (data[11] == 'A')
        {
            increment = true;
        }
        
        if (data[11] == 'D')
        {
            increment = false;
        }        	
    }
}

//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void
UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        MAP_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}

//*****************************************************************************
//
// This example demonstrates how to send a string of data to the UART.
//
//*****************************************************************************
int
main(void)
{
	 uint32_t ui32PWMClockRate;
    //
    // Run from the PLL at 120 MHz.
    // Note: SYSCTL_CFG_VCO_240 is a new setting provided in TivaWare 2.2.x and
    // later to better reflect the actual VCO speed due to SYSCTL#22.
    //
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_240), 120000000);
                                             
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    //
    // Enable the GPIO pins for the LED (PN0).
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1);
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);

    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);

    //
    // Enable processor interrupts.
    //
    MAP_IntMasterEnable();

    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_INT_PIN_0,GPIO_FALLING_EDGE); //? Falling edge: (HIGH => LOW)
    GPIOIntRegister(GPIO_PORTJ_BASE, GPIOIntHandler);
    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);

    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock / 5);
    MAP_IntEnable(INT_TIMER0A);
    MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerEnable(TIMER0_BASE, TIMER_A);
    //
    // Set GPIO A0 and A1 as UART pins.
    //
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    MAP_UARTConfigSetExpClk(UART0_BASE, g_ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    MAP_IntEnable(INT_UART0);
    MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    //
    // Prompt for text to be entered.
    //
    UARTSend((uint8_t *)"\033[2JEnter text: ", 16);

    //
    // Loop forever echoing data through the UART.
    //

	 MAP_GPIOPinConfigure(GPIO_PF0_M0PWM0);
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);

    MAP_PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);
    ui32PWMClockRate = g_ui32SysClock / 64;
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
                        PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, (ui32PWMClockRate / 1000));
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1200);
    MAP_PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);

    MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    uint32_t counter =0;
    while(1)
    {}
}
