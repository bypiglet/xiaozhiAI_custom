#include <stdio.h>
#include "bp_spi_driver.h"
#include "my_udp/my_udp.h"
#include "common/wifi_board.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#ifdef __cplusplus
extern "C" {
#endif

void app_main(void);  // 声明 app_main 函数

#ifdef __cplusplus
}
#endif


uint8_t txData = 0x51;  // 要发送的数据
uint8_t rxData = 0x00;  // 用来接收的数据

// 使用你已经定义好的 SPI_Master_Receive 函数
void SPI_Master_Receive_And_Respond()
{
   

    // 调用 SPI_Master_Receive 函数 
    SPI_Master_Receive(&txData, &rxData, 1);
    // 打印发送的数据
    //ESP_LOGI("SPI", "Send data: 0x%02X", txData);
}



void app_main(void)
{   
    //uint8_t tx_data[]={0xAA,0xBB,0xCC};
    //uint8_t rx_data[3];
    wifi_connect();
    udp_socket_init();
    SPI_Master_Init();
    //SPI_Master_Receive(tx_data,rx_data,sizeof(tx_data));
    printf("hello world! \n");
    printf("nothiing to see here \n");
    printf("这是一个spi的实现 \n");    
    

    while (1)
    {
        SPI_Master_Receive_And_Respond();
        vTaskDelay(10 / portTICK_PERIOD_MS);  // 延时 1 秒
    }
    
}
