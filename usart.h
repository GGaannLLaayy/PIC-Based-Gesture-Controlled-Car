/* 
 * File:   usart.h
 * Author: mahendra
 *
 * Created on July 22, 2018, 10:03 PM
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif
     void serial_init(void);
        void serial_println(const char *buffer);
        void serial_print(const char *buffer);
        void serial_write(char data);




#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

