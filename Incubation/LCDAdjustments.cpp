/*
* LCD Adjustments: Copyright (c) 2010 Andy Brown
* http://www.andybrown.me.uk
*
* This work is licensed under a Creative Commons
* Attribution-ShareAlike 3.0 Unported License.
* http://creativecommons.org/licenses/by-sa/3.0/
*/

#include "LCDAdjustments.h"


/*
* Setup the class with pins
*/

void LCDAdjustments::setup(
uint8_t brightnessPin_,
uint8_t contrastPin_,
uint8_t initialBrightness_,
uint8_t initialContrast_)
{
// 32Khz on 9/10
//TCCR1B=1;

// setup the brightness
_brightness.setup(brightnessPin_,initialBrightness_);

// setup the contrast
_contrast.setup(contrastPin_,initialContrast_);
}


/*
* Return the brightness manager
*/

LCDAdjustments::PWMManager &LCDAdjustments::brightness()
{
return _brightness;
}


/*
* Return the contrast manager
*/

LCDAdjustments::PWMManager& LCDAdjustments::contrast()
{
return _contrast;
}


/*
* Enter power saving immediately
*/

void LCDAdjustments::enterPowerSaving()
{
// save the current value and switch off the backlight

_powerSavingValue=_brightness.getCurrentValue();
_brightness.setValue(0);
}


/*
* Enter power saving with fade
*/

void LCDAdjustments::enterPowerSaving(uint32_t microsPerStep_)
{
// save current value and fade out the backlight

_powerSavingValue=_brightness.getCurrentValue();
_brightness.fadeToPercentage(0,microsPerStep_);
}


/*
* Exit from power saving immediately
*/

void LCDAdjustments::exitPowerSaving()
{
_brightness.setValue(_powerSavingValue);
}


/*
* Exit from power saving with fade up
*/

void LCDAdjustments::exitPowerSaving(uint32_t microsPerStep_)
{
_brightness.fadeToValue(_powerSavingValue,microsPerStep_);
}


/*
* Setup the PWM manager
*/

void LCDAdjustments::PWMManager::setup(
uint8_t pin_,
uint8_t defaultPercentage_)
{
_pin=pin_;
_defaultPercentage=defaultPercentage_;

pinMode(pin_,OUTPUT);
setPercentage(defaultPercentage_);
}


/*
* Set the value immediately
*/

void LCDAdjustments::PWMManager::setPercentage(uint8_t percentage_)
{
setValue(percentageToValue(percentage_));
}


/*
* Set the absolute value
*/

void LCDAdjustments::PWMManager::setValue(uint8_t value_)
{
// save the current value and write it to the pin

_currentValue=value_;
analogWrite(_pin,value_);
}


/**
* Fade to a given percentage
*/

void LCDAdjustments::PWMManager::fadeToPercentage(
uint8_t targetPercentage_,
uint32_t microsPerStep_)
{
fadeToValue(percentageToValue(targetPercentage_),microsPerStep_);
}


/**
* Fade to a given value
*/

void LCDAdjustments::PWMManager::fadeToValue(
uint8_t targetValue_,
uint32_t microsPerStep_)
{
int8_t direction;

// figure out whether we're going up or down
direction=targetValue_>_currentValue ? 1 : -1;

while(_currentValue!=targetValue_)
{
setValue(_currentValue+direction);
delayMicroseconds(microsPerStep_);
}
}


/*
* Convert percentage to absolute value
*/

uint8_t LCDAdjustments::PWMManager::percentageToValue(uint8_t percentage_) const
{
return static_cast<uint8_t>((255*(int)percentage_)/100);
}


/*
* Reset to the default percentage
*/

void LCDAdjustments::PWMManager::reset()
{
setPercentage(_defaultPercentage);
}


/*
* Get the current value
*/

uint8_t LCDAdjustments::PWMManager::getCurrentValue() const
{
return _currentValue;
}




