
// Hardware Imports
#include "inc/hw_memmap.h" // Peripheral Base Addresses
#include "inc/lm3s6965.h" // Peripheral Bit Masks and Registers

// Component Header
#include "uart.h"

// UART Channels - You can use these names, but don't uncomment them!
// #define UART0 0
// #define UART1 1
// #define UART2 2

// Reading modes - You can use these names, but don't uncomment them!
// #define NONBLOCKING 0
// #define BLOCKING 1

void uart_init(uint8_t uart)
{
  // Implement me!!
    #define UART2 2
    UART2_CTL_R &= ~(UART_CTL_UARTEN); //disable uarten
    //turn it off (~ flips everything)
    //UART_IBRD_DIVINT_M = 0x0a;
    //UART_FBRD_DIVFRAC_M = 0x36;
    UART2_IBRD_R &= ~(UART_IBRD_DIVINT_M); //clears
    UART2_IBRD_R |= 0x0a;  //writes it int 
    UART2_FBRD_R &= ~(UART_FBRD_DIVFRAC_M);
    UART2_FBRD_R |= 0x36;
    UART2_LCRH_R &= ~(UART_LCRH_WLEN_M);
    UART2_LCRH_R |= UART_LCRH_WLEN_8;
    UART2_LCRH_R &= ~(UART_LCRH_PEN);
    UART2_CTL_R |= UART_CTL_UART;
}

uint8_t uart_read(uint8_t uart, int blocking, int *read)
{
  // Implement me!!
    if (blocking==1){ //if blocking
        while (UART_O_FR & UART_FR_RXFF);//wait for something to be recieved
        read=1;
        return (UART_O_DR &= UART_DR_DATA_M); //the data registar with the masking 
    } else{   // if not blocking
        if (UART_O_FR == (UART_O_FR |= UART_FR_TXFF)){
            //if the registar is equal to the registar containing the recieve full bit???
            read=1;
            return (UART_O_DR &= UART_DR_DATA_M);
        } else {
            read=0;
            return 0;
        }
    }
}

void uart_write(uint8_t uart, uint32_t data)
{
  // Implement me!!
    
}

void uart_write_str(uint8_t uart, char *str) {
  while (*str) { // Loop until null terminator
    uart_write(uart, (uint32_t)*str++);
  }
}

inline void nl(uint8_t uart) {
  uart_write(uart, '\n');
}

void uart_write_hex(uint8_t uart, uint32_t data) {
  uint32_t nibble;

  for (int shift = 28; shift >= 0; shift -=4) {
    nibble = (data >> shift) & 0xF;
    if (nibble > 9) {
      nibble += 0x37;
    } else {
      nibble += 0x30;
    }
    uart_write(uart, nibble);
  }
}


void UART0_IRQHandler(void)
{
}
    