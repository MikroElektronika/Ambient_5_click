/*
    __ambient5_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__ambient5_driver.h"
#include "__ambient5_hal.c"

/* ------------------------------------------------------------------- MACROS */

/* slave address */
const uint8_t _AMBIENT5_DEVICE_ADDRESS                  = 0x10;

/* registers */
const uint8_t _AMBIENT5_CONFIGURATION                   = 0x00;
const uint8_t _AMBIENT5_HIGH_THRESHOLD                  = 0x01;
const uint8_t _AMBIENT5_LOW_THRESHOLD                   = 0x02;
const uint8_t _AMBIENT5_POWER_SAVING_MODE               = 0x03;
const uint8_t _AMBIENT5_HIGH_RESOLUTION_OUTPUT_DATA     = 0x04;
const uint8_t _AMBIENT5_WHITE_CHANNEL_OUTPUT_DATA       = 0x05;
const uint8_t _AMBIENT5_INTERRUPT_STATUS                = 0x06;

/* configuration register */
const uint16_t _AMBIENT5_GAIN_x1                      = 0x0000;
const uint16_t _AMBIENT5_GAIN_x2                      = 0x0800;
const uint16_t _AMBIENT5_GAIN_x1_8                    = 0x1000;
const uint16_t _AMBIENT5_GAIN_x1_4                    = 0x1800;
const uint16_t _AMBIENT5_INTEGRATION_TIME_25ms        = 0x0300;
const uint16_t _AMBIENT5_INTEGRATION_TIME_50ms        = 0x0200;
const uint16_t _AMBIENT5_INTEGRATION_TIME_100ms       = 0x0000;
const uint16_t _AMBIENT5_INTEGRATION_TIME_200ms       = 0x0040;
const uint16_t _AMBIENT5_INTEGRATION_TIME_400ms       = 0x0080;
const uint16_t _AMBIENT5_INTEGRATION_TIME_800ms       = 0x00C0;
const uint16_t _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_1 = 0x0000;
const uint16_t _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_2 = 0x0010;
const uint16_t _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_4 = 0x0020;
const uint16_t _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_8 = 0x0030;
const uint16_t _AMBIENT5_INTERRUPT_DISABLE            = 0x0000;
const uint16_t _AMBIENT5_INTERRUPT_ENABLE             = 0x0002;
const uint16_t _AMBIENT5_POWER_ON                     = 0x0000;
const uint16_t _AMBIENT5_SHUT_DOWN                    = 0x0001;

/* power saving mode */
const uint16_t _AMBIENT5_MODE_1                       = 0x0000;
const uint16_t _AMBIENT5_MODE_2                       = 0x0002;
const uint16_t _AMBIENT5_MODE_3                       = 0x0004;
const uint16_t _AMBIENT5_MODE_4                       = 0x0006;
const uint16_t _AMBIENT5_POWER_SAVING_MODE_DISABLE    = 0x0000;
const uint16_t _AMBIENT5_POWER_SAVING_MODE_ENABLE     = 0x0001;

/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __AMBIENT5_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __AMBIENT5_DRV_SPI__

