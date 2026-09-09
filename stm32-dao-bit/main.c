#define RCC_APB2ENR (*(volatile unsigned int*)0x40021018)
#define GPIOA_CRL   (*(volatile unsigned int*)0x40010800)
#define GPIOA_CRH   (*(volatile unsigned int*)0x40010804)
#define GPIOA_IDR   (*(volatile unsigned int*)0x40010808)
#define GPIOA_ODR   (*(volatile unsigned int*)0x4001080C)

int main(void)
{
    RCC_APB2ENR |= (1 << 2);   // bat clock GPIOA

    // PA0-PA7: input floating (MODE=00, CNF=01 -> 0x4 moi chan)
    GPIOA_CRL = 0x44444444;

    // PA8-PA15: output push-pull 10MHz (MODE=01, CNF=00 -> 0x1 moi chan)
    GPIOA_CRH = 0x11111111;

    while (1) {
        unsigned int input_val = GPIOA_IDR & 0xFF;   // doc 8 bit thap (PA0-PA7)
        unsigned int inverted  = (~input_val) & 0xFF; // dao bit

        GPIOA_ODR = (inverted << 8);   // ghi vao PA8-PA15
    }
}
