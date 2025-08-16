# Zephyr WiFi Code

Simple example Zephyr WiFi code that is targeted for the [ESP32-S3](https://www.espressif.com/en/products/socs/esp32-s3), [ESP32-C3](https://www.espressif.com/en/products/socs/esp32-c3), Raspberry [Pico W](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html) (Infineon [CYW43439](https://www.infineon.com/part/CYW43439)) and Nordic [nRF7002](https://www.nordicsemi.com/Products/Wireless/WiFi/Products?lang=en#infotabs), although it should be platform-agnostic (one of the advantages of Zephyr).

This example connects to a WiFi network, obtains an IPv4 address via DHCP, pings Goggle's DNS server 8.8.8.8 four times, does a DNS lookup for iot.beyondlogic.org returning IPv4 and IPv6 addresses and finally performs a http GET request for http://iot.beyondlogic.org/LoremIpsum.txt

```
*** Booting Zephyr OS build v4.2.0-1744-g1cb0b6a7ffa5 ***
WiFi Example
Board: esp32s3_devkitc
Connecting to SSID: test_ap
Connected
SSID: test_ap
Band: 2.4GHz
Channel: 9
Security: WPA2-PSK
RSSI: -68
IPv4 address: 192.168.0.152
Subnet: 255.255.255.0
Router: 192.168.0.254
Ready...
Reply from 8.8.8.8: bytes=28 time=25ms TTL=116
Reply from 8.8.8.8: bytes=28 time=21ms TTL=116
Reply from 8.8.8.8: bytes=28 time=18ms TTL=116
Reply from 8.8.8.8: bytes=28 time=16ms TTL=116

Looking up IP addresses:
IPv4: 66.39.146.38
IPv6: 2607:f440::4227:9226
Connecting to HTTP Server:
Connecting to 2607:f440::4227:9226:80 Failure (-1)
Connecting to 66.39.146.38:80 Success
HTTP/1.1 200 OK
Date: Sat, 16 Aug 2025 11:19:55 GMT
Server: Apache
Last-Modified: Thu, 27 Jun 2024 11:26:53 GMT
ETag: "f6f-61bdd685e5940"
Accept-Ranges: bytes
Content-Length: 3951
Content-Type: text/plain

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec vel dolor auctor, bibendum lectus sit amet, bibendum velit. Nunc euismod, odio eget eleifend aliquet, nibh nibh malesuada risus, vel pretium nunc eros at elit. Donec finibus ultrices quam a luctus. Curabitur lobortis massa id sapien aliquam, id congue mi lobortis. Fusce id aliquam ante. Nullam congue velit ac bibendum eleifend. Nulla quis gravida odio, vel rutrum risus. Ut tincidunt, justo in fermentum bibendum, mauris mauris malesuada metus, ut eleifend augue lectus ut ex. Nam ut mollis ante.
```

# Building for ESP32-S3 (xtensa)

Follow the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to install Zephyr and the build tools. 

Zephyr Board Information: [ESP32-S3-DevKitC](https://docs.zephyrproject.org/latest/boards/espressif/esp32s3_devkitc/doc/index.html)

```
git clone https://github.com/craigpeacock/Zephyr_ESP32_WiFi.git
cd Zephyr_ESP32_WiFi
west blobs fetch hal_espressif
west build -b esp32s3_devkitc/esp32s3/procpu
west flash
west espressif monitor
```

# Building for ESP32-C3 (RISC-V)

Follow the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to install Zephyr and the build tools. 

Zephyr Board Information: [ESP32-C3-DevKitC](https://docs.zephyrproject.org/latest/boards/espressif/esp32c3_devkitc/doc/index.html)

```
git clone https://github.com/craigpeacock/Zephyr_ESP32_WiFi.git
cd Zephyr_ESP32_WiFi
west blobs fetch hal_espressif
west build -b esp32c3_devkitc/esp32c3
west flash
west espressif monitor
```

# Building for ESP32-C6 (RISC-V)

Follow the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to install Zephyr and the build tools. 

Zephyr Board Information: [ESP32-C6-DevKitC](https://docs.zephyrproject.org/latest/boards/espressif/esp32c6_devkitc/doc/index.html)

```
git clone https://github.com/craigpeacock/Zephyr_ESP32_WiFi.git
cd Zephyr_ESP32_WiFi
west blobs fetch hal_espressif
west build -b esp32c6_devkitc/esp32c6/hpcore
west flash
west espressif monitor
```

# Building for Raspberry PicoW

Follow the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) to install Zephyr and the build tools.

Zephyr Board Information: [Raspberry Pi Pico](https://docs.zephyrproject.org/latest/boards/raspberrypi/rpi_pico/doc/index.html)

```
git clone https://github.com/craigpeacock/Zephyr_ESP32_WiFi.git
cd Zephyr_ESP32_WiFi
west blobs fetch hal_infineon
west build -b rpi_pico/rp2040/w
west flash
```

The console is available on P0/P1. UART0_TX is P0, UART0_RX is P1.

Console Output:
```
WLAN Firmware    : wl0: Jun  5 2024 06:33:59 version 7.95.88 (cf1d613 CY) FWID 01-7b7cf51a
WLAN CLM         : API: 12.2 Data: 9.10.39 Compiler: 1.29.4 ClmImport: 1.36.3 Creation: 2024-04-16 21:20:55
WHD VERSION      : 3.3.2.25168 : v3.3.2 : GCC 12.2 : 2024-12-06 06:53:17 +0000
*** Booting Zephyr OS build v4.2.0-1744-g1cb0b6a7ffa5 ***
WiFi Example
Board: rpi_pico
Connecting to SSID: test_ap
Connected
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

This project currently builds and sucessfully connects when using nRFConnect SDK 2.2.0 and 2.3.0. Support for the nRF7002 is very new and change should be expected as the code matures over time. Below is a list of common issues encounted when porting your Zephyr WiFi code to the nRF7002 target:

## Troubleshooting 

It may be observed when using SDK 2.3.0 that the following error (Unable to get wpa_s handle for wlan0) is reported at runtime:

```
WiFi Example
Board: nrf7002dk_nrf5340_cpuapp
Connecting to SSID: test_ap
[00:00:00.600,189] <inf> wpa_supp: z_wpas_start: 385 Starting wpa_supplicant thread with debug level: 3
[00:00:00.600,402] <inf> wpa_supp: Successfully initialized wpa_supplicant
[00:00:00.600,830] <err> wpa_supp: z_wpas_get_handle_by_ifname: Unable to get wpa_s handle for wlan0
```

Examining nRF7002 code from Nordic, it appears they have put a 1 second day in after registering the callbacks, and before calling wifi_connect(). This was not required in SDK 2.2.0

To prevent the following build error
```
\wifi\nrf700x\zephyr\src\shim.c:14:10: fatal error: sys/time.h: No such file or directory
```
add the following to your prj.conf:
```
CONFIG_NEWLIB_LIBC=y
CONFIG_NEWLIB_LIBC_NANO=n
```

To prevent build error
```
undefined reference to `z_impl_sys_rand32_get'
```
and the following to your prj.conf:
```
CONFIG_ENTROPY_GENERATOR=y
CONFIG_TEST_RANDOM_GENERATOR=y
```










