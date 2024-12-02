/*
 * uart.h
 *
 * Created: 2024-12-02 오후 3:47:33
 *  Author: tshoon
 */ 


#ifndef UART_H_
#define UART_H_

void uart_init(void);
int8_t uart_getch(void);
void uart_putch(int8_t ch);
void uart_puts(int8_t* str);
void num2ascii(int8_t ch);


#endif /* UART_H_ */