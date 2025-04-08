idf_component_register(SRCS "my_spi_connect/spi_connect.cc"
                            "my_udp/my_udp.cc"
                            "common/wifi_board.cc"
                            "main.cc"
                        INCLUDE_DIRS "." "my_spi_connect" "my_udp" "common"
                        REQUIRES 
                            esp_event 
                            nvs_flash 
                            esp_netif
                            driver
                            )  
