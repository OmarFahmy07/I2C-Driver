/*
 * I2C_Program.c
 *
 *  Created on: Oct 17, 2020
 *      Author: Omar Fahmy
 */

/* LIB LAYER */
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
/* MCAL LAYER */
#include "I2C_Configure.h"
#include "I2C_Private.h"

void (*GLOB_VidI2CPtrCallBack)(void) = NULL;

/************************************************************************************/
/* 						  PUBLIC FUNCTIONS IMPLEMENTATION	  						*/
/************************************************************************************/
u8 I2C_U8Init(void)
{
	/* Bit Rate Configuration */
#if BIT_RATE >= MINIMUM_BIT_RATE
	TWBR_REGISTER = BIT_RATE;
#else
#error "Invalid I2C bit rate configuration. Minimum bit rate allowed is 10."
#endif
	/* Prescaler Configuration */
#if PRESCALER_1 == PRESCALER
	CLR_BIT(TWSR_REGISTER, TWPS1);
	CLR_BIT(TWSR_REGISTER, TWPS0);
#elif PRESCALER_4 == PRESCALER
	CLR_BIT(TWSR_REGISTER, TWPS1);
	SET_BIT(TWSR_REGISTER, TWPS0);
#elif PRESCALER_16 == PRESCALER
	SET_BIT(TWSR_REGISTER, TWPS1);
	CLR_BIT(TWSR_REGISTER, TWPS0);
#elif PRESCALER_64 == PRESCALER
	SET_BIT(TWSR_REGISTER, TWPS1);
	SET_BIT(TWSR_REGISTER, TWPS0);
#else
#error "Invalid I2C prescaler configuration"
#endif
	/* Slave Address Configuration */
#if SLAVE_ADDRESS >= MINIMUM_ADDRESS && SLAVE_ADDRESS <= MAXIMUM_ADDRESS
	TWAR_REGISTER = SLAVE_ADDRESS;
	TWAR_REGISTER <<= SHIFT_BY_ONE;
#else
#error "Invalid I2C slave address configuration (out of range)."
#endif
#if ENABLE_GENERAL_CALL == GENERAL_CALL
	SET_BIT(TWAR_REGISTER, TWGCE);
#elif DISABLE_GENERAL_CALL == GENERAL_CALL
	CLR_BIT(TWAR_REGISTER, TWGCE);
#else
#error "Invalid general call configuration"
#endif
	/* Enable I2C Peripheral */
	SET_BIT(TWCR_REGISTER, TWEN);
	return NO_ERROR;
}

