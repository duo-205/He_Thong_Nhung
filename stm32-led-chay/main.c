#define RCC_APB2ENR (*(volatile unsigned int*)0x40021018)
#define GPIOA_CRL   (*(volatile unsigned int*)0x40010800)
#define GPIOA_ODR   (*(volatile unsigned int*)0x4001080C)

static void delay(volatile unsigned int count)
{
    while (count--) {
        __asm__("nop");
    }
}

int main(void)
{
    RCC_APB2ENR |= (1 << 2);   // bat clock GPIOA

    // cau hinh PA0-PA7: output push-pull 10MHz (MODE=01, CNF=00 -> 0x1 moi chan)
    GPIOA_CRL = 0x11111111;

    int pos = 0;
    int direction = 1;   // 1 = chay sang phai, -1 = chay sang trai

    while (1) {
        GPIOA_ODR = (1 << pos);   // chi bat LED tai vi tri pos, cac chan con lai = 0
        delay(300000);

        pos += direction;

        if (pos == 7) {
            direction = -1;   // den bien phai, doi chieu sang trai
        } else if (pos == 0) {
            direction = 1;    // den bien trai, doi chieu sang phai
        }
    }
}
