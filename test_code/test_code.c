#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

uint32_t g_ui32SysClock;
uint32_t g_ui32Flags;
bool flag1 = true;
bool flag2 = true;
bool flag3 = true;
bool flag4 = true;
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

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
    //
    // Use the flags to Toggle the LED for this timer
    //
    if (flag1)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0xFF);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00);
    }
    flag1 = !flag1;
    //
    // Update the interrupt status.
    //
    MAP_IntMasterDisable();
    //Aditional logic
    cOne = HWREGBITW(&g_ui32Flags, 0) ? '1' : '0';
    cTwo = HWREGBITW(&g_ui32Flags, 1) ? '1' : '0';
    // UARTprintf("\rT1: %c  T2: %c", cOne, cTwo);
    MAP_IntMasterEnable();
}

void
Timer1IntHandler(void)
{
    char cOne, cTwo;

    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Toggle the flag for the second timer.
    //
    HWREGBITW(&g_ui32Flags, 1) ^= 1;

    //
    // Use the flags to Toggle the LED for this timer
    //
    if (flag2)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0xFF);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00);
    }
    flag2 = !flag2;
    //
    // Update the interrupt status.
    // 
    MAP_IntMasterDisable();
    cOne = HWREGBITW(&g_ui32Flags, 0) ? '1' : '0';
    cTwo = HWREGBITW(&g_ui32Flags, 1) ? '1' : '0';
    // UARTprintf("\rT1: %c  T2: %c", cOne, cTwo);
    MAP_IntMasterEnable();
}

void
Timer2IntHandler(void)
{
    char cOne, cTwo;

    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Toggle the flag for the first timer.
    //
    HWREGBITW(&g_ui32Flags, 0) ^= 1;
    //
    //
    // Use the flags to Toggle the LED for this timer
    //
    if (flag3)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0xFF);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);
    }
    flag3 = !flag3;
    //
    // Update the interrupt status.
    //
    MAP_IntMasterDisable();
    //Aditional logic
    cOne = HWREGBITW(&g_ui32Flags, 0) ? '1' : '0';
    cTwo = HWREGBITW(&g_ui32Flags, 1) ? '1' : '0';
    // UARTprintf("\rT1: %c  T2: %c", cOne, cTwo);
    MAP_IntMasterEnable();
}

void
Timer3IntHandler(void)
{
    char cOne, cTwo;

    //
    // Clear the timer interrupt.
    //
    MAP_TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Toggle the flag for the second timer.
    //
    HWREGBITW(&g_ui32Flags, 1) ^= 1;

    //
    // Use the flags to Toggle the LED for this timer
    //
    if (flag3)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0xFF);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);
    }
    flag3 = !flag3;
    //
    // Update the interrupt status.
    // 
    MAP_IntMasterDisable();
    cOne = HWREGBITW(&g_ui32Flags, 0) ? '1' : '0';
    cTwo = HWREGBITW(&g_ui32Flags, 1) ? '1' : '0';
    // UARTprintf("\rT1: %c  T2: %c", cOne, cTwo);
    MAP_IntMasterEnable();
}

void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, g_ui32SysClock);
}

int
main(void)
{
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_240), 120000000);

    ConfigureUART();


    #pragma region leds
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

    #pragma endregion leds
    #pragma region timers
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);

    MAP_IntMasterEnable();

    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
    MAP_TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);
    
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock ); // 1 segundo 
    MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, g_ui32SysClock / 2); // 0.5 segundos
    MAP_TimerLoadSet(TIMER2_BASE, TIMER_A, g_ui32SysClock ); 
    MAP_TimerLoadSet(TIMER3_BASE, TIMER_A, g_ui32SysClock );

    MAP_IntEnable(INT_TIMER0A);
    MAP_IntEnable(INT_TIMER1A);
    MAP_IntEnable(INT_TIMER2A);
    MAP_IntEnable(INT_TIMER3A);

    MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

    MAP_TimerEnable(TIMER0_BASE, TIMER_A);
    MAP_TimerEnable(TIMER1_BASE, TIMER_A);
    MAP_TimerEnable(TIMER2_BASE, TIMER_A);
    MAP_TimerEnable(TIMER3_BASE, TIMER_A);

    #pragma endregion timers
    while(1)
    {
    }
}
