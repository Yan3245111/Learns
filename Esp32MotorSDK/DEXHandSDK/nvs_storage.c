#include "nvs_storage.h"

#include <string.h>
#include <nvs_flash.h>
#include <nvs.h>



#define NVS_NAMESPACE "storage"

void nvs_storage_init(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

bool nvs_save_float(const char* key, float value) {
    nvs_handle_t handle;
    esp_err_t ret = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (ret != ESP_OK) {
        printf("Failed to open NVS: %s\n", esp_err_to_name(ret));
        return false;
    }

    // 将 float 转为 uint32_t 存储（NVS 不直接支持 float）
    uint32_t temp;
    memcpy(&temp, &value, sizeof(float));
    
    ret = nvs_set_u32(handle, key, temp);
    if (ret != ESP_OK) {
        printf("Failed to save float: %s\n", esp_err_to_name(ret));
        nvs_close(handle);
        return false;
    }

    ret = nvs_commit(handle);
    nvs_close(handle);
    
    if (ret != ESP_OK) {
        printf("Failed to commit: %s\n", esp_err_to_name(ret));
        return false;
    }
    
    printf("Saved float: %.2f\n", value);
    return true;
}

float nvs_load_float(const char* key, float default_val) {
    nvs_handle_t handle;
    esp_err_t ret = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    if (ret != ESP_OK) {
        printf("Failed to open NVS: %s\n", esp_err_to_name(ret));
        return default_val;
    }

    uint32_t temp;
    ret = nvs_get_u32(handle, key, &temp);
    nvs_close(handle);
    
    if (ret == ESP_ERR_NVS_NOT_FOUND) {
        printf("Key '%s' not found, using default: %.2f\n", key, default_val);
        return default_val;
    } else if (ret != ESP_OK) {
        printf("Failed to load float: %s\n", esp_err_to_name(ret));
        return default_val;
    }
    
    float value;
    memcpy(&value, &temp, sizeof(float));
    printf("Loaded float: %.2f\n", value);
    return value;
}

// ========== 便捷函数：角度存储 ==========

void nvs_save_angle(float angle) {
    nvs_save_float("angle", angle);
}

float nvs_load_angle(void) {
    return nvs_load_float("angle", 0.0f);
}
