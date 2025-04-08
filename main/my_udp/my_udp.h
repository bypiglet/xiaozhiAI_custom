#ifndef MY_UDP_H
#define MY_UDP_H

#include "driver/gpio.h"
//V1版本烧录前需要 “erase flash”，在进行烧录。因为nvs中保持有UDP的目的IP地址,清除后使用的就是默认IP地址。


//UDP初始化，选择ipv4，UDP协议
void udp_socket_init() ;

//从用户缓冲区发送数据到UDP服务器，这里发送端口固定
void send2wifi(uint8_t *date, size_t length,int PORT);

//UDP接受函数，参数：端口，接受数据，串口号
// void udp_receive_task(void *revice_data,uart_port_t uart_num);

#endif // MY_UART_H