u8 I2C_U8MasterStart(u8* const LOC_U8Status)
{
	if (LOC_U8Status != NULL)
	{
		I2C_U8StartConditionSequence();
		/* If START condition was transmitted successfully */
		if ( START_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = SENT_START;
		}
		/* If the start byte was not transmitted successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = START_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8MasterRepeatedStart(u8* const LOC_U8Status)
{
	if (LOC_U8Status != NULL)
	{
		I2C_U8StartConditionSequence();
		/* If the REPEATED START condition was transmitted successfully */
		if ( REPEATED_START_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = SENT_REPEATED_START;
		}
		/* If the REPEATED START condition was not transmitted successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = REPEATED_START_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8MasterSendAddressWrite(const u8 LOC_U8Address, u8* const LOC_U8Status)
{
	if (LOC_U8Status != NULL)
	{
		/* Load Address */
		TWDR_REGISTER = LOC_U8Address;
		TWDR_REGISTER <<= SHIFT_BY_ONE;
		/* Send Address+W Byte */
		I2C_U8InfoSequence();
		/* If address byte was transmitted successfully and ACK has been received */
		if ( ADDRESS_WRITE_ACK_STATUS == (TWSR_REGISTER & MASK_PRESCALER_BITS) )
		{
			/* Update Status */
			*LOC_U8Status = RECEIVED_ACK;
		}
		/* If address byte was transmitted successfully and NACK has been received */
		else if ( ADDRESS_WRITE_NACK_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = RECEIVED_NACK;
		}
		/* If arbitration was lost */
		else if ( ARBITRATION_LOST_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = ARBITRATION_LOST;
		}
		/* If the address byte was not transmitted successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = ADDRESS_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8MasterSendData (const u8 LOC_U8Data, u8* const LOC_U8Status)
{
	if (LOC_U8Status != NULL)
	{
		/* Load Data */
		TWDR_REGISTER = LOC_U8Data;
		/* Send Data Byte */
		I2C_U8InfoSequence();
		/* If data byte was transmitted successfully and ACK has been received */
		if ( SENT_DATA_ACK_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = RECEIVED_ACK;
		}
		/* If data byte was transmitted successfully and NACK has been received */
		else if ( SENT_DATA_NACK_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = RECEIVED_NACK;
		}
		/* If arbitration was lost */
		else if ( ARBITRATION_LOST_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = ARBITRATION_LOST;
		}
		/* If data byte was not transmitted successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = DATA_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8MasterSendAddressRead(const u8 LOC_U8Address, u8* const LOC_U8Status)
{
	if ( LOC_U8Status != NULL )
	{
		/* Load Address */
		TWDR_REGISTER = LOC_U8Address;
		TWDR_REGISTER <<= SHIFT_BY_ONE;
		/* Activate Read Operation */
		SET_BIT(TWDR_REGISTER, TWD0);
		/* Send Address+R Byte */
		I2C_U8InfoSequence();
		/* If address byte was transmitted successfully and ACK has been received */
		if ( ADDRESS_READ_ACK_STATUS == (TWSR_REGISTER & MASK_PRESCALER_BITS) )
		{
			/* Update Status */
			*LOC_U8Status = RECEIVED_ACK;
		}
		/* If address byte was transmitted successfully and NACK has been received */
		else if ( ADDRESS_READ_NACK_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = RECEIVED_NACK;
		}
		/* If arbitration was lost */
		else if ( ARBITRATION_LOST_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = ARBITRATION_LOST;
		}
		/* If the address byte was not transmitted successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = ADDRESS_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8MasterReceiveData (u8* const LOC_U8Data, const u8 LOC_U8Response, u8* const LOC_U8Status)
{
	if (LOC_U8Status != NULL && LOC_U8Data != NULL && ( SEND_ACK == LOC_U8Response || SEND_NACK == LOC_U8Response ) )
	{
		/* Send ACK or NACK pulse according to the passed parameter */
		WRITE_BIT(TWCR_REGISTER, TWEA, LOC_U8Response);
		/* Receive Data */
		I2C_U8InfoSequence();
		/* If data byte was received successfully and ACK has been sent */
		if ( RECEIVED_DATA_ACK_STATUS == (TWSR_REGISTER & MASK_PRESCALER_BITS) )
		{
			/* Update Status */
			*LOC_U8Status = SENT_ACK;
			/* Store received data */
			*LOC_U8Data = TWDR_REGISTER;
		}
		/* If data byte was received successfully and NACK has been sent */
		else if ( RECEIVED_DATA_NACK_STATUS == (TWSR_REGISTER & MASK_PRESCALER_BITS) )
		{
			/* Update Status */
			*LOC_U8Status = SENT_NACK;
			/* Store received data */
			*LOC_U8Data = TWDR_REGISTER;
		}
		/* If data byte was not received successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = DATA_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8MasterStop(void)
{
	/* Clear Start Condition */
	CLR_BIT(TWCR_REGISTER, TWSTA);
	/* Set Stop Condition */
	SET_BIT(TWCR_REGISTER, TWSTO);
	/* Clear Flag - Start Operation */
	SET_BIT(TWCR_REGISTER, TWINT);
	return NO_ERROR;
}




u8 I2C_U8SlaveWaitForAddress(u8* const LOC_U8Status)
{
	if (LOC_U8Status != NULL)
	{
		/* Clear Start Condition */
		CLR_BIT(TWCR_REGISTER, TWSTA);
		/* Clear Stop Condition */
		CLR_BIT(TWCR_REGISTER, TWSTO);
		/* Enable Acknowledge Bit */
		SET_BIT(TWCR_REGISTER, TWEA);

		/* Wait until addressed */
		while ( !GET_BIT(TWCR_REGISTER, TWINT) );

		/* If slave was addressed successfully */
		if ( SLA_ADDRESSED_ACK_STATUS == (TWSR_REGISTER & MASK_PRESCALER_BITS) || \
				GC_ADDRESSED_ACK_STATUS == (TWSR_REGISTER & MASK_PRESCALER_BITS) || \
				LOST_SLA_ADDRESSED_STATUS == (TWSR_REGISTER & MASK_PRESCALER_BITS) || \
				LOST_GC_ADDRESSED_STATUS == (TWSR_REGISTER & MASK_PRESCALER_BITS) )
		{
			/* Update Status */
			*LOC_U8Status = SENT_ACK;
		}
		/* If slave was not addressed successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = ADDRESS_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8SlaveReceiveData(u8* const LOC_U8Data, const u8 LOC_U8Response, u8* const LOC_U8Status)
{
	if (LOC_U8Data != NULL && LOC_U8Status != NULL)
	{
		/* Send ACK or NACK after receiving data according to the passed response */
		WRITE_BIT(TWCR_REGISTER, TWEA, LOC_U8Response);
		/* Clear Flag */
		SET_BIT(TWCR_REGISTER, TWINT);

		/* Wait until data is received */
		while ( !GET_BIT(TWCR_REGISTER, TWINT) );

		/* If data was received successfully and ACK was returned */
		if ( SLA_ADDRESSED_ACK_DATA_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS )  || \
				GC_ADDRESSED_ACK_DATA_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = SENT_ACK;
			/* Get Received Data */
			*LOC_U8Data = TWDR_REGISTER;
		}
		/* If data was received successfully and NACK was returned */
		else if ( SLA_ADDRESSED_NACK_DATA_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS )  || \
				GC_ADDRESSED_NACK_DATA_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = SENT_NACK;
			/* Get Received Data */
			*LOC_U8Data = TWDR_REGISTER;
		}
		/* If data was not received successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = DATA_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8SlaveSendData (const u8 LOC_U8Data, u8* const LOC_U8Status)
{
	if (LOC_U8Status != NULL)
	{
		/* Load Data */
		TWDR_REGISTER = LOC_U8Data;
		/* Send Data Byte */
		I2C_U8InfoSequence();
		/* If data byte was transmitted successfully and ACK has been received */
		if ( SLAVE_SENT_ACK_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) || \
				SLAVE_LAST_DATA_ACK_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = RECEIVED_ACK;
		}
		/* If data byte was transmitted successfully and NACK has been received */
		else if ( SLAVE_SENT_NACK_STATUS == ( TWSR_REGISTER & MASK_PRESCALER_BITS ) )
		{
			/* Update Status */
			*LOC_U8Status = RECEIVED_NACK;
		}
		/* If data byte was not transmitted successfully */
		else
		{
			/* Update Status */
			*LOC_U8Status = DATA_ERROR;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 I2C_U8ClearFlag(void)
{
	SET_BIT(TWCR_REGISTER, TWINT);
	return NO_ERROR;
}

u8 I2C_U8EnableInterrupt(void)
{
	SET_BIT(TWCR_REGISTER, TWIE);
	return NO_ERROR;
}

u8 I2C_U8DisableInterrupt(void)
{
	CLR_BIT(TWCR_REGISTER, TWIE);
	return NO_ERROR;
}

u8 I2C_U8SetCallBack( void (*ptrToFun) (void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidI2CPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}
/************************************************************************************/


/************************************************************************************/
/* 						  PRIVATE FUNCTIONS IMPLEMENTATION  						*/
/************************************************************************************/
void __vector_19(void)
{
	if (GLOB_VidI2CPtrCallBack != NULL)
	{
		(*GLOB_VidI2CPtrCallBack)();
	}
}

static u8 I2C_U8StartConditionSequence(void)
{
	/* Clear Stop Condition */
	CLR_BIT(TWCR_REGISTER, TWSTO);
	/* Set Start Condition */
	SET_BIT(TWCR_REGISTER, TWSTA);
	/* Clear Flag - Start Operation */
	SET_BIT(TWCR_REGISTER, TWINT);

	/* Wait until START condition has been transmitted */
	while ( !GET_BIT(TWCR_REGISTER, TWINT) );

	return NO_ERROR;
}

static u8 I2C_U8InfoSequence(void)
{
	/* Clear Start Condition */
	CLR_BIT(TWCR_REGISTER, TWSTA);
	/* Clear Stop Condition */
	CLR_BIT(TWCR_REGISTER, TWSTO);
	/* Clear Flag - Start Operation */
	SET_BIT(TWCR_REGISTER, TWINT);

	/* Wait until info byte has been transmitted or received */
	while ( !GET_BIT(TWCR_REGISTER, TWINT) );

	return NO_ERROR;
}
/************************************************************************************/
