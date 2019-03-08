![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Ambient_5 Click

- **CIC Prefix**  : AMBIENT5
- **Author**      : Aleksandar Paunovic
- **Verison**     : 1.0.0
- **Date**        : Nov 2018.

---

### Software Support

We provide a library for the Ambient_5 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2663/ambient-5-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

 Library contains functions for reading from and writing to selected registers
 Library contains functions for calculating refresh time, data resolution and light level
 Library contains functions for powering device on and checking state of int pin
 Library contains functions for setting high and low threshold values

Key functions :

- ``` void ambient5_powerOn( void ) ```                      - powers device on and sets basic settings
- ``` float ambient5_getHighResolutionLightLevel( void ) ``` - returns ambient light level in lux [lx]
- ``` uint16_t ambient5_getRefreshTime( void ) ```           - returns time needed for new data to become available

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes i2c, log, and INT pin as input
- Application Initialization - Initializes i2c driver, powers the device and calculates refresh time
- Application Task - Logs high resolution data after a period of time ( refresh time calculated using - ambient5_getRefreshTime( ) )


```.c

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

```


The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2663/ambient-5-click) page.

Other mikroE Libraries used in the example:

- I2C
- UART
- Conversions

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
