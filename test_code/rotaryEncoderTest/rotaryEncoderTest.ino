// // Rotary Encoder Module connections
// const int ROTARY_ENCODER_A_PIN = 22; // PinCLK
// const int ROTARY_ENCODER_B_PIN = 21; // PinDT
// const int ROTARY_ENCODER_BUTTON_PIN = 15; // PinSW

// volatile int encoderValue = 0;
// int lastReportedValue = 1;
// static int lastEncoderValue = 0;

// // Variables to debounce Rotary Encoder
// long TimeOfLastDebounce = 0;
// const int DelayofDebounce = 2; // Reduced debounce delay in milliseconds

// // Store previous Pins state
// int PreviousCLK;   
// int PreviousDT;

// void IRAM_ATTR handleEncoderChange() {
//   int currentCLK = digitalRead(ROTARY_ENCODER_A_PIN);
//   int currentDT = digitalRead(ROTARY_ENCODER_B_PIN);

//   if (PreviousCLK == 0 && currentCLK == 1) {
//     if (currentDT == 0) {
//       encoderValue++;  // Clockwise
//     } else {
//       encoderValue--;  // Counter-Clockwise
//     }
//   } else if (PreviousCLK == 1 && currentCLK == 0) {
//     if (currentDT == 1) {
//       encoderValue++;  // Clockwise
//     } else {
//       encoderValue--;  // Counter-Clockwise
//     }
//   }

//   PreviousCLK = currentCLK;
//   PreviousDT = currentDT;
// }

// void IRAM_ATTR handleButtonPress() {
//   unsigned long currentTime = millis();
//   if (currentTime - TimeOfLastDebounce > DelayofDebounce) {
//     TimeOfLastDebounce = currentTime;
//     Serial.println("Button Pressed!");
//   }
// }

// void setup() {
//   Serial.begin(115200);

//   pinMode(ROTARY_ENCODER_A_PIN, INPUT);
//   pinMode(ROTARY_ENCODER_B_PIN, INPUT);
//   pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);

//   attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_A_PIN), handleEncoderChange, CHANGE);
//   attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_BUTTON_PIN), handleButtonPress, FALLING);

//   PreviousCLK = digitalRead(ROTARY_ENCODER_A_PIN);
//   PreviousDT = digitalRead(ROTARY_ENCODER_B_PIN);

//   xTaskCreatePinnedToCore(
//     readEncoderTask,    // Function to implement the task
//     "readEncoderTask",  // Name of the task
//     10000,              // Stack size in words
//     NULL,               // Task input parameter
//     1,                  // Priority of the task
//     NULL,               // Task handle
//     0                   // Core where the task should run
//   );
// }

// void loop() {
//   if (lastReportedValue != encoderValue) {
//     Serial.println(encoderValue);
//     lastReportedValue = encoderValue;
//   }
//   Serial.println(encoderValue);
//   delay(10);
// }

// void readEncoderTask(void * pvParameters) {
//   for (;;) {
//     if (lastEncoderValue != encoderValue) {
//       // Handle encoder value changes
//       lastEncoderValue = encoderValue;
//     }
//     vTaskDelay(1 / portTICK_PERIOD_MS); // Delay for 1 ms
//   }
// }


const int DT_PIN = 21;
const int CLK_PIN = 22;
int counter = 0;
int lastState;
int currState;
String prev = "";

void setup() {
  // put your setup code here, to run once:

  pinMode(DT_PIN, INPUT);
  pinMode(CLK_PIN, INPUT);
  lastState = digitalRead(CLK_PIN);

  Serial.begin(115200);


}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  String pattern = "";

  currState = digitalRead(CLK_PIN);
  int clkPin = digitalRead(CLK_PIN);
  int dtPin = digitalRead(DT_PIN);

  if (clkPin == 0) {
    Serial.println("Clock LOW");
    pattern += "C_0";
  } else if (clkPin == 1) {
    pattern += "C_1";
  }

  if (dtPin == 0) {
    Serial.println("Data LOW");
    pattern += "D_0";
  } else if (dtPin == 1) {
    pattern += "D_1";
  }

  if (prev != pattern) {
    Serial.println(pattern);
    prev = pattern;
  }

  // String t = "AB values: " + String(clkPin) + String(dtPin);

  // Serial.println(t);

  // Serial.println(clkPin);
  // Serial.println(dtPin);

  //  if(currState != lastState) {
  //    if (dtPin < currState) {
  //      counter++;
  //    } else {
  //      counter--;
  //    }
  //    Serial.println("Position");
  //    Serial.println(counter);
  //  }
  //  lastState = currState;
}
