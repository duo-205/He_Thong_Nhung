#define RCC_APB2ENR (*(volatile unsigned int*)0x40021018)
#define GPIOA_CRL   (*(volatile unsigned int*)0x40010800)
#define GPIOA_IDR   (*(volatile unsigned int*)0x40010808)
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

    // PA0: input pull-up (MODE=00, CNF=10 -> 0x8)
    // PA1: output push-pull 10MHz (MODE=01, CNF=00 -> 0x1), dich sang vi tri chan PA1
    GPIOA_CRL = 0x00000018;   // 0x8 (PA0) | 0x1<<4 (PA1)

    GPIOA_ODR |= (1 << 0);    // set ODR=1 cho PA0 de kich hoat che do pull-UP

    int prev_state = 1;   // trang thai nut truoc do (1 = chua nhan, mac dinh nha)

    while (1) {
        int cur_state = (GPIOA_IDR >> 0) & 1;   // doc trang thai PA0

        // phat hien canh: truoc do dang nhan (0), bay gio da nha (1) -> vua nha nut
        if (prev_state == 0 && cur_state == 1) {
            GPIOA_ODR ^= (1 << 1);   // dao trang thai LED tai PA1
        }

        prev_state = cur_state;

        delay(30000);   // delay nho de chong doi (debounce) tin hieu rung phim
    }
}
