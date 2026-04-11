# TBTracker-ESP32 Burst Controller
Remote controller to send a burst command to TBTracker.
Build for use with a Heltec V3 433MHz.

This sends a LoRa command to initialize the "Burst" command on TBTracker-ESP32.
This feature is implemented in my fork of the original TBTracker.

<img width="529" height="199" alt="Screenshot_20260405-143344" src="https://github.com/user-attachments/assets/bcb8dd52-fa95-4639-bdbc-1fcd2d8ab4e5" />

Simply upload the code in Arduino IDE to the Heltec V3 and when running press the "PRG" button on the board to send the burst command.

Make sure you have Arduno IDE enabled to program ESP32's and chose board "Heltec Wireless LoRa (V3)"
