#include "delay.h"

static __IO uint32_t TimingDelay = 0;

void Delay(__IO uint32_t nCount)
{
  TimingDelay = nCount;

  /* Enable the SysTick Counter */
  SysTick_Config(720000);
  while(TimingDelay != 0);
  /* Disable the SysTick Counter */
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE;

   /* Clear the SysTick Counter */
   SysTick->VAL = (uint32_t)0x0;
}
void Decrement_TimingDelay(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}
