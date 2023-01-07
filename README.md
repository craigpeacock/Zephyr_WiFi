# Zephyr ESP32 WiFi Code

Simple example Zephyr WiFi code targeted for the [ESP32](https://docs.zephyrproject.org/latest/boards/xtensa/esp32/doc/index.html), although it should be platform-agnostic.

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

# Building

Follow the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to install Zephyr and the build tools. 

```
git clone https://github.com/craigpeacock/Zephyr_ESP32_WiFi.git
cd Zephyr_ESP32_WiFi
west blobs fetch hal_espressif
west build -b esp32
west flash
west espressif monitor
```

*West blobs fetch hal_espressif* downloads WiFi and Bluetooth binary blobs required for the ESP32. If these are not installed, you are likely to get linker errors resulting from missing files such as libnet80211.a
