/*
    __ambient5_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __ambient5_driver.h
@brief    Ambient_5 Driver
@mainpage Ambient_5 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   AMBIENT5
@brief      Ambient_5 Click Driver
@{

| Global Library Prefix | **AMBIENT5** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Nov 2018.**      |
| Developer             | **Aleksandar Paunovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _AMBIENT5_H_
#define _AMBIENT5_H_

/** 
 * @macro T_AMBIENT5_P
 * @brief Driver Abstract type 
 */
#define T_AMBIENT5_P    const uint8_t*

/** @defgroup AMBIENT5_COMPILE Compilation Config */              /** @{ */

// #define   __AMBIENT5_DRV_SPI__                            /**<     @macro __AMBIENT5_DRV_SPI__  @brief SPI driver selector */
   #define   __AMBIENT5_DRV_I2C__                            /**<     @macro __AMBIENT5_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __AMBIENT5_DRV_UART__                           /**<     @macro __AMBIENT5_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup AMBIENT5_VAR Variables */                           /** @{ */

/* slave address */
extern const uint8_t _AMBIENT5_DEVICE_ADDRESS;

/* registers */
extern const uint8_t _AMBIENT5_CONFIGURATION;
extern const uint8_t _AMBIENT5_HIGH_THRESHOLD;
extern const uint8_t _AMBIENT5_LOW_THRESHOLD;
extern const uint8_t _AMBIENT5_POWER_SAVING_MODE;
extern const uint8_t _AMBIENT5_HIGH_RESOLUTION_OUTPUT_DATA;
extern const uint8_t _AMBIENT5_WHITE_CHANNEL_OUTPUT_DATA;
extern const uint8_t _AMBIENT5_INTERRUPT_STATUS;

/* configuration register */
extern const uint16_t _AMBIENT5_GAIN_x1;
extern const uint16_t _AMBIENT5_GAIN_x2;
extern const uint16_t _AMBIENT5_GAIN_x1_8;
extern const uint16_t _AMBIENT5_GAIN_x1_4;
extern const uint16_t _AMBIENT5_INTEGRATION_TIME_25ms;
extern const uint16_t _AMBIENT5_INTEGRATION_TIME_50ms;
extern const uint16_t _AMBIENT5_INTEGRATION_TIME_100ms;
extern const uint16_t _AMBIENT5_INTEGRATION_TIME_200ms;
extern const uint16_t _AMBIENT5_INTEGRATION_TIME_400ms;
extern const uint16_t _AMBIENT5_INTEGRATION_TIME_800ms;
extern const uint16_t _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_1;
extern const uint16_t _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_2;
extern const uint16_t _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_4;
extern const uint16_t _AMBIENT5_PERSISTANCE_PROTECT_NUMBER_8;
extern const uint16_t _AMBIENT5_INTERRUPT_DISABLE;
extern const uint16_t _AMBIENT5_INTERRUPT_ENABLE;
extern const uint16_t _AMBIENT5_POWER_ON;
extern const uint16_t _AMBIENT5_SHUT_DOWN;

/* power saving mode */
extern const uint16_t _AMBIENT5_MODE_1;
extern const uint16_t _AMBIENT5_MODE_2;
extern const uint16_t _AMBIENT5_MODE_3;
extern const uint16_t _AMBIENT5_MODE_4;
extern const uint16_t _AMBIENT5_POWER_SAVING_MODE_DISABLE;
extern const uint16_t _AMBIENT5_POWER_SAVING_MODE_ENABLE;

                                                                       /** @} */
/** @defgroup AMBIENT5_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup AMBIENT5_INIT Driver Initialization */              /** @{ */

#ifdef   __AMBIENT5_DRV_SPI__
void ambient5_spiDriverInit(T_AMBIENT5_P gpioObj, T_AMBIENT5_P spiObj);
#endif
#ifdef   __AMBIENT5_DRV_I2C__
void ambient5_i2cDriverInit(T_AMBIENT5_P gpioObj, T_AMBIENT5_P i2cObj, uint8_t slave);
#endif
#ifdef   __AMBIENT5_DRV_UART__
void ambient5_uartDriverInit(T_AMBIENT5_P gpioObj, T_AMBIENT5_P uartObj);
#endif

                                                                       /** @} */
