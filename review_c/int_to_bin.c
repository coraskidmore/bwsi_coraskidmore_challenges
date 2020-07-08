#include <stdio.h>
#include <stdint.h>
#include "uart.h"

void intToBin (uint8_t target, char* buffer) {
    /* Your code goes here */
    int i;
    //"1101_0011{\0}"
    for (i=0;i<=7;i++){
        uint8_t temp;
        char write;
        temp = target >> (7-i);
        temp = temp & 0x1; //0000_0001b
        /////target == 0000_0011
        //           & 0000_0001
        //           = 0000_0001
        //  
        ////target == 1111_1110
        //          & 0000_0001
        //          = 0000_0000
        if (temp == 1){
            write = '1';
        } else {
            write = '0';
        }
        buffer[i] = write;
    }
    buffer[8]='\0'; //null terminal
} 

int main () {
    uart_init(UART2);
    uint8_t value;
    int ret;
    char binaryStr[9];

    // Begin main program loop
    while (value != 10) {
        value = uart_read(UART2, BLOCKING, &ret);
        intToBin(value, binaryStr);
        uart_write_str(UART2, binaryStr);
    }

    return 0;
}



//int value = 5;
// 
//int *val_ptr;
////justcreates a pointer (* tells it is a pointer/variable)
//val_ptr=5
////now val_ptr accesses at memory adress 5
//printf("%p",val_ptr'); - prints 5 (%p is for pointer)
//printf("%d",*val_ptr); - prints what ever is at memory adress 5

//val_ptr = &value;
////& gets the value of the memory adress of where it is stored
//printf("%p",val_ptr'); - prints the memory address
//printf("%d",*val_ptr); - prints the value of value (by accessing the memory adress in val_ptr)

//arrays
//char array[5] = {1,2,3,4,5};
////creates an array (size 5) that can be referenced to by array
////array is also just a pointer to the first value
//char *arr_ptr;
////just creats a pointer
//arr_ptr = array;
////arr_ptr points to the first value
//arr_ptr = &array;
////arr_ptr has address of the pointer to the array
