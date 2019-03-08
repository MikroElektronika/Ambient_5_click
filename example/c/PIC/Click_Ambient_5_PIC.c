/*
Example for Ambient_5 Click

    Date          : Nov 2018.
    Author        : Aleksandar Paunovic

Test configuration PIC :
    
    MCU             : P18F87K22
    Dev. Board      : EasyPIC PRO v7
    PIC Compiler ver : v7.2.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes i2c, log, and INT pin as input
- Application Initialization - Initializes i2c driver, powers the device and calculates refresh time
- Application Task - Logs high resolution data after a period of time ( refresh time calculated using - ambient5_getRefreshTime( ) )
*/

#include "Click_Ambient_5_types.h"
#include "Click_Ambient_5_config.h"


char text[50];
uint16_t rTime;
uint16_t i;
uint16_t lth;
uint16_t hth;
float highResLightLevel;
float highThreshold = 500.0;
float lowThreshold = 100.0;
float res;


void systemInit( )
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );

    mikrobus_i2cInit( _MIKROBUS1, &_AMBIENT5_I2C_CFG[0] );

    mikrobus_logInit( _LOG_USBUART, 9600 );

    Delay_ms(100);
    
    mikrobus_logWrite( " sys init done ", _LOG_LINE );
}

void applicationInit( )
{
    ambient5_i2cDriverInit( (T_AMBIENT5_P)&_MIKROBUS1_GPIO, (T_AMBIENT5_P)&_MIKROBUS1_I2C, _AMBIENT5_DEVICE_ADDRESS );
    
    Delay_ms(500);
    
    ambient5_powerOn( );
    
    Delay_ms(10);
    
    ambient5_setLowLightLevelThreshold( lowThreshold );
    ambient5_setHighLightLevelThreshold( highThreshold );
    
    rTime = ambient5_getRefreshTime( );
    
    mikrobus_logWrite( " app init done ", _LOG_LINE );
}

void applicationTask( )
{
    for (i = 0; i < rTime; i ++)
    {
        Delay_ms(1);
    }
    
    highResLightLevel = ambient5_getHighResolutionLightLevel( );

    FloatToStr( highResLightLevel, text );

    mikrobus_logWrite( " Ambient Light Level :   ", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_TEXT );
    mikrobus_logWrite( "  lx", _LOG_LINE );
}

void main( )
{
    systemInit( );
    applicationInit( );
    
    while (1)
    {
        applicationTask( );
    }
}