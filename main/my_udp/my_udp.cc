#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "my_udp/my_udp.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

static const char *TAG = "UDP_client";
static int udp_socket=-1;
char host_ip[] = "192.168.000.000";


//NVS读取IP地址
static esp_err_t read_ip_from_nvs(size_t len) {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err == ESP_OK) {
        size_t ip_len = len;
        err = nvs_get_str(my_handle, "wifi_ip", host_ip, &ip_len);
        nvs_close(my_handle);
    }
    return err;
}


//UDP初始化
void udp_socket_init() {
    
    //这里修改默认的UDP目的地址,设置前保证nvs区域被清空
    if (read_ip_from_nvs(sizeof(host_ip)) != ESP_OK) {
        snprintf(host_ip, sizeof(host_ip), "192.168.18.136");
        //ESP_LOGE(TAG, "Failed to read IP from NVS, using default.");
    }
    
    // struct sockaddr_in dest_addr;
    // dest_addr.sin_addr.s_addr = inet_addr(host_ip);
    // dest_addr.sin_family = AF_INET;
    // dest_addr.sin_port = htons(PORT);

    int addr_family = AF_INET;
    int ip_protocol = IPPROTO_IP;

    udp_socket = socket(addr_family, SOCK_DGRAM, ip_protocol);
    if (udp_socket < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
    }
    //ESP_LOGE(TAG, "初始化成功");
}

//从用户缓冲区发送数据到UDP服务器，这里发送端口固定
void send2wifi(uint8_t *date, size_t length,int PORT) {

        // int addr_family = 0;
        // int ip_protocol = 0;
        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(host_ip);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(PORT);
        // addr_family = AF_INET;
        // ip_protocol = IPPROTO_UDP;
// #elif defined(CONFIG_EXAMPLE_IPV6)
//         struct sockaddr_in6 dest_addr = { 0 };
//         inet6_aton(HOST_IP_ADDR, &dest_addr.sin6_addr);
//         dest_addr.sin6_family = AF_INET6;
//         dest_addr.sin6_port = htons(PORT);
//         dest_addr.sin6_scope_id = esp_netif_get_netif_impl_index(EXAMPLE_INTERFACE);
//         addr_family = AF_INET6;
//         ip_protocol = IPPROTO_IPV6;


        // Set timeout to control the transmission speed of UDP 
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;
        setsockopt (udp_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);
    
        // UDP sending function
            int err = sendto(udp_socket, date, length, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
            if (err < 0) {
                ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        //ESP_LOGI(TAG, "Socket created, sending to %s:%d", host_ip, PORT);
}




//  void udp_receive_task(u_int8_t *revice_data,uart_port_t udp_uart_num)
// {       

//         //Determine if the socket exit,or
//         if (udp_socket < 0)
//         {
//             ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
//             return; 
//         }

//         while (1)
//         {
//             //struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
//             struct sockaddr_in source_addr;
//             socklen_t socklen = sizeof(source_addr);

//             memset(&source_addr, 0, sizeof(source_addr));
//             source_addr.sin_family = AF_INET;
//             source_addr.sin_port = htons(2000);  // 设置源端口
//             source_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 使用默认网卡
//             bind(udp_socket, (struct sockaddr *)&source_addr, sizeof(source_addr));

//             int revice_data_len = recvfrom(udp_socket, revice_data, 6144, 0, (struct sockaddr *)&source_addr, &socklen);
//             //printf("data_len: %d\n",revice_data_len);
            
//             // Error occurred during receiving
//             if (revice_data_len < 0)
//             {
//                 //  ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
                
//             }
//             // Data received
//             else
//             {
//                 // memcpy(revice_http, revice_data, len);
//                 // wifi2uart_len = len;
//                 //ESP_LOG_BUFFER_HEXDUMP("recv from udp:", wifi2uart, wifi2uart_len, ESP_LOG_INFO);

//                 uart_write_bytes(udp_uart_num, (const char *)revice_data, revice_data_len);
//                 // 调用 send2wifi 发送接收到的数据
//                 //send2wifi(revice_data, revice_data_len);
//                 // printf("Received data in hex: ");
//                 // for (int i = 0; i < revice_data_len; i++) {
//                 //              printf("%02X ", revice_data[i]);
//                 //     }
//                 // printf("data_len: %d\n",revice_data_len);
//             }
//             vTaskDelay(10/portTICK_PERIOD_MS);//1ms
//         }

//         //可选关闭端口号，并且删除任务
//         if (udp_socket != -1)
//         {
//             ESP_LOGE(TAG, "Shutting down socket and restarting..."); 
//             shutdown(udp_socket, 0);
//             close(udp_socket);
//         }
    
//     // vTaskDelete(NULL);
// }


