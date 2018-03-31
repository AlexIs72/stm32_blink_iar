#include "stm32f10x.h"

#include "stm32f10x_rcc.h"

RCC_ClocksTypeDef RCC_Clocks;


void led_init_gpio()
{
    // Разрешаем тактирование порта GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_DeInit(GPIOC);

    
    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);

    /*
        Модули Blue Pill имеют на борту светодиод, подключенный к PC13.

        ВНИМАНИЕ: Порт PC13 имеет очень слабый источник тока (3мА макс) и ни в коем
        случае не должен использоваться как драйвер светодиода. Только как открытый коллектор.
    */

    // Режим порта ВЫВОД, открытый коллектор.
    gpio.GPIO_Mode=GPIO_Mode_Out_OD;
    gpio.GPIO_Speed=GPIO_Speed_2MHz;
    gpio.GPIO_Pin=GPIO_Pin_13;
    GPIO_Init(GPIOC, &gpio);

    // Выключаем светодиод
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}

void led_init()
{
    led_init_gpio();
//    modledState=modled_st_idle;
//    modledStart=global_count;
}

void led_on() {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}

void led_off() {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
}


int main() {

	RCC_GetClocksFreq(&RCC_Clocks);

    led_init_gpio();
    
    // Инициализируем таймер SysTick чтобы он срабатывал каждую /*милли*/секунду
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 10/*00 */);
    
    while(1) {
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
    }
    
	return 0;
}