#define RCC_APB2ENR (*(volatile unsigned int*)0x40021018)
#define GPIOC_CRH   (*(volatile unsigned int*)0x40011004)
#define GPIOC_ODR   (*(volatile unsigned int*)0x4001100C)

static void delay(volatile unsigned int count)
{
    while (count--) {
        __asm__("nop");
    }
}

int main(void)
{
    RCC_APB2ENR |= (1 << 4);        // bat clock GPIOC

    GPIOC_CRH &= ~(0xF << 20);      // xoa cau hinh chan PC13
    GPIOC_CRH |=  (0x1 << 20);      // output push-pull 10MHz

    while (1) {
        GPIOC_ODR ^= (1 << 13);     // dao trang thai chan PC13
        delay(1000000);
    }
}
