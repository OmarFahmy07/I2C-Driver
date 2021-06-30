/*
 * I2C_Private.h
 *
 *  Created on: Oct 17, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_I2C_I2C_PRIVATE_H_
#define MCAL_I2C_I2C_PRIVATE_H_


/***********************************************************************************/
/*  							  REGISTERS ADDRESSES							   */
/***********************************************************************************/
#define TWCR_REGISTER 								*((volatile u8*)0x56)
#define TWDR_REGISTER 								*((volatile u8*)0x23)
#define TWAR_REGISTER 								*((volatile u8*)0x22)
#define TWSR_REGISTER 								*((volatile u8*)0x21)
#define TWBR_REGISTER 								*((volatile u8*)0x20)
/***********************************************************************************/


/***********************************************************************************/
/* 					              TWCR REGISTER BITS							   */
/***********************************************************************************/
#define TWINT										7
#define TWEA										6
#define TWSTA										5
#define TWSTO										4
#define TWWC										3
#define TWEN										2
#define BIT1										1
#define TWIE										0
/***********************************************************************************/


/***********************************************************************************/
/* 					              TWSR REGISTER BITS							   */
/***********************************************************************************/
#define TWPS1										1
#define TWPS0										0
/***********************************************************************************/

/***********************************************************************************/
/* 					              TWAR REGISTER BITS							   */
/***********************************************************************************/
#define TWGCE										0
/***********************************************************************************/


/***********************************************************************************/
/* 					              TWDR REGISTER BITS							   */
/***********************************************************************************/
#define TWD0										0
/***********************************************************************************/


/***********************************************************************************/
/* 					                  BIT RATE RANGE						   	   */
/***********************************************************************************/
#define MINIMUM_BIT_RATE							10
/***********************************************************************************/


/***********************************************************************************/
/* 					                	PRESCALER 							   	   */
/***********************************************************************************/
#define PRESCALER_1									1
#define PRESCALER_4									4
#define PRESCALER_16								16
#define PRESCALER_64								64
/***********************************************************************************/


/***********************************************************************************/
/* 					               SLAVE ADDRESS RANGE							   */
/***********************************************************************************/
#define MINIMUM_ADDRESS								0x01
#define MAXIMUM_ADDRESS								0x77
/***********************************************************************************/


/***********************************************************************************/
/* 					           GENERAL CALL - BROADCASTING						   */
/***********************************************************************************/
#define ENABLE_GENERAL_CALL							0
#define DISABLE_GENERAL_CALL						1
/***********************************************************************************/


/***********************************************************************************/
/* 					           		STATUS CODES						   		   */
/***********************************************************************************/
#define START_STATUS								0x08
#define REPEATED_START_STATUS						0x10
#define ADDRESS_WRITE_ACK_STATUS					0x18
#define ADDRESS_WRITE_NACK_STATUS					0x20
#define ADDRESS_READ_ACK_STATUS						0x40
#define ADDRESS_READ_NACK_STATUS					0x48
#define SENT_DATA_ACK_STATUS						0x28
#define SENT_DATA_NACK_STATUS						0x30
#define RECEIVED_DATA_ACK_STATUS					0x50
#define RECEIVED_DATA_NACK_STATUS					0x58
#define ARBITRATION_LOST_STATUS						0x38
#define SLA_ADDRESSED_ACK_STATUS					0x60
#define GC_ADDRESSED_ACK_STATUS						0x70
#define LOST_SLA_ADDRESSED_STATUS					0x68
#define LOST_GC_ADDRESSED_STATUS					0x78
#define SLA_ADDRESSED_ACK_DATA_STATUS				0x80
#define GC_ADDRESSED_ACK_DATA_STATUS				0x90
#define SLA_ADDRESSED_NACK_DATA_STATUS				0x88
#define GC_ADDRESSED_NACK_DATA_STATUS				0x98
#define SLA_ADDRESSED_READ_ACK_STATUS				0xA8
#define LOST_SLA_ADDRESSED_READ_STATUS				0xB0
#define SLAVE_SENT_ACK_STATUS						0xB8
#define SLAVE_SENT_NACK_STATUS						0xC0
#define SLAVE_LAST_DATA_ACK_STATUS					0xC8
/***********************************************************************************/


/*************************************************************************************/
/* 					           	   OPERATION STATUS						   		     */
/*************************************************************************************/
#define SENT_START				0
#define START_ERROR				1
#define SENT_REPEATED_START		2
#define REPEATED_START_ERROR	3
#define RECEIVED_ACK			4
#define RECEIVED_NACK			5
#define ARBITRATION_LOST		6
#define ADDRESS_ERROR			7
#define DATA_ERROR				8
#define SENT_ACK				9
#define SENT_NACK				10
/*************************************************************************************/


/*************************************************************************************/
/* 					       	  FUNCTIONS PASSED ARGUMENTS				   		     */
/*************************************************************************************/
#define SEND_ACK				1
#define SEND_NACK				0
/*************************************************************************************/


/***********************************************************************************/
/* 					           	   OTHER DEFINITIONS							   */
/***********************************************************************************/
#define SHIFT_BY_ONE								1
#define MASK_PRESCALER_BITS							0xF8
/***********************************************************************************/


/***********************************************************************************/
/* 							  PRIVATE FUNCTIONS PROTOTYPE 						   */
/***********************************************************************************/
void __vector_19(void) __attribute__((signal));
static u8 I2C_U8StartConditionSequence(void);
static u8 I2C_U8InfoSequence(void);
/***********************************************************************************/



#endif /* MCAL_I2C_I2C_PRIVATE_H_ */