void ambient5_spiDriverInit(T_AMBIENT5_P gpioObj, T_AMBIENT5_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __AMBIENT5_DRV_I2C__

void ambient5_i2cDriverInit(T_AMBIENT5_P gpioObj, T_AMBIENT5_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __AMBIENT5_DRV_UART__

void ambient5_uartDriverInit(T_AMBIENT5_P gpioObj, T_AMBIENT5_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

uint16_t ambient5_getRegister( uint8_t registerAddress_ )
{
    uint16_t readData_;
    uint8_t writeBuffer[1];
    uint8_t readBuffer[2];

    writeBuffer[0] = registerAddress_;

    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, writeBuffer, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readBuffer, 2, END_MODE_STOP );

    readData_ = readBuffer[1];
    readData_ <<= 8;
    readData_ |= readBuffer[0];

    return readData_;
}

void ambient5_setRegister( uint8_t registerAddress_, uint16_t registerValue_ )
{
    uint8_t writeBuffer[3];

    writeBuffer[0] = registerAddress_;
    writeBuffer[1] = registerValue_;
    writeBuffer[2] = registerValue_ >> 8;

    hal_i2cStart( );
    hal_i2cWrite( _slaveAddress, writeBuffer, 3, END_MODE_STOP );
}

float ambient5_getResolution( void )
{
    uint16_t register_;
    uint16_t gain_;
    uint16_t it_;
    float resolution_ = 0.0036;

    register_ = ambient5_getRegister( _AMBIENT5_CONFIGURATION );

    gain_ = register_;
    it_ = register_;
    
    gain_ >>= 11;
    gain_ &= 0x0003;
    
    it_ >>= 6;
    it_ &= 0x000F;
    
    if (gain_ == 1)
    {
        resolution_ *= 1;
    }
    else if (gain_ == 0)
    {
        resolution_ *= 2;
    }
    else if (gain_ == 3)
    {
        resolution_ *= 8;
    }
    else if (gain_ == 2)
    {
        resolution_ *= 16;
    }
    
    if (it_ == 3)
    {
        resolution_ *= 1;
    }
    else if (it_ == 2)
    {
        resolution_ *= 2;
    }
    else if (it_ == 1)
    {
        resolution_ *= 4;
    }
    else if (it_ == 0)
    {
        resolution_ *= 8;
    }
    else if (it_ == 8)
    {
        resolution_ *= 16;
    }
    else if (it_ == 12)
    {
        resolution_ *= 32;
    }
    
    return resolution_;
}

uint16_t ambient5_getRefreshTime( void )
{
    uint16_t it_;
    uint16_t mode_;
    uint16_t refreshTime_;

    it_ = ambient5_getRegister( _AMBIENT5_CONFIGURATION );
    mode_ = ambient5_getRegister( _AMBIENT5_POWER_SAVING_MODE );

    it_ >>= 6;
    it_ &= 0x000F;

    mode_ >>= 1;
    mode_ &= 0x0003;

    if (it_ == 12)
    {
        if (mode_ == 0)
        {
            refreshTime_ = 525;
        }
        else if (mode_ == 1)
        {
            refreshTime_ = 1025;
        }
        else if (mode_ == 2)
        {
            refreshTime_ = 2025;
        }
        else if (mode_ == 3)
        {
            refreshTime_ = 4025;
        }
    }
    else if (it_ == 8)
    {
        if (mode_ == 0)
        {
            refreshTime_ = 550;
        }
        else if (mode_ == 1)
        {
            refreshTime_ = 1050;
        }
        else if (mode_ == 2)
        {
            refreshTime_ = 2050;
        }
        else if (mode_ == 3)
        {
            refreshTime_ = 4050;
        }
    }
    else if (it_ == 0)
    {
        if (mode_ == 0)
        {
            refreshTime_ = 600;
        }
        else if (mode_ == 1)
        {
            refreshTime_ = 1100;
        }
        else if (mode_ == 2)
        {
            refreshTime_ = 2100;
        }
        else if (mode_ == 3)
        {
            refreshTime_ = 4100;
        }
    }
    else if (it_ == 1)
    {
        if (mode_ == 0)
        {
            refreshTime_ = 700;
        }
        else if (mode_ == 1)
        {
            refreshTime_ = 1200;
        }
        else if (mode_ == 2)
        {
            refreshTime_ = 2200;
        }
        else if (mode_ == 3)
        {
            refreshTime_ = 4200;
        }
    }
    else if (it_ == 2)
    {
        if (mode_ == 0)
        {
            refreshTime_ = 900;
        }
        else if (mode_ == 1)
        {
            refreshTime_ = 1400;
        }
        else if (mode_ == 2)
        {
            refreshTime_ = 2400;
        }
        else if (mode_ == 3)
        {
            refreshTime_ = 4400;
        }
    }
    else if (it_ == 3)
    {
        if (mode_ == 0)
        {
            refreshTime_ = 1300;
        }
        else if (mode_ == 1)
        {
            refreshTime_ = 1800;
        }
        else if (mode_ == 2)
        {
            refreshTime_ = 2800;
        }
        else if (mode_ == 3)
        {
            refreshTime_ = 4800;
        }
    }

    return refreshTime_;
}

float ambient5_getHighResolutionLightLevel( void )
{
    float highResolutionLightlevel_;
    float res_;
    uint16_t aux;

    aux = ambient5_getRegister( _AMBIENT5_HIGH_RESOLUTION_OUTPUT_DATA );
    res_ = ambient5_getResolution( );

    highResolutionLightlevel_ = (float)(aux * res_);

    return highResolutionLightlevel_;

}

float ambient5_getWhiteChannelLightLevel( void )
{
    float whiteChannelLightLevel_;
    float res_;
    uint16_t aux;

    aux = ambient5_getRegister( _AMBIENT5_WHITE_CHANNEL_OUTPUT_DATA );
    res_ = ambient5_getResolution( );
    
    whiteChannelLightLevel_ = (float)(aux * res_);
    
    return whiteChannelLightLevel_;
}

void ambient5_setLowLightLevelThreshold( float lowLightLevelThreshold_ )
{
    uint16_t lightLevelThreshold;
    float res_;

    res_ = ambient5_getResolution( );

    lightLevelThreshold = (uint16_t)(lowLightLevelThreshold_ / res_);
    
    ambient5_setRegister( _AMBIENT5_LOW_THRESHOLD, lightLevelThreshold );
}

void ambient5_setHighLightLevelThreshold( float highLightLevelThreshold_ )
{
    uint16_t lightLevelThreshold;
    float res_;

    res_ = ambient5_getResolution( );

    lightLevelThreshold = (uint16_t)(highLightLevelThreshold_ / res_);

    ambient5_setRegister( _AMBIENT5_HIGH_THRESHOLD, lightLevelThreshold );
}

void ambient5_powerOn( void )
{
    ambient5_setRegister( _AMBIENT5_CONFIGURATION,
                          _AMBIENT5_GAIN_x2 |
                          _AMBIENT5_INTEGRATION_TIME_25ms |
                          _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_1 |
                          _AMBIENT5_INTERRUPT_ENABLE |
                          _AMBIENT5_POWER_ON );
                            
    ambient5_setRegister( _AMBIENT5_POWER_SAVING_MODE,
                          _AMBIENT5_MODE_1 |
                          _AMBIENT5_POWER_SAVING_MODE_ENABLE );
}

uint8_t ambient5_checkIntPin( void )
{
    return hal_gpio_intGet( );
}

/* -------------------------------------------------------------------------- */
/*
  __ambient5_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */