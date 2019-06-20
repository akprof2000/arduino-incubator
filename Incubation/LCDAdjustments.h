/*
* LCD Adjustments: Copyright (c) 2010 Andy Brown
* http://www.andybrown.me.uk
*
* This work is licensed under a Creative Commons
* Attribution_ShareAlike 3.0 Unported License.
* http://creativecommons.org/licenses/by_sa/3.0/
*/

#ifndef __B66E1DAA_232C_4362_86C4_86F942C1F9C8
#define __B66E1DAA_232C_4362_86C4_86F942C1F9C8


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#include <stdint.h>

/*
* LCD Adjustments header file
*/

class LCDAdjustments
{
public:
class PWMManager
{
private:
uint8_t _pin;
uint8_t _currentValue;
uint8_t _defaultPercentage;

public:
// initialize on a PWM pin
void setup(uint8_t pin_,uint8_t defaultValue_);

// reset to the default percentage
void reset();

// set percent value immediately
void setPercentage(uint8_t percentage_);

// set absolute value immediately
void setValue(uint8_t value_);

// fade to the target percentage
void fadeToPercentage(
uint8_t targetPercentage_,
uint32_t microsPerStep_);

// fade to the target value
void fadeToValue(
uint8_t targetValue_,
uint32_t microsPerStep_);

// convert a percentage to an absolute value
uint8_t percentageToValue(uint8_t value_) const;

// get the current value
uint8_t getCurrentValue() const;
};

private:
// brightness manager
PWMManager _brightness;

// contrast manager
PWMManager _contrast;

// saved power saving value
uint8_t _powerSavingValue;

public:
// create the class
void setup(
uint8_t brightnessPin_,
uint8_t contrastPin_,
uint8_t initialBrightnessPercent_,
uint8_t initialContrastPercent_);

// get the brightness handler
PWMManager& brightness();

// get the contrast handler
PWMManager& contrast();

// enter power saving immediately
void enterPowerSaving();

// enter power saving by fade out
void enterPowerSaving(uint32_t microsPerStep_);

// exit power saving immediately
void exitPowerSaving();

// exit power saving, fading up
void exitPowerSaving(uint32_t microsPerStep_);
};

#endif




