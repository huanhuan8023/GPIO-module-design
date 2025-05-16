#include<stdio.h>
#include<sys/time.h>
#include"gpio.h"

// LED struct
typedef struct{
     unsigned int interval_ms;         //support fast blink,slow blink and constant on
     bool active;                     //support active low and active high
     bool on;                        //determine is on or off
     unsigned long last_toggle_ms;  //last switching time
}LEDState;

static LEDState leds[LED_COUNT];

// Simulating system timer
static unsigned long get_ms(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*1000+tv.tv_usec/1000;
}

// Setting LED blinking time(0 is constant on,-1 is constant off)
int set_led(enum LED led_number, unsigned int interval){
    if(led_number<0 || led_number>=LED_COUNT){
        return -1;
    }

    leds[led_number].interval_ms=interval;
    leds[led_number].last_toggle_ms=get_ms();

    if(interval==0){
        leds[led_number].on=true;
        if(led_number==0) printf("LED Green constant on\n");
        if(led_number==1) printf("LED Red constant on\n");
    }
    else if(interval==-1){
        leds[led_number].on=false;
        if(led_number==0) printf("LED Green constant off\n");
        if(led_number==1) printf("LED Red constant off\n");
    }
    else{
        leds[led_number].on=false;
        if(led_number==0) printf("LED Green blink every %u ms\n",interval);
        if(led_number==1) printf("LED Red blink every %u ms\n",interval);
    }

    return 0;
}

// Non-block LED control
void led_app(void){
    unsigned long now=get_ms();

    for(int i=0;i<LED_COUNT;i++){
        if (leds[i].interval_ms==0) {
            if (!leds[i].on) {
                leds[i].on=true;
                printf("LED %s ON (Constant)\n", i==0 ? "Green" : "Red");
            }
            continue;
        }

        if (leds[i].interval_ms==-1) {
            if (leds[i].on) {
                leds[i].on=false;
                printf("LED %s OFF (Constant)\n", i == 0 ? "Green" : "Red");
            }
            continue;
        }

        if(now-leds[i].last_toggle_ms>=leds[i].interval_ms){
            leds[i].on=!leds[i].on;
            leds[i].last_toggle_ms=now;
            
            if(i==0){
                printf("LED Green %s\n", leds[i].on? "ON":"OFF");
            }

            if(i==1){
                printf("LED Red %s\n", leds[i].on? "ON":"OFF");
            }
        }
    }
}

