// Read carefully each question. All questions are written in English.

// For CODING SECTION you should read the following instructions:

// -The PWM load and delay between steps are controlled by a frame received from UART(MXXXX_DY). Where XXXX is a number from 0 to 4095 and Y is a delay from 1 to 9 ms. 2048 steps means 1 revolution. The PWM is configured to 4096 levels.

// -The button on PC6 changes direction of DC motor and the mode of stepper(full and half).

// -It should be sent by UART the amount of revolutions in the following format:REV_X

// Donde X es el número de vueltas. El código está configurado para enviar hasta 999.

// Where X is the number of revolutions. It is expected to send up to 999 revolutions.

// Take into account the following tables for steps:

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/****-A-****"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

uint32_t ui32SysClkFreq;
uint8_t spin=0;
uint32_t aux=0;

#define GPIO_PA0_U0RX 0x00000001

#define GPIO_PA1_U0TX 0x00000401


int aux1=0;
int aux2=0;
int aux3=0;
//----------Vector for Stepper Unipolar 28BYJ------------//
uint8_t HalfStep [****-J-****] = {****-B-****,0x04,0x02,0x01};
uint8_t FullStep [******] = {0x0c,0x06,****-C-****,0x09};
/*Remember: both 2048 = 1 revolution*/

uint8_t current_step=0;
uint32_t counter=0;
uint32_t delay_value=0;
char steps[4];
//-------------------------PWM------------------------//
#define PWM_FREQUENCY 916
#define PI 3.14159f
#define GPIO_PF2_M0PWM2 0x00050806

void UARTIntHandler(void)
{
 uint32_t ui32Status,pwm_value;
    uint8_t dig1,dig2,dig3,dig4;
    ui32Status = MAP_UARTIntStatus(UART0_BASE, true);

    MAP_UARTIntClear(UART0_BASE, ui32Status);
    uint8_t ind=0;
    while(MAP_UARTCharsAvail(UART0_BASE))
    {
    data[ind]=MAP_UARTCharGetNonBlocking(UART0_BASE);
       
        MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);

        
        SysCtlDelay(g_ui32SysClock / (1000 * 3));

        MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
        ind++;
    }
    
    if(data[0]=='M' && data[5]=='_' && data[6]=='D'){
    dig1=data[1]-48;
    dig2=data[2]-48;
    dig3=data[3]-48;
    dig4=data[4]-48;
    pwm_value=dig1*1000+dig2*100+dig3*10+dig4;    
        delay_value=data[7]-48;
    PWMPulseWidthSet(PWM0_BASE,******,pwm_value);
    }
}

int main(void)
{

volatile uint32_t ui32PWMClock;
volatile uint32_t ui32Load;
volatile uint32_t ui32Index;
volatile uint32_t ui32Level;
ui32SysClkFreq=SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
SysCtlPeripheralEnable(****-D-****);
SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
GPIOPinConfigure(GPIO_PA0_U0RX);
GPIOPinConfigure(GPIO_PA1_U0TX);
GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1);
UARTConfigSetExpClk(UART0_BASE, ui32SysClkFreq, 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
IntMasterEnable();
IntEnable(INT_UART0);
UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);

GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,******);
GPIOPadConfigSet(GPIO_PORTC_BASE,****-E-****, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE,GPIO_PIN_0|****-F-****);

PWMClockSet(PWM0_BASE,****-G-****);
GPIOPinConfigure(****-P-****);
GPIOPinTypePWM(****-Q-****,GPIO_PIN_2);
ui32PWMClock=ui32SysClkFreq/(******);
ui32Load=(ui32PWMClock/PWM_FREQUENCY)-1;
PWMGenConfigure(PWM0_BASE,******,PWM_GEN_MODE_DOWN);
PWMGenPeriodSet(PWM0_BASE,****-H-****,ui32Load);

PWMPulseWidthSet(PWM0_BASE,*******,ui32Load/2);
PWMOutputState(PWM0_BASE,****-I-****,true);
PWMGenEnable(PWM0_BASE,******);

 

while(1)
{

 


GPIOPinWrite(****-O-****, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, steps[current_step]);
counter++;
current_step++;
if(current_step>3) current_step=0;
SysCtlDelay(40000*delay_value); 

if(spin==0){

GPIOPinWrite(GPIO_PORTP_BASE, ****-S-****, 0);
GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_1, 1);
steps[0]=****-T-****[0];
steps[1]=******[1];
steps[2]=******[2];
steps[3]=******[3];

if(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6)==0) ****-K-****=1;

}else if(spin==1){

GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_0, 1);
GPIOPinWrite(GPIO_PORTP_BASE, GPIO_PIN_1, 0);
steps[0]=FullStep[0];
steps[1]=FullStep[1];
steps[2]=FullStep[2];
steps[3]=FullStep[3];

if(GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_6)==0) spin=0;

}

int revs=counter/(****-M-****);
UARTCharPut(UART0_BASE, 'R');
UARTCharPut(UART0_BASE, 'E');
UARTCharPut(UART0_BASE, 'V');
UARTCharPut(UART0_BASE, 'S');
UARTCharPut(UART0_BASE, '_');
if(revs<10){

UARTCharPut(UART0_BASE, revs+****-L-****);
UARTCharPut(UART0_BASE, '\n');
}else if(revs>9 && revs<100){

aux1=revs%****-N-****;
aux2=revs/10;


UARTCharPut(UART0_BASE, aux2+******);
UARTCharPut(UART0_BASE, aux1+******);
UARTCharPut(UART0_BASE, '\n');
}else if(revs>99 && revs<1000){


aux3=revs/100;
aux1=(revs-(****-R-****)*100)/10;
aux2=revs%10;


UARTCharPut(UART0_BASE, aux3+******);
UARTCharPut(UART0_BASE, aux1+******);
UARTCharPut(UART0_BASE, aux2+******);
UARTCharPut(UART0_BASE, '\n');
}

 

}
}