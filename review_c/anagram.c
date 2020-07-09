#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "uart.h"

uint8_t isAnagram (char* str_a, char* str_b) {
    /* Your code goes here */
    int leta[26] = {0};
    int letb[26] = {0};
    int i;
    for (i=0;i<=strlen(str_a);i++){
        if (str_a[i]!=' '){
            leta[(str_a[i]-'a')]=leta[(str_a[i]-'a')]+1;
        }
    }
    int k;
    for (k=0; k<=strlen(str_b);k++){
        if (str_b[k]!=' '){
            letb[(str_b[k]-'a')]=letb[(str_b[k]-'a')]+1;
        }
    }    
    int l;
    for (l=0;l<26;l++){
        if (leta[l]!=letb[l]){
            return 0;
        }
    }
    return 1;
    
//     int i;
//     for (i=0;i<=strlen(str_a);i++){
//         if (str_a[i]==' '){
//             str_a[i]=0;
//         }
//     }
//     printf("%d",char*str_a);
//     int k;
//     for (k=0;k<=strlen(str_b);k++){
//         if (str_b[k]!=' '){
//             str_b[k]=0;
//         }
//     }
//     printf("%d",char*str_b);
//     char same=0;
//     int a;
//     for (a=0;a<=strlen(str_a);a++){
//         int b;
//         for (b=0;b<=strlen(str_b);b++){
//             if (str_a[a]==str_b[b]){
//                 str_a[a]=0;
//                 str_b[b]=0;
//                 same=1;
//                 break;
//             }
//         if (same==1){
//             same=0;
//             break;
//         }
//         }
//     }
//     int c;
//     char asum=0;
//     for (c=0;c<=strlen(str_a);c++){
//         asum=asum+str_a[c];
//     }
//     int d;
//     char bsum=0;
//     for (d=0;d<=strlen(str_b);d++){
//         bsum=bsum+str_b[d];
//     }
//     if(asum==0){
//         if (bsum==0){
//             return 1;
//         } 
//     }
    
//     return 0;
} 

int main () {
    uart_init(UART2);
    int ret;
    uint8_t numTests;
    char str_a[50];
    char str_b[50];
    uint8_t strPtr = 0;
    uint8_t testResult = 0;
    
    // Get ammount of tests
    numTests = uart_read(UART2, BLOCKING, &ret);

    // Begin main program loop
    for (int i = 0; i < numTests; i++) {
        char value = 0;
        uint8_t strPtr = 0;

        // Recieve first string
        while (value != 10) {
            value = uart_read(UART2, BLOCKING, &ret);
            str_a[strPtr++] = value;
        }
        str_a[(strPtr-1)] = '\0';  // Replaces newline with null terminator
        value = 0;
        strPtr = 0;

        // Recieve next string
        while (value != 10) {
            value = uart_read(UART2, BLOCKING, &ret);
            str_b[strPtr++] = value;
        }
        str_b[(strPtr-1)] = '\0';

        // Return result of test
        testResult = isAnagram(str_a, str_b);
        uart_write(UART2, (char) testResult);
    }

    return 0;
}