/** @defgroup AMBIENT5_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Reading register
 *
 * param[in] uint8_t registerAddress_  - address (opCode) of a register
 * param[out] uint16_t readData_       - register content
 *
 * This function gets selected registers content
 */
uint16_t ambient5_getRegister( uint8_t registerAddress_ );

/**
 * @brief Writing register
 *
 * param[in] uint8_t registerAddress_ - address (opCode) of a register
 * param[in] uint16_t registerValue_  - value of a register to be set
 *
 * This function sets selected register content
 */
void ambient5_setRegister( uint8_t registerAddress_, uint16_t registerValue_ );

/**
 * @brief Calculating device resolution
 *
 * param[out] float resolution_ - resolution of output data
 *
 * This function calculates resolution of output data in "high resolution" and "white channel" registers
 */
float ambient5_getResolution( void );

/**
 * @brief Calculating refresh time
 *
 * param[out] uint16_t refreshTime_ - time needed for new data to become available in miliseconds - [ms]
 *
 * This function calculates refresh time, based on user settings for integration time and power saving mode
 * This function returns number of miliseconds needed for new data to become available
 */
uint16_t ambient5_getRefreshTime( void );

/**
 * @brief Calculating light level
 *
 * param[out] float highResolutionLightlevel_ - light level in lux - [lx]
 *
 * This function calculates light level (lux) read from "high resolution output data" register
 */
float ambient5_getHighResolutionLightLevel( void );

/**
 * @brief Calculating light level
 *
 * param[out] float whiteChannelLightLevel_ - light level in lux - [lx]
 *
 * This function calculates light level (lux) read from "white channel output data" register
 */
float ambient5_getWhiteChannelLightLevel( void );

/**
 * @brief Setting low light level threshold
 *
 * param[in] float lowLightLevelThreshold_ - low light level threshold in lux - [lx]
 *
 * This function sets low light level threshold (lux) by setting "low threshold windows setting" register
 */
void ambient5_setLowLightLevelThreshold( float lowLightLevelThreshold_ );

/**
 * @brief Setting high light level threshold
 *
 * param[in] float highLightLevelThreshold_ - high light level threshold in lux - [lx]
 *
 * This function sets high light level threshold (lux) by setting "high threshold windows setting" register
 */
void ambient5_setHighLightLevelThreshold( float highLightLevelThreshold_ );

/*
 * @brief Powering on
 *
 * This function powers device on and sets basic settings
 */
void ambient5_powerOn( void );

/*
 * @brief Checking INT pin state
 *
 * param[out] (0 or 1) - state of INT pin
 *
 * This function checks INT pin state
 * This function returns 0 if INT pin is LOW
 * This function returns 1 if INT pin is HIGH
 */
uint8_t ambient5_checkIntPin( void );

                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Ambient_5_STM.c
    @example Click_Ambient_5_TIVA.c
    @example Click_Ambient_5_CEC.c
    @example Click_Ambient_5_KINETIS.c
    @example Click_Ambient_5_MSP.c
    @example Click_Ambient_5_PIC.c
    @example Click_Ambient_5_PIC32.c
    @example Click_Ambient_5_DSPIC.c
    @example Click_Ambient_5_AVR.c
    @example Click_Ambient_5_FT90x.c
    @example Click_Ambient_5_STM.mbas
    @example Click_Ambient_5_TIVA.mbas
    @example Click_Ambient_5_CEC.mbas
    @example Click_Ambient_5_KINETIS.mbas
    @example Click_Ambient_5_MSP.mbas
    @example Click_Ambient_5_PIC.mbas
    @example Click_Ambient_5_PIC32.mbas
    @example Click_Ambient_5_DSPIC.mbas
    @example Click_Ambient_5_AVR.mbas
    @example Click_Ambient_5_FT90x.mbas
    @example Click_Ambient_5_STM.mpas
    @example Click_Ambient_5_TIVA.mpas
    @example Click_Ambient_5_CEC.mpas
    @example Click_Ambient_5_KINETIS.mpas
    @example Click_Ambient_5_MSP.mpas
    @example Click_Ambient_5_PIC.mpas
    @example Click_Ambient_5_PIC32.mpas
    @example Click_Ambient_5_DSPIC.mpas
    @example Click_Ambient_5_AVR.mpas
    @example Click_Ambient_5_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __ambient5_driver.h

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