# Zephyr WiFi Code

Simple example Zephyr WiFi code is targeted for the [ESP32](https://docs.zephyrproject.org/latest/boards/xtensa/esp32/doc/index.html) and [ESP32C3](https://docs.zephyrproject.org/3.1.0/boards/riscv/esp32c3_devkitm/doc/index.html), although it should be platform-agnostic.

Connects to a WiFi network, obtains an IPv4 address via DHCP and disconnects after 30 seconds.

```
*** Booting Zephyr OS build zephyr-v3.2.0-2019-g7ac69dc4ca95 ***
Connecting to SSID: Welcome_IN
Connected
IPv4 address: 192.168.0.67
Subnet: 255.255.255.0
Router: 192.168.0.254
Disconnected
```

# Building for ESP32 (xtensa)

Follow the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to install Zephyr and the build tools. 

```
git clone https://github.com/craigpeacock/Zephyr_ESP32_WiFi.git
cd Zephyr_ESP32_WiFi
west blobs fetch hal_espressif
west build -b esp32
west flash
west espressif monitor
```

# Building for ESP32C3 (RISC-V)

Follow the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to install Zephyr and the build tools. 

```
git clone https://github.com/craigpeacock/Zephyr_ESP32_WiFi.git
cd Zephyr_ESP32_WiFi
west blobs fetch hal_espressif
west build -b esp32c3_devkitm
west flash
west espressif monitor
```

# Troubleshooting

*West blobs fetch hal_espressif* downloads WiFi and Bluetooth binary blobs required for the ESP32. If these are not installed, you are likely to get linker errors resulting from missing files such as

```
cannot find -lnet80211: No such file or directory
cannot find -lcore: No such file or directory
cannot find -lpp: No such file or directory
cannot find -lcoexist: No such file or directory
cannot find -lphy: No such file or directory
cannot find -lmesh: No such file or directory
```

The RISC-V architecture (ESP32C3) requires the kconfig option CONFIG_HEAP_MEM_POOL_SIZE=32768 otherwise multiple errors result with undefined reference to `k_malloc'

If this value is too small, errors can result loading the WiFi driver at runtime:

```
[00:00:00.003,000] <err> esp32_wifi_adapter: memory allocation failed          
[00:00:00.005,000] <err> esp32_wifi: Failed to start Wi-Fi driver  
```

# nrf7002dk_nrf5340_cpuapp (Nordic nRF7002)

Project currently builds and sucessfully connects when using nRFConnect SDK 2.2.0. 

It is noted when using SDK 2.3.0, the following error (Unable to get wpa_s handle for wlan0) is reported at runtime:

```
WiFi Example
Board: nrf7002dk_nrf5340_cpuapp
Connecting to SSID: test_ap
[00:00:00.600,189] <inf> wpa_supp: z_wpas_start: 385 Starting wpa_supplicant thread with debug level: 3
[00:00:00.600,402] <inf> wpa_supp: Successfully initialized wpa_supplicant
[00:00:00.600,830] <err> wpa_supp: z_wpas_get_handle_by_ifname: Unable to get wpa_s handle for wlan0
```




