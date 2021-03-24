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
#include "driverlib/pwm.h"

#define freq_m1 1000
char data[20]="";
uint32_t g_ui32PWMIncrement;//!
uint32_t vel_pwm = 0;
uint32_t g_ui32SysClock;
uint32_t g_ui32Flags;
bool flag1 = true;
bool flag2 = true;
bool flag3 = true;
bool flag4 = true;
bool automatic = true;
uint8_t counter = 0;
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

#pragma region void_timers

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
    if(automatic){    
        if (flag1)
        {
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0xFF);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x00);
        }
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
    if(automatic){    if (flag2)
        {
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0xFF);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x00);
        }}
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
    if(automatic){    if (flag3)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0xFF);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x00);
        }}
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
    if(automatic){    if (flag4)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0xFF);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x00);
        }}
    flag4 = !flag4;
    //
    // Update the interrupt status.
    // 
    MAP_IntMasterDisable();
    cOne = HWREGBITW(&g_ui32Flags, 0) ? '1' : '0';
    cTwo = HWREGBITW(&g_ui32Flags, 1) ? '1' : '0';
    // UARTprintf("\rT1: %c  T2: %c", cOne, cTwo);
    MAP_IntMasterEnable();
}

#pragma endregion void_timers

void GPIOIntHandler(void)
{
    uint32_t ui32Status;
	ui32Status=GPIOIntStatus(GPIO_PORTJ_BASE, true);
    GPIOIntClear(GPIO_PORTJ_BASE,ui32Status);
    if (ui32Status == 0x01)
    {
        automatic = !automatic;
        counter = 0;
    }
    if (!automatic && ui32Status == 0x02)
    {
        counter++;
        if(counter == 16)
            counter = 0;
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, ((counter+1)%2==0)? 0xFF : 0x00); 
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, ((counter+2)%4==0)? 0xFF : 0x00); 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, ((counter+4)%8==0)? 0xFF : 0x00); 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, ((counter+8)%16==0)? 0xFF : 0x00); 
    }
    
}

#pragma region UART
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
	MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, pwm_value); ///***
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



#pragma endregion UART
int
main(void)
{
    uint32_t ui32PWMClockRate;
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
    #pragma region buttons
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); // Enable Port J
    MAP_GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1); // Asign Pin J0 as Input
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU); // Set input pin with 4mA
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_INT_PIN_0 | GPIO_PIN_1, GPIO_FALLING_EDGE); // Set pin J0 as falling edge (Falling edge or rising edge)
    GPIOIntRegister(GPIO_PORTJ_BASE, GPIOIntHandler); // Set void as an action
    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0 | GPIO_PIN_1); // Enable pin J0
    #pragma endregion buttons
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
    
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock *8); // 1 segundo 
    MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, g_ui32SysClock *4); // 0.5 segundos
    MAP_TimerLoadSet(TIMER2_BASE, TIMER_A, g_ui32SysClock *2); 
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
    #pragma region UART
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    MAP_UARTConfigSetExpClk(UART0_BASE, g_ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_PAR_NONE));
    MAP_IntEnable(INT_UART0);
    MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    #pragma endregion UART
    #pragma region PWM
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    MAP_GPIOPinConfigure(GPIO_PG1_M0PWM5);
    MAP_GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_1);

    MAP_PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);
    ui32PWMClockRate = g_ui32SysClock / 64;
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_2,
                        PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, (ui32PWMClockRate / 1000));
    MAP_PWMOutputState(PWM0_BASE, PWM_OUT_5, true);

    MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_2);

    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 1200);
    #pragma endregion PWM
    while(1)
    {
    }
}
