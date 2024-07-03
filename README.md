# Cheat sheet ek 

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
MAP_GPIOPinConfigure(GPIO_PF0_M0PWM0); // Configure PWM by table pin name
MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);

MAP_PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_64);
ui32PWMClockRate = g_ui32SysClock / 64;
MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
                    PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, (ui32PWMClockRate / 1000));
MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1200);
MAP_PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
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
|ACP|Accelerator Coherency Port|
|ADC|Analog to digital converter|
|AHB|Advanced High Performance Bus|
|AHR|Advanced High-performance bus|
|FF|Flip flops|
|APB|Advanced peripheral bus|
|APU|Application processing unit|
|ARM|Advanced risk machine|
|ASIC|Application Specific Integrated Circuit|
|ASIP|Application-Specific Instruction Processor|
|AXI|Advanced extensible interface|
|AXL|Advanced extensible interface|
|BRAM|Block ram|
|CAN|Controller area network|
|CLB|Configurable logic block|
|DAC|Digital to analog converter|
|Dcache|Data|
|DDR|Double data rate|
|DMA|Direct memory access|
|DSP|Digital signal processor|
|ECC|Error Correction Code|
|EDA|Electronic design automation|
|ETM|Embedded trace macrocell|
|LPDDR|Low Power Double Data Rate|
|FPGA|Field programmable gate array|
|FPU|Floating point unit|
|GPGPU|General Purpose Graphics Processing Unit|
|GPIO|General purpose input output|
|GPU|Graphics processing unit|
|HDL|Hardware description language|
|I2C|Inter-integrated circuit|
|Icache|Instructions|
|IP|Intellectual property|
|LPDDR|Low power DDR|
|LUT|Look-up table|
|MAC|multiple and accumulate|
|MCU|MicroController Unit|
|MMU|Memory management unit|
|MPSoC|MultiProcessor SoC|
|MPU|Memory protection unit|
|NEON|SIMD processor|
|OCM|On chip memory|
|PL|Programmable logic|
|PWM|Pulse width modulation|
|RAM|Random access memory|
|RPU|Raid processing unit|
|RTL|Register Transfer Level|
|RTOS|Real Time Operating System|
|SBC|Single Board COmputer|
|SCU|Snoop Control Unit|
|SDP|Digital Signal Processor|
|SIMD|Single Instruction Multiple Data|
|SoC|System on a Chip|
|SPI|Serial peripheral interface|
|TCM|Tightly coupled memory|
|TPU|Tensor Processing Unit|
|TPY|Tensor processing unit by google|
|UART|Universal asynchronous receiver transmitter|
|USB|Universal serial bus|
|VHDL|Very High Speed Integrated Circuit Hardware Description Language|
|VLSI|Very large-scale integration|
