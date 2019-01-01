// ArduinoProtoThreadExample
// ArduinoProtoThreadExample.ino
//
// The main sketch file of the ArduinoProtoThreadExample project.
//
// https://github.com/gregkrsak/ArduinoProtoThread
//
// Copyright 2018, 2019 Greg M. Krsak <greg.krsak@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//


#include "ArduinoProtoThread.hpp"

#include "ArduinoProtoThreadStateMachine.hpp"

#include "pins.h"


// Sample delegate object
class LedFlasher : public ArduinoProtoThreadDelegate
{
public:
  LedFlasher(int pin)
  {
    this->outputPin = pin;
  }
  ~LedFlasher() { }
  
  void onStart()
  {
    pinMode(this->outputPin, OUTPUT);
  }
  void onRunning()
  {
    static bool ledState = LOW;
    // Flip-flop the LED state
    if (ledState == HIGH)
    {
      ledState = LOW;
    }
    else
    {
      ledState = HIGH;
    }
    // Send the state to hardware
    digitalWrite(this->outputPin, ledState);
  }
  void onKill()
  {
    return;
  }

protected:
  int outputPin;
};


// Main protothread instance
ArduinoProtoThread *protoThread;
// Protothread delegate for an LED flasher
LedFlasher *flasher;


//////////////////////////////////////////////////////////////////////////////////////////////////
// RUN ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  // Initialize delegates
  flasher = new LedFlasher(OUTPUT_PIN_LED);
  // Initialize protothreads
  protoThread = new ArduinoProtoThread();
  protoThread->delegateCallbacksTo(flasher);
  protoThread->setExecutionIntervalTo(500);
  protoThread->changeStateTo(Start);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// INFINITE LOOP
//////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  protoThread->timeSlice();
}

// End of ArduinoProtoThreadExample.ino
