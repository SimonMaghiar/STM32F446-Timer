#include "main.h"
#include "string.h"
#include "stdio.h"
#include "systemclock.h"


void start_timer(TIM_TypeDef *TIMx, uint16_t ms);


int main(void)
{

  NVIC_SetPriority(TIM2_IRQn, 0x03);
  NVIC_EnableIRQ(TIM2_IRQn);
  start_timer(TIM2, 1000);

  while (1)
  {

  }
}



void start_timer(TIM_TypeDef *TIMx, uint16_t ms) {
  // Start by making sure the timer's 'counter' is off.
  TIMx->CR1 &= ~(TIM_CR1_CEN);
  // Next, reset the peripheral. (This is where a HAL can help)
  if (TIMx == TIM2) {
    //enable TIM2 clock peripheral
    RCC->APB1ENR |=  (RCC_APB1RSTR_TIM2RST);
  }
  // Set the timer prescaler/autoreload timing registers.
  // (These are 16-bit timers, so this won't work with >65MHz.)
  TIMx->PSC   = HAL_RCC_GetHCLKFreq() / 1000;
  TIMx->ARR   = ms;
  // Send an update event to reset the timer and apply settings.
  TIMx->EGR  |= TIM_EGR_UG;
  // Enable the hardware interrupt.
  TIMx->DIER |= TIM_DIER_UIE;
  // Enable the timer.
  TIMx->CR1  |= TIM_CR1_CEN;
}


void TIM2_IRQHandler(void) {
  // Handle a timer 'update' interrupt event
  if (TIM2->SR & TIM_SR_UIF) {
    TIM2->SR &= ~(TIM_SR_UIF);
    HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_8);
  }
}
