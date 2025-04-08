#include "wifi_board.h"


#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"
#include <wifi_station.h>
#include <wifi_configuration_ap.h>
#include <ssid_manager.h>

static const char *TAG = "WiFi_Connect";

// WiFi连接函数
void wifi_connect()
{
    // Initialize the default event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize NVS flash for WiFi configuration
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Get the WiFi configuration
    auto& ssid_list = SsidManager::GetInstance().GetSsidList();
    if (ssid_list.empty()) {
        // Start the WiFi configuration AP
        ESP_LOGI(TAG, "No WiFi SSID found, starting AP for configuration.");
        auto& ap = WifiConfigurationAp::GetInstance();
        ap.SetSsidPrefix("ESP32");
        ap.Start();
        return;
    }

    // Otherwise, connect to the WiFi network
    ESP_LOGI(TAG, "Connecting to WiFi network.");
    WifiStation::GetInstance().Start();
}
