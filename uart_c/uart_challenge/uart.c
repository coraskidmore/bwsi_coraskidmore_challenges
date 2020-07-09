
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
//     switch (uart){
//         case UART0:
//             break;
//         case UART1:
//             break;
//         case UART2:
//             break;
//         default:
//             break;
//     }
    
    
    #define UART2 2
    UART2_CTL_R &= ~(UART_CTL_UARTEN); //disable uart
    //turn it off (~ flips everything)
    //UART_IBRD_DIVINT_M = 0x0a;
    //UART_FBRD_DIVFRAC_M = 0x36;
    UART2_IBRD_R &= ~(UART_IBRD_DIVINT_M); //clears the section of the IBRD registar for int component
    UART2_IBRD_R |= 0x0a;  //writes the int component into the IBRD registar
    UART2_FBRD_R &= ~(UART_FBRD_DIVFRAC_M); //clears the section of the FBRD registar for fractal component
    UART2_FBRD_R |= 0x36; //writes the fractal component into the FBRD registar
    UART2_LCRH_R &= ~(UART_LCRH_WLEN_M); //clears the word length parameter in LCRH registar (sets to 0)
    UART2_LCRH_R |= UART_LCRH_WLEN_8; //sets word length to 8 bits
    UART2_LCRH_R &= ~(UART_LCRH_PEN); //not nessesary but zeros the parity (disables it)
    UART2_CTL_R |= UART_CTL_UARTEN; //enables uart
}

uint8_t uart_read(uint8_t uart, int blocking, int *read)
{
  // Implement me!!
    if (blocking){ //if blocking
        while ((UART2_FR_R  & UART_FR_RXFE));//wait for the recieve FIFO to be empty
        *read=1; //set read to 1
        return (UART2_DR_R & UART_DR_DATA_M); //return the data (masking the rest of the code)
    } else{   // if not blocking
        if (UART2_FR_R & UART_FR_RXFF){ //if the registar is equal to the registar containing the recieve full bit???
            //UART2_FR_R  == (UART2_FR_R | UART_FR_RXFF) - my original for the if
            *read=1; //set read to 1
            return (UART2_DR_R & UART_DR_DATA_M); //return the data (masking the rest of the code)
        } else {  //if their is no data to read
            *read=0; //set read to 0
            return 0; //return 0
        }
    }
}

void uart_write(uint8_t uart, uint32_t data)
{
  // Implement me!!
    while((UART2_FR_R & UART_FR_BUSY)); //wait until the transmission is not busy
    //UART2_DR_R &= ~(UART_DR_DATA_M); //clear the part of the data registar that holds the data
    //you cant do this bc this is sending 0x00 to the transmit registar, then data which results in (0x00,data) in each bit 
    //UART2_DR_R = data; //puts the data in the data registar
    UART2_DR_R = (UART2_DR_R & ~(UART_DR_DATA_M)) | (data & UART_DR_DATA_M); //simulaniously clear the data registar and put in the new data
}

void uart_write_str(uint8_t uart, char *str) {
  while (*str) { // Loop until null terminator (while will go until it hits a null terminator)
    uart_write(uart, (uint32_t)*str++); //writes a bit of the string, then increases the mem adress for the next loop.
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
    