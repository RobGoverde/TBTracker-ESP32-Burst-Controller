/*
Remote bust controller for TBTracker-ESP32 by Roel Kroes.
Burst controller by Rob Goverde.

This example is build for a Heltec V3 433MHz.
It sends a LoRa command to to TBTracker-ESP32 firmware that, when enabled, sets a pin high for remote burst.

>>Still very much experimental!<<

Build upon the RadioLib SX126x Transmit with Interrupts Example by J Gromes.
https://jgromes.github.io/RadioLib/
*/

const int buttonPin = 0; //PRM button on the Heltec V3, pushing gives the burst command.

// include the library
#include <RadioLib.h>

// Heltec V3 has the following connections:
// NSS pin:   8
// DIO1 pin:  14
// NRST pin:  12
// BUSY pin:  13
SX1262 radio = new Module(8, 14, 12, 13);


// save transmission state between loops
int transmissionState = RADIOLIB_ERR_NONE;

// flag to indicate that a packet was sent
volatile bool transmittedFlag = false;

// this function is called when a complete packet
// is transmitted by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif
void setFlag(void) {
  // we sent a packet, set the flag
  transmittedFlag = true;
}

void setup() {
  pinMode(buttonPin, INPUT);
  displaysetup();
  displayloop();
  Serial.begin(9600);

  // initialize SX1262 with default settings
  Serial.print(F("[SX1262] Initializing ... "));
  int state = radio.begin(432.662, 62.5,8,8);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }

  // set the function that will be called
  // when packet transmission is finished
  radio.setPacketSentAction(setFlag);

  // start transmitting the first packet
  Serial.print(F("[SX1262] Sending first packet ... "));

}

// counter to keep track of transmitted packets
int count = 0;

void loop() {
  // check if the previous transmission finished
  if(digitalRead(buttonPin) == LOW) {
    Serial.println("Press.");
    send();

}
}

void send(){
  transmissionState = radio.startTransmit("0BURST0"); //this is the magic word.
 if(transmittedFlag) {
    // reset flag
    transmittedFlag = false;

    if (transmissionState == RADIOLIB_ERR_NONE) {
      // packet was successfully sent
      Serial.println(F("transmission finished!"));

      // NOTE: when using interrupt-driven transmit method,
      //       it is not possible to automatically measure
      //       transmission data rate using getDataRate()
burst();
    } else {
      Serial.print(F("failed, code "));
      Serial.println(transmissionState);

    }

    // clean up after transmission is finished
    // this will ensure transmitter is disabled,
    // RF switch is powered down etc.
    radio.finishTransmit();
delay(500);
  }
}

