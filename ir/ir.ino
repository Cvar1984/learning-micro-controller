/**
 * Copyright (c) 2020 Ramdhan Firmansyah
 * File              : ir.ino
 * Author            : Cvar1984 <gedzsarjuncomuniti@gmail.com>
 * Date              : 08.10.2020
 * Last Modified Date: 08.10.2020
 * Last Modified By  : Cvar1984 <gedzsarjuncomuniti@gmail.com>
 */
#include <IRremote.h>

// #define IR_TX_PIN 11
#define IR_RX_PIN 12
#define LED_RED 2 // u can use this pin for any of modules that require digital signal eg: relay, and buzzer 

IRrecv irrecv(IR_RX_PIN);
decode_results results;

void setup() {
    pinMode(LED_RED, OUTPUT);
    pinMode(IR_RX_PIN, INPUT);
    Serial.begin(115200);
    irrecv.enableIRIn();
    irrecv.blink13(true);
}

bool isOn = false;
void handleSignal(unsigned long hex)
{
    switch (hex) {
        case 0x29283C1B: // sony camera shutter ( tested using mi remote on my Redmi5A )
            if (isOn) {
                // turn of
                digitalWrite(LED_RED, LOW);
                isOn = false;
            }
            else {
                // turn on
                digitalWrite(LED_RED, HIGH);
                isOn = true;
            }
            break;
        default:
            Serial.println(results.value, HEX); // if nothing works you can see what is going on :)
            break;
    }
    delay(100); // delay 100ms to avoid receive multiple hex code ( cause LED_BUILTIN blink instead of turn on until u pres it again )
}

void loop() {
    if (irrecv.decode(&results)) {
        handleSignal(results.value);
        irrecv.resume();
    }
}
