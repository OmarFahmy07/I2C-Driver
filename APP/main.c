/*
 * main.c
 *
 *  Created on: Oct 17, 2020
 *      Author: Omar Fahmy
 */

#define MASTER 1
#define SLAVE 0

#define MODE MASTER

#if MODE == MASTER

#include "../HAL/LCD/LCD_Interface.h"

#include "../MCAL/I2C/I2C_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"

#include <util/delay.h>

/*********************************************************************************/
/*										MASTER									 */
/*********************************************************************************/

int main (void)
{
	u8 status, sendData;
	I2C_U8Init();
	LCD_U8Init();
	I2C_U8MasterStart(&status);
	I2C_U8MasterSendAddressRead(0b00000011, &status);

	while (1)
	{
		I2C_U8MasterReceiveData(&sendData, I2C_SEND_ACK, &status);
		LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
		LCD_U8SendNumber(sendData);
		_delay_ms(1000);
	}

	return 0;
}

#elif MODE == SLAVE
#include "../HAL/LCD/LCD_Interface.h"

#include "../MCAL/I2C/I2C_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"

#include <util/delay.h>

/*********************************************************************************/
/*										SLAVE									 */
/*********************************************************************************/

int main (void)
{
	LCD_U8Init();
	I2C_U8Init();
	u8 status, data = 0;

	I2C_U8SlaveWaitForAddress(&status);

	while (1)
	{
		I2C_U8SlaveSendData(data, &status);
		LCD_U8SendCommand(LCD_CLEAR_DISPLAY);
		LCD_U8SendNumber(data);
		data++;
	}

	return 0;
}
#endif
