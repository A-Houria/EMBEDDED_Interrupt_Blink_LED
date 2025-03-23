#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// BASE ADDRESSES
//PMM
#define PMM_BASE                0x0120 // PMM base address
#define PM5CTL0                 (*(volatile uint8_t *)(PMM_BASE + 0x10)) // PM5CTL0 Register from PMM with offset 0x10
//Ports Base Addresses
#define P1_2_BASE               0x0200 // Port p1, p2 and  base address
#define P4_BASE                 0x0220 // Port p4 base address
#define P6_BASE                 0x0240 // Port p6 base address
#define P4_INTERRUPT_BASE       0xFFCE // Port p4 interrupt base address
// PORT1
#define P1_OUT                  (*(volatile uint8_t *)(P1_2_BASE + 0x02))
#define P1_DIR                  (*(volatile uint8_t *)(P1_2_BASE + 0x04))
// PORT2
#define P2_OUT                   (*(volatile uint8_t *)(P1_2_BASE + 0x02))
#define P2_DIR                  (*(volatile uint8_t *)(P1_2_BASE + 0x05))
#define P2_PEN                  (*(volatile uint8_t *)(P1_2_BASE + 0x07))
#define P2_IE                   (*(volatile uint8_t *)(P1_2_BASE + 0x1B))
#define P2_IES                  (*(volatile uint8_t *)(P1_2_BASE + 0x19))
#define P2_IFG                  (*(volatile uint8_t *)(P1_2_BASE + 0x1D))
// PORT4
#define P4_OUT                   (*(volatile uint8_t *)(P4_BASE + 0x02))
#define P4_DIR                  (*(volatile uint8_t *)(P4_BASE + 0x05))
#define P4_PEN                  (*(volatile uint8_t *)(P4_BASE + 0x07))
#define P4_IE                   (*(volatile uint8_t *)(P4_BASE + 0x1B))
#define P4_IES                  (*(volatile uint8_t *)(P4_BASE + 0x19))
#define P4_IFG                  (*(volatile uint8_t *)(P4_BASE + 0x1D))
// PORT6
#define P6_OUT                  (*(volatile uint8_t *)(P6_BASE + 0x03))
#define P6_DIR                  (*(volatile uint8_t *)(P6_BASE + 0x05))

void main(void)
{
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // CLEAR LOCKLPM5
    PM5CTL0 &= ~(1 << 0);

    //PORT 2 Config
    P2_DIR &= ~(1 << 3);
    P2_OUT |= (1 << 3);
    P2_PEN |= (1 << 3);
    P2_IE  |= (1 << 3);
    P2_IES |= (1 << 3);
    P2_IFG &= ~(1 << 3);
    //PORT 4 Config
    P4_DIR &= ~(1 << 1);
    P4_OUT |= (1 << 1);
    P4_PEN |= (1 << 1);
    P4_IE  |= (1 << 1);
    P4_IES |= (1 << 1);
    P4_IFG &= ~(1 << 1);
    //PORT 6 Config
    P6_DIR |= (1 << 6);
    P6_OUT &= ~(1 << 6);
    //PORT 1 Config
    P1_DIR |= (1 << 0);
    P1_OUT &= ~(1 << 0);

    __enable_interrupt();   // Enables Maskable Interrupts

    while(1) {}
}
//----------------- ISRs ------------------------------//
#pragma vector = PORT2_VECTOR
__interrupt void P2_B3_ISR(void){
    P6_OUT ^= (1 << 6);
    P2_IFG &= ~(1 << 3);
}

#pragma vector = PORT4_VECTOR
__interrupt void P4_B1_ISR(void){
    P1_OUT ^= (1 << 0);
    P4_IFG &= ~(1 << 1);
}
