#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<sys/time.h>
#include"gpio.h"

//Debounce interval
#define DEBOUNCE_MS 50   
// Button struct
typedef struct{
    bool pressed;
    bool triggered;
    unsigned long last_change_ms;
    void(*callback)(void);
}ButtonState;

static ButtonState buttons[BUTTON_COUNT];

// Simulating system timer
static unsigned long get_ms(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*1000+tv.tv_usec/1000;
}

int set_push_button(enum PUSH_BUTTON push_button, void (*callback_func)(void)){
    if(push_button<0 || push_button>=BUTTON_COUNT){
        return -1;
    }

    buttons[push_button].pressed=false;
    buttons[push_button].triggered=false;
    buttons[push_button].callback=callback_func;
    buttons[push_button].last_change_ms=get_ms();

    return 0;
}

// Using keyboard simulates button
static bool read_button(enum PUSH_BUTTON button) {
    if (button == PB_1 && (GetAsyncKeyState('1') & 0x8000)) {
        return true;
    }
    if (button == PB_2 && (GetAsyncKeyState('2') & 0x8000)) {
        return true;
    }
    return false;
}


void push_button_app(void){
    unsigned long now;
    now=get_ms();
    for(int i=0;i<BUTTON_COUNT;i++){
        bool current_input=read_button(i);
        if(!current_input && buttons[i].pressed){
            buttons[i].pressed=false;
            buttons[i].triggered=false;
            printf("Button %d released\n",i);
        }                                                        // At any time, the press was not detected, the button was released
        if(current_input && !buttons[i].pressed){
            buttons[i].pressed=true;
            buttons[i].last_change_ms=now;
        }                                                       // Detecting press, timing starts
        if(current_input && buttons[i].pressed && !buttons[i].triggered && now-buttons[i].last_change_ms>=DEBOUNCE_MS){
                printf("Button %d pressed\n",i);
                buttons[i].triggered=true;                     // Only triggered once
                if(buttons[i].callback){
                    buttons[i].callback();
                }
            
        }
    }
}