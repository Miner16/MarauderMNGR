# MarauderMNGR

MarauderMNGR is a console / UI for the WiFi marauder, it allows you to use Marauder without a Flipper Zero or screen. It connects to your phone using its own WiFi.
This has a couple of benefits over using a TFT display or a Flipper Zero, It's less suspicious in a public space, less bulky, easier to use, and way faster to type on compared to a Flipper.

The UI consist of a text box which displays all incoming serial data (up to 30 lines then the old ones get cut off), a text box to input commands, and below that are quick action buttons for prewritten commands.


### Needed stuff:
- [ESP32 X2](https://a.aliexpress.com/_EGdUiGh)
- 4 JUMPER WIRES
- EXTERNAL ANTENNAS (IF SUPPORTED)
- COMPUTER TO FLASH THE ESP'S

To get from a pile of stuff to a working product, do this:

1. Find a suitable cable for your ESP to connect to your PC, some cables don't transfer data so you may need to try a couple.
2. Connect the ESP to your PC (don't use a USB hub)
3. Check the USB controller on your ESP (little black square or rectangle with lots of pins)
4. Install the suitable driver according to the model: [CP2102](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) or [CH340/CH341](https://www.wch.cn/downloads/CH343SER_ZIP.html)
5. The ESP should now get recognized as some kind of 'USB to UART' bridge in Device Manager under 'Ports (COM & LPT)'.
6. Open https://fzeeflasher.com/
7. Start holding down the BOOT or B button on your ESP
8. Click CONNECT and select your ESP. (while still holding down the BOOT button)
9. Now select ESP32-WROOM in 'Select Model'
10. Select LATEST and MARAUDER
11. Now press PROGRAM
12. Wait for the flashing process finish and now you can disconnect the ESP. I suggest marking the ESP with a pen so you know where Marauder is flashed.
13. 


### Connect them like this:
- 5V-5V
- GND-GND
- RX-TX
- TX-RX

![image](https://github.com/user-attachments/assets/6c680426-2d76-4f4f-8eb0-b432d7d37618)
