#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;

extern void _start(void);

void Reset_Handler(void);
void Default_Handler(void);

void NMI_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)__attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)   __attribute__((weak, alias("Default_Handler")));

__attribute__((section(".isr_vector"), used))
const uintptr_t vector_table[] = {
    (uintptr_t)&_estack,
    (uintptr_t)Reset_Handler,
    (uintptr_t)NMI_Handler,
    (uintptr_t)HardFault_Handler,
    (uintptr_t)MemManage_Handler,
    (uintptr_t)BusFault_Handler,
    (uintptr_t)UsageFault_Handler,
    (uintptr_t)0,
    (uintptr_t)0,
    (uintptr_t)0,
    (uintptr_t)0,
    (uintptr_t)SVC_Handler,
    (uintptr_t)DebugMon_Handler,
    (uintptr_t)0,
    (uintptr_t)PendSV_Handler,
    (uintptr_t)SysTick_Handler,
};

void Reset_Handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    /* 1. Copy initialized global/static data (.data) from Flash to RAM.
     *    _sidata: load address of .data in Flash
     *    _sdata : start address of .data in RAM
     *    _edata : end address of .data in RAM
     */
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* 2. Delegate the remaining startup sequence to _start:
     *    - zero the .bss section
     *    - call initialise_monitor_handles()
     *    - invoke main()
     */
    _start();

    /* Should never be reached */
    for (;;) {
    }
}

void Default_Handler(void)
{
    for (;;) {
    }
}
