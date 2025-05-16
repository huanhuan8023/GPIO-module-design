#include <stdbool.h>
#include <stdint.h>

enum LED{
    GREEN,
    RED,
    LED_COUNT
};

enum PUSH_BUTTON{
    PB_1, // toggle Green led
    PB_2, // can change RED led blink interval in 500, 1000, 2000 ms
    BUTTON_COUNT
};

int set_led(enum LED led_number, unsigned int interval);
int set_push_button(enum PUSH_BUTTON push_button, void (*callback_func)(void));
void led_app(void);
void push_button_app(void);


