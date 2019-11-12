# STM32F446-Timer

This will blink the led every 1s. 

The clock main core frequency is 50Mhz. 
The TIM2_IRQHandler is invoked every 1s. The reason are the following:

******************************************************************************************************************************************
*Clock Cycles*

First, some background information. The typical Arduino has a 16MHz oscillator. A 16MHz oscillator results in the microcontroller having a clock cycle once every 16-millionth of a second. A clock cycle is roughly the time it takes for one instruction cycle (there are exceptions). Therefore, on the Arduino, each clock cycle is 1/16,000,000 of a second, which is:

0.0000000625 seconds

0.0000625 milliseconds (ms)

0.0625 microseconds (µs)

*Prescaler*

While technically a prescaler divides the timer, I like to think of it as a multiplier. For example, with an Arduino clock cycle occurring every 1/16,000,000 of a second, applying a 64 prescale means Timer #0 is ticking at 64 times the base oscillator rate, or 64*1/16,000,000, which is every:

0.000004 seconds

0.004 ms

4 µs

*Timer Counter*

Timer #0 has an 8-bit counter register (TCNT0) which is incremented by 1 every 0.004 milliseconds. The maximum 8-bit value the timer can hold is 255 (hexadecimal 0xFF). Therefore, when the timer attempts to count to 256, it “rolls over” to 0. This “roll over” is called an “overflow” in microcontroller parlance. Take note the counter ticks off 256 times, not 255 times (because 0 + 255 = 256).

*Overflow Interrupt*

The Timer #0 overflow can trigger an interrupt. When an interrupt occurs, the Arduino halts execution of the running program and then calls the specific interrupt subroutine. This subroutine is typically called an “interrupt handler.”



******************************************************************************************************************************************

In our case, we will set the prescaler to 50Mhz/1000 = 50.000. This means that our timer will tick each 1/50Mhz * 50.000 = 0.001s which is 1ms. 

Auto-reload register (TIM2->ARR) specifies after how many ticks, the timer should generate an interrupt. 
