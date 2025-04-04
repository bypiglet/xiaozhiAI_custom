#include <stdio.h>
#include "my_spi_connect/spi_connect.h"

#ifdef __cplusplus
extern "C" {
#endif

void app_main(void);  // 声明 app_main 函数

#ifdef __cplusplus
}
#endif


void app_main(void)
{   
    uint8_t tx_data[]={0xAA,0xBB,0xCC};
    uint8_t rx_data[3];
    SPI_Master_Init();
    SPI_Master_Receive(tx_data,rx_data,sizeof(tx_data));

    for (int i = 0; i < 3; i++) {
        printf("Received data[%d]: 0x%02X\n", i, rx_data[i]);
    }

    printf("hello world! \n");
    printf("nothiing to see here \n");
    printf("这是一个spi的实现 \n");    
}
