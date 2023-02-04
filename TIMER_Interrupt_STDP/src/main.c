
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

// default clock speed = 84MHz

void GPIO_Config(void);
void TIM4_Config(void);
void NVIC_TIM4_Config(void);


int main(void)
{
	GPIO_Config();
	TIM4_Config();
	NVIC_TIM4_Config();

  while (1)
  {

  }
}


void TIM4_Config(void)               // this configuration counts up to 10000 per second.
{
	TIM_TimeBaseInitTypeDef tim4;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);            // tim4 clock buss is activated

	tim4.TIM_ClockDivision = TIM_CKD_DIV1;                          // default clock speed / divided 1 = 84MHz
	tim4.TIM_CounterMode = TIM_CounterMode_Up;                      // counting up
	tim4.TIM_Period = 9999;                                         //  84 000 000 / ( (9999 + 1) * (8399 + 1) ) = 1 Hertz = 1 second
	tim4.TIM_Prescaler = 8399;
	tim4.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &tim4);									// initialized tim4
	TIM_Cmd(TIM4, ENABLE);
}


void NVIC_TIM4_Config()									// timer4 interrupt configuration
{
	NVIC_InitTypeDef tim4_it;

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	tim4_it.NVIC_IRQChannel = TIM4_IRQn;
	tim4_it.NVIC_IRQChannelCmd = ENABLE;
	tim4_it.NVIC_IRQChannelPreemptionPriority = 0;
	tim4_it.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&tim4_it);
}


void GPIO_Config(void)
{
	GPIO_InitTypeDef Led;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  // activated the D port clock buss

	Led.GPIO_Mode = GPIO_Mode_OUT;
	Led.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	Led.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Led.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOD, &Led);  // configuration is initialized
}


void TIM4_IRQHandler()
{
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);				// we have to use this function to clear the interrupt
	GPIO_ToggleBits(GPIOD, GPIO_Pin_All);
}





/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
