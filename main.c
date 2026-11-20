#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#define SYS_CLK 25000000

#define __IM volatile const /*! Defines 'read only' structure member permissions */
#define __OM volatile       /*! Defines 'write only' structure member permissions */
#define __IOM volatile      /*! Defines 'read / write' structure member permissions */

typedef struct
{
    __IOM uint32_t CTRL; /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    __IOM uint32_t LOAD; /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    __IOM uint32_t VAL;  /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    __IM uint32_t CALIB; /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;
#define SCS_BASE (0xE000E000UL)                /*!< System Control Space Base Address */
#define SysTick_BASE (SCS_BASE + 0x0010UL)     /*!< SysTick Base Address */
#define SysTick ((SysTick_Type *)SysTick_BASE) /*!< SysTick configuration struct */

#define __disable_irq() __asm volatile("cpsid i" : : : "memory")
#define __enable_irq() __asm volatile("cpsie i" : : : "memory")

static int a = 128;

int add(int a, int b)
{
    return a + b;
}

volatile uint32_t systick_cnt = 0;

int main(void)
{
    uint32_t my_timer = 0;

    assert(add(1, 2) == 3);
    assert(a == 128);
    printf("hello\n");

    __disable_irq();
    SysTick->LOAD = SYS_CLK / 1000 - 1;
    SysTick->VAL = 0UL;
    SysTick->CTRL = (1u << 2) | (1u << 1) | (1u << 0);
    __enable_irq();

    for (;;)
    {
        if ((systick_cnt - my_timer) >= 500)
        {
            my_timer = systick_cnt;
            printf("%lu\n", systick_cnt);
        }
    }
    return 0;
}

void SysTick_Handler(void)
{
    systick_cnt += 1u;
}
