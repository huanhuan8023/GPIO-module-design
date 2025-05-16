#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  
#include "gpio.h"

// The callback function of button 1 controls the on and off of the green led 
void toggle_green_led(){
    static bool on=false;
    on=!on;
    printf("-> LED Green changed from %s to %s\n", on ? "OFF" :"ON",on ? "ON" :"OFF" );
    set_led(GREEN,on ? 0:-1);
}

// The callback function of button 2 can change RED led blink interval in 500, 1000, 2000 ms
void change_red_interval(){
    static int state=0;
    int intervals[]={500,1000,2000};
    int pre_state=state;
    state=(state+1)%3;
    printf("-> LED Red interval changed from %d ms to %d ms\n",intervals[pre_state], intervals[state]);
    set_led(RED,intervals[state]);
}

int main(void) {
    // Initialize the LED
    set_led(GREEN, -1);  
    set_led(RED, 500);   
    
    // Initialize the Button
    set_push_button(PB_1,toggle_green_led);
    set_push_button(PB_2,change_red_interval);

    printf("=== GPIO Simulation Start ===\n");
    printf("Press '1' for PB_1 (LED Green toggle)\n");
    printf("Press '2' for PB_2 (Change LED Red blank interval)\n");

    while (1) {
        led_app();  // Handle LED status updates non-blocking
        push_button_app(); //Button detection and callback execution
        Sleep(10);    

    }

    return 0;
}
