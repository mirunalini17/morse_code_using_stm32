//only LED blink
// ===============================
// STM32 Blue Pill Morse Code
// LED: PC13 (ACTIVE LOW)
// Bare Metal Version
// ===============================

#define RCC_APB2ENR (*(volatile unsigned int*)0x40021018)
#define GPIOC_CRH   (*(volatile unsigned int*)0x40011004)
#define GPIOC_ODR   (*(volatile unsigned int*)0x4001100C)

#define GPIOC_EN (1<<4)
#define LED      (1<<13)



// ===============================
// GPIO Init
// ===============================
void gpio_init(void)
{
    RCC_APB2ENR |= GPIOC_EN;

    // PC13 output push-pull (2 MHz)
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);
}


void delay(volatile int t)
{
    for(int i = 0; i < t * 8000; i++);
    // increased loop for visible delay
}

// ===============================
// DOT = short blink
// ===============================
void dot(void)
{
    GPIOC_ODR &= ~LED;   // ON
    delay(30);           // visible short ON

    GPIOC_ODR |= LED;    // OFF
    delay(30);           // gap
}

// ===============================
// DASH = long blink
// ===============================
void dash(void)
{
    GPIOC_ODR &= ~LED;   // ON
    delay(90);           // long ON

    GPIOC_ODR |= LED;    // OFF
    delay(30);           // gap
}


// ===============================
// Character Mapping
// (Start with essential letters)
// ===============================
void morse_char(char c)
{
    switch(c)
    {
        case 'H': dot(); dot(); dot(); dot(); break;
        case 'E': dot(); break;
        case 'L': dot(); dash(); dot(); dot(); break;
        case 'O': dash(); dash(); dash(); break;

        case 'S': dot(); dot(); dot(); break;
        case 'T': dash(); break;
        case 'M': dash(); dash(); break;
        case 'A': dot(); dash(); break;

        default: break;
    }

    // gap between letters
    delay(3);
}

// ===============================
// String to Morse
// ===============================
void morse_string(char *str)
{
    while(*str)
    {
        if(*str == ' ')
        {
            delay(7); // word gap
        }
        else
        {
            morse_char(*str);
        }
        str++;
    }
}

// ===============================
// MAIN
// ===============================
int main(void)
{
    gpio_init();

    while(1)
    {
        morse_string("HELLO STM32");
        delay(10); // pause before repeat
    }
}
