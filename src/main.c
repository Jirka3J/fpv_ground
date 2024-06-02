#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
//#include "uart1.h"

    int32_t latitude = 495539350;
    int32_t longitude = 171031850;
    int32_t lockedLatitude = 495539350;
    int32_t lockedLongitude = 171031850;

void init(void)
{
    init_milis();
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW);

    TIM2_TimeBaseInit(TIM2_PRESCALER_256, 1250);
    TIM2_OC1Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE, 1 , TIM2_OCPOLARITY_LOW);
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_Cmd(ENABLE);
}

int getDiff(now,locked){
    int16_t x = now - locked;
    return x; 
}

int getAngle(){
    int16_t a = getDiff(latitude,lockedLatitude);
    int16_t b = getDiff(longitude,lockedLongitude);
    int16_t x =
}

int main(void)
{

    uint32_t time = 0;
    uint16_t value = 100;

    init();

    while (1) {



            if (milis() - time > 100 ) {
                TIM2_SetCompare1(value++);

                time = milis();

                }
        if (value>1000) {value=10;}
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
