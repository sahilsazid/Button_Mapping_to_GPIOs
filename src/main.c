#include <stm32f446xx.h>
#define GPIOC_PIN_0 (1U << 0)
#define GPIOC_PIN_1 (1U << 1)
#define GPIOC_PIN_2 (1U << 2)

void toggle_slow(void);
void toggle_medium(void);
void toggle_fast(void);

typedef struct
{

    GPIO_TypeDef *PORT;

    uint16_t PIN;

    void (*action)(void);

} Button_Mapping;

int main()
{

    RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN);
    RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOCEN);

    GPIOA->MODER &= ~(0x3 << (0 * 2)); // Clear bits for PA0
    GPIOA->MODER |= (0x1 << (0 * 2));  // Set PA0 as Genral Purpose Output mode

    GPIOA->MODER &= ~(0x3 << (1 * 2)); // Clear bits for PA1
    GPIOA->MODER |= (0x1 << (1 * 2));  // Set PA1 as Output

    GPIOA->MODER &= ~(0x3 << (4 * 2)); // Clear bits for PA4
    GPIOA->MODER |= (0x1 << (4 * 2));  // Set PA4 as Output

    // 3. Configure PC0, PC1, PC2 as INPUT (MODER = 00)
    GPIOC->MODER &= ~(0x3 << (0 * 2)); // Clear bits for PC0
    GPIOC->MODER &= ~(0x3 << (1 * 2)); // Clear bits for PC1
    GPIOC->MODER &= ~(0x3 << (2 * 2)); // Clear bits for PC2

    GPIOC->PUPDR &= ~(0x3 << (0 * 2)); // Clear bits for PC0
    GPIOC->PUPDR |= (0x2 << (0 * 2));  // Set pull-down for PC0
    GPIOC->PUPDR &= ~(0x3 << (1 * 2)); // Clear bits for PC1
    GPIOC->PUPDR |= (0x2 << (1 * 2));  // Set pull-down for PC1
    GPIOC->PUPDR &= ~(0x3 << (2 * 2)); // Clear bits for PC2
    GPIOC->PUPDR |= (0x2 << (2 * 2));  // Set pull-down for PC2

    Button_Mapping MAP[] =
        {
            {GPIOC, GPIOC_PIN_0, &toggle_slow},
            {GPIOC, GPIOC_PIN_1, &toggle_medium},
            {GPIOC, GPIOC_PIN_2, &toggle_fast}
        };

    while (1)
    {
        for (int j = 0; j < sizeof(MAP) / sizeof(MAP[0]); j++)
        {
            if ((MAP[j].PORT->IDR & MAP[j].PIN))
            {
                MAP[j].action();
                for (volatile int k = 0; k < 100000; k++);
            }
        }
    }
}

void toggle_slow(void)
{

    volatile long int i = 0;

    GPIOA->BSRR |= (0X0001);

    for (i = 0; i < 300000; i++)
        ;

    GPIOA->BSRR |= GPIO_BSRR_BR0;
    for (i = 0; i < 300000; i++)
        ;
}
void toggle_medium(void)
{

    volatile long int i = 0;

    GPIOA->BSRR |= GPIO_BSRR_BS1;

    for (i = 0; i < 200000; i++)
        ;

    GPIOA->BSRR |= GPIO_BSRR_BR1;
    for (i = 0; i < 200000; i++)
        ;
}
void toggle_fast(void)
{

    volatile long int i = 0;

    GPIOA->BSRR |= GPIO_BSRR_BS4;

    for (i = 0; i < 1500000; i++)
        ;

    GPIOA->BSRR |= GPIO_BSRR_BR4;
    for (i = 0; i < 1500000; i++)
        ;
}