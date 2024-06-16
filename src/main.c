#include <stdbool.h>
#include <stm8s.h>
#include <stdio.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
#include "uart1.h"
#define SCALE 10000



#define RAD_TO_DEG (180.0 / 3.14)

    int32_t latitude = 495539350;
    int32_t longitude = 171031850;
    int32_t lockedLatitude = 495539350;
    int32_t lockedLongitude = 171031850;
    uint16_t lastPWM = 0;

void init(void){
    init_milis();
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW);

    TIM2_TimeBaseInit(TIM2_PRESCALER_32, 10000);
    TIM2_OC1Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE, 1000 , TIM2_OCPOLARITY_HIGH);
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_Cmd(ENABLE);

    init_uart1();
}

// For future I CC = 500/5%DUTY >> 0% and CC = 1000/10%DUTY >> 100%


int32_t getDiff(int32_t now,int32_t locked){
    return now - locked; 
}

int getAngle(){
    int16_t decimal = getDiff(latitude,lockedLatitude)/getDiff(longitude,lockedLongitude);
    return arctan_fixed(decimal,10);
}


uint16_t toPWM(int32_t degrees){
    if(degrees>6000|degrees<0){
        return lastPWM;
    }else{
        return degrees*833/10000+500;
    }
}
//
int32_t arctan_fixed(int16_t x, uint8_t N) {
    int32_t arctan_x = 0;
    int32_t x_pow = x;  

    for (uint8_t n = 0; n < N; n++) {
        int16_t term = x_pow / (2 * n + 1);
        if (n % 2 == 0) {
            arctan_x += term;
        } else {
            arctan_x -= term;
        }
        x_pow = (x_pow * x / SCALE) * x / SCALE;
    }

    return arctan_x*1800/3141;
}


int main(void)
{

    uint32_t time = 0;
    uint16_t value = 500;
    uint16_t iteration = 0;
    uint8_t n = 10;
    uint16_t duty;

    init();

    while (1) {
        iteration = milis();
        uint16_t x = arctan_fixed(8000,n);
        //if (milis() - time > 10 ) {
        //    value=value+10;
        duty = toPWM(x);
        TIM2_SetCompare1(duty);
        //    time = milis();
        //    }
        //if (value>1000) {value=500;}
        iteration = milis()-iteration;
        if (milis() - time > 1000 ) {
            time = milis();
            printf("%d,%d",x,duty);
            printf("délka smyčky%d,\n",iteration);
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
