#define RCC_APB2ENR (*(volatile unsigned int*)0x40021018)
#define RCC_APB1ENR (*(volatile unsigned int*)0x4002101C)

#define GPIOA_CRL   (*(volatile unsigned int*)0x40010800)
#define GPIOC_CRH   (*(volatile unsigned int*)0x40011004)
#define GPIOC_ODR   (*(volatile unsigned int*)0x4001100C)

// USART2
#define USART2_SR   (*(volatile unsigned int*)0x40004400)
#define USART2_DR   (*(volatile unsigned int*)0x40004404)
#define USART2_BRR  (*(volatile unsigned int*)0x40004408)
#define USART2_CR1  (*(volatile unsigned int*)0x4000440C)

#define LED (1<<13)

// ---------------- DELAY ----------------
void delay(volatile int t)
{
    for(int i = 0; i < t * 8000; i++);
}

// ---------------- UART ----------------
void uart_tx(char c)
{
    while(!(USART2_SR & (1<<7)));
    USART2_DR = c;
}

void uart_print(char *s)
{
    while(*s)
        uart_tx(*s++);
}

// ---------------- LED ----------------
void dot()
{
    GPIOC_ODR &= ~LED;
    delay(30);
    GPIOC_ODR |= LED;
    delay(30);
}

void dash()
{
    GPIOC_ODR &= ~LED;
    delay(90);
    GPIOC_ODR |= LED;
    delay(30);
}

char *morse_table[] =
{
    ".-",    // A
    "-...",  // B
    "-.-.",  // C
    "-..",   // D
    ".",     // E
    "..-.",  // F
    "--.",   // G
    "....",  // H
    "..",    // I
    ".---",  // J
    "-.-",   // K
    ".-..",  // L
    "--",    // M
    "-.",    // N
    "---",   // O
    ".--.",  // P
    "--.-",  // Q
    ".-.",   // R
    "...",   // S
    "-",     // T
    "..-",   // U
    "...-",  // V
    ".--",   // W
    "-..-",  // X
    "-.--",  // Y
    "--.."   // Z
};

// ---------------- MORSE ----------------
void morse_char(char c)
{
    char *code;

    if(c >= 'a' && c <= 'z')
        c -= 32;

    if(c < 'A' || c > 'Z')
    {
        uart_print("? unknown\r\n");
        return;
    }

    code = morse_table[c - 'A'];

    uart_tx(c);
    uart_tx(' ');
    uart_print(code);
    uart_print("\r\n");

    while(*code)
    {
        if(*code == '.')
            dot();
        else if(*code == '-')
            dash();

        code++;
    }

    delay(80);
}

// ---------------- INIT ----------------
void uart2_init()
{
    RCC_APB2ENR |= (1<<2);   // GPIOA
    RCC_APB1ENR |= (1<<17);  // USART2

    // PA2 TX
    GPIOA_CRL &= ~(0xF << 8);
    GPIOA_CRL |=  (0xB << 8);

    // PA3 RX
    GPIOA_CRL &= ~(0xF << 12);
    GPIOA_CRL |=  (0x4 << 12);

    USART2_BRR = 0x341; // 9600

    USART2_CR1 = (1<<13) | (1<<3) | (1<<2);
}

void gpio_init()
{
    RCC_APB2ENR |= (1<<4); // GPIOC clock

    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    GPIOC_ODR |= LED; // LED OFF
}

// ---------------- MAIN ----------------
int main()
{
    gpio_init();
    uart2_init();

    uart_print("MORSE READY\r\n");

    while(1)
    {
        char c;

        while(!(USART2_SR & (1<<5))); // RXNE
        c = USART2_DR;

        if(c == '\r' || c == '\n')
            continue;

        if(c >= 'a' && c <= 'z')
            c -= 32;

        morse_char(c);
    }
}
