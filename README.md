# Cheat sheet ek - tm4c1294xl

## GPIO Output

### Example code

~~~c
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Enable Port F
MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); // Asign Pin F0 as Output
~~~

## GPIO Input

### Example code

~~~c
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); // Enable Port J
MAP_GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0); // Asign Pin J0 as Input
GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU); // Set input pin with 4mA
GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_INT_PIN_0,GPIO_FALLING_EDGE); // Set pin J0 as falling edge (Falling edge or rising edge)
GPIOIntRegister(GPIO_PORTJ_BASE, GPIOIntHandler); // Set void as an action
GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0); // Enable pin J0
~~~

## PWM

### Example code

~~~c
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0); // Enable PWM0
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1); // Enable Timer 1
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Enable port F
MAP_GPIOPinConfigure(GPIO_PF0_M0PWM0); // Configure PWM by table pin name
MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0); // Asign pin F0 as PWM 
MAP_PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_8); // Set PWM clock with prescaler of 8 (8, 64)
ui32PWMClockRate = g_ui32SysClock / 8; // Divide clock with prescaler
MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); // Configure generator 0 based on table, most of time gen (we have up"triangular signal" and down"sawtooth signal"), no sync for 2 generators 0 independet (we have dependent and independent)
MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, (ui32PWMClockRate / freq_m1)); // Configure PWM frequency in Hz
g_ui32PWMIncrement = ((ui32PWMClockRate / freq_m1) / 1000); // pulse width variable
MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, g_ui32PWMIncrement); // Set pulse width
~~~

### Code table

| Pin Name | Pin Number | Pin Assignment | Pin Type | Buffer Type | Description                                                                           |
|----------|:----------:|:--------------:|:--------:|:-----------:|---------------------------------------------------------------------------------------|
| M0FAULT0 |     46     |     PF4 (6)    |     I    |     TTL     | Motion Control Module 0 PWM Fault 0.                                                  |
| M0FAULT1 |     61     |     PK6 (6)    |     I    |     TTL     | Motion Control Module 0 PWM Fault 1.                                                  |
| M0FAULT2 |     60     |     PK7 (6)    |     I    |     TTL     | Motion Control Module 0 PWM Fault 2.                                                  |
| M0FAULT3 |     81     |     PL0 (6)    |     I    |     TTL     | Motion Control Module 0 PWM Fault 3.                                                  |
| M0PWM0   |     42     |     PF0 (6)    |     O    |     TTL     | Motion Control Module 0 PWM 0. This signal is controlled by Module 0 PWM Generator 0. |
| M0PWM1   |     43     |     PF1 (6)    |     O    |     TTL     | Motion Control Module 0 PWM 1. This signal is controlled by Module 0 PWM Generator 0. |
| M0PWM2   |     44     |     PF2 (6)    |     O    |     TTL     | Motion Control Module 0 PWM 2. This signal is controlled by Module 0 PWM Generator 1. |
| M0PWM3   |     45     |     PF3 (6)    |     O    |     TTL     | Motion Control Module 0 PWM 3. This signal is controlled by Module 0 PWM Generator 1. |
| M0PWM4   |     49     |     PG0 (6)    |     O    |     TTL     | Motion Control Module 0 PWM 4. This signal is controlled by Module 0 PWM Generator 2. |
| M0PWM5   |     50     |     PG1 (6)    |     O    |     TTL     | Motion Control Module 0 PWM 5. This signal is controlled by Module 0 PWM Generator 2. |
| M0PWM6   |     63     |     PK4 (6)    |     O    |     TTL     | Motion Control Module 0 PWM 6. This signal is controlled by Module 0 PWM Generator 3. |
| M0PWM7   |     62     |     PK5 (6)    |     O    |     TTL     | Motion Control Module 0 PWM 7. This signal is controlled by Module 0 PWM Generator 3. |

## Timer

### Example code

~~~c
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); // Enable timer 0
MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); // Configure timeras CFG
MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock); // Configure timer 0A with g_ui32SysClock
MAP_IntEnable(INT_TIMER0A); // Enable timer 0A
MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Enable timer 0A
MAP_TimerEnable(TIMER0_BASE, TIMER_A); // Enable timer 0A
~~~

## UART

### Example code

~~~c
MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
MAP_UARTConfigSetExpClk(UART0_BASE, g_ui32SysClock, 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                            UART_CONFIG_PAR_NONE));
MAP_IntEnable(INT_UART0);
MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
~~~

## Delay

### Example code

~~~c
for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++){}
~~~

---

## Siglas
|Acronym|Meaning|
|:-----:|-------|
|SCU | Snoop control unit|
|FPU | floating point unit|
|DSP | Digital signal processor|
|ETM | Embedded trace macrocell|
|SIMD | Single instruction multiple data|
|MCU | Microcontroller unit|
|GPU | Graphics processing unit|
|SOC | System on chip|
|AXL | Advanced extensible interface|
|AHR | Advanced High-performance bus|
|APB | Advanced peripheral bus|
|RPU | Real-time processing unit|
|APU | Application processing unit|
|ARM | Advanced risk machine|
|FPU | Floating point unit|
|NEON | SIMD processor|
|MMU | Memory management unit|
|Icache | Instructions|
|Dcache | Data|
|AXI | Advanced extensible interface|
|RPU | Raid processing unit|
|MPU | Memory protection unit|
|TCM | Tightly coupled memory|
|OCM | On chip memory|
|GPIO | General purpose input output|
|ADC | Analog to digital converter|
|SPI | Serial peripheral interface|
|I2C | Inter-integrated circuit|
|PWM | Pulse width modulation|
|DAC | Digital to analog converter|
|UART | Universal asynchronous receiver transmitter|
|DDR | Double data rate|
|LPDDR | Low power DDR|
|USB | Universal serial bus|
|CAN | Controller area network|
|DMA | Direct memory access|
|PL | Programmable logic|
|FPGA | Field programmable gate array|
|CLB | Configurable logic block|
|FF | Flip flops|
|LUT | Look-up table|
|EDA | Electronic design automation|
|HDL | Hardware description language|
|DSP | Digital signal processor|
|RAM | Random access memory|
|BRAM | Block ram|
|IP | Intellectual property|
|MAC | multiple and accumulate|
|TPY | Tensor processing unit by google|