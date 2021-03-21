# Cheat sheet ek - tm4c1294xl

## GPIO Output

### Example code

~~~c
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
~~~

## GPIO Input

### Example code

~~~c
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); 
MAP_GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_INT_PIN_0,GPIO_FALLING_EDGE); //Falling edge or rising edge
GPIOIntRegister(GPIO_PORTJ_BASE, GPIOIntHandler);
GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
~~~

## PWM

### Example code

~~~c
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
MAP_GPIOPinConfigure(GPIO_PK5_M0PWM7);
MAP_GPIOPinTypePWM(GPIO_PORTK_BASE, GPIO_PIN_5);
MAP_PWMClockSet(PWM0_BASE, PWM_SYSCLK_DIV_8);
ui32PWMClockRate = g_ui32SysClock / 8;
MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, (ui32PWMClockRate / freq_m1));
g_ui32PWMIncrement = ((ui32PWMClockRate / freq_m1) / 1000);
MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, g_ui32PWMIncrement);
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
MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock);
MAP_IntEnable(INT_TIMER0A);
MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
MAP_TimerEnable(TIMER0_BASE, TIMER_A);
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
