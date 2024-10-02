# include <avr/io.h>
#include <util/delay.h>
# include <gpio.h>

# define LED_GREEN PB5
# define WAIT 250
# define LED_RED PB0
#define BTN DD0

int main()
{
    // set pin PB5 as output
    // DDRB = DDRB | (1 << LED_GREEN);

    GPIO_mode_output(&DDRB, LED_GREEN);
    GPIO_mode_output(&DDRB, LED_RED);
    GPIO_mode_input_pullup(&DDRD, BTN);

    // set PB5 to low
    //PORTB = PORTB & ~ (1 << LED_GREEN);

    GPIO_write_low(&PORTB, LED_GREEN);
    GPIO_write_low(&PORTB, LED_RED);

    while(1)//pokud je splneno
    {
        if (GPIO_read(&PIND, BTN) == 0)
    
    {
        // blink a LED
        PORTB = PORTB ^ (1 << LED_GREEN);
        PORTB = PORTB ^ (1 << LED_RED);
            _delay_ms(WAIT);
    }
    }
    return 0;
}

