/*
 * I2C_Interface.h
 *
 *  Created on: Oct 17, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_I2C_I2C_INTERFACE_H_
#define MCAL_I2C_I2C_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/*************************************************************************************/
/* 				MACROS THAT ARE TO BE RETURNED AS STATUS IN FUNCTIONS				 */
/*************************************************************************************/
#define I2C_SENT_START				0
#define I2C_START_ERROR				1
#define I2C_SENT_REPEATED_START		2
#define I2C_REPEATED_START_ERROR	3
#define I2C_RECEIVED_ACK			4
#define I2C_RECEIVED_NACK			5
#define I2C_ARBITRATION_LOST		6
#define I2C_ADDRESS_ERROR			7
#define I2C_DATA_ERROR				8
#define I2C_SENT_ACK				9
#define I2C_SENT_NACK				10
/*************************************************************************************/


/*************************************************************************************/
/* 						USEFUL MACROS AS FUNCTIONS' ARGUMENTS   					 */
/*************************************************************************************/
#define I2C_SEND_ACK				1
#define I2C_SEND_NACK				0
/*************************************************************************************/


/************************************************************************************/
/* 								FUNCTIONS PROTOTYPE					 				*/
/************************************************************************************/

/************************************************************************************/
/* Description: initializes the I2C peripheral				  						*/
/* Input      : nothing 		                                                    */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 I2C_U8Init(void);
/************************************************************************************/

/************************************************************************************/
/* Description: sends a start condition to start communication as a master. This	*/
/* function can	be used whenever it is desired to be a master. 						*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_SENT_START: if start condition was transmitted successfully				*/
/* • I2C_START_ERROR: if start condition was not transmitted successfully			*/
/*																					*/
/* Input: pointer to a variable to receive the status in	                        */
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8MasterStart(u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: sends a repeated start condition to start communication as a master.*/
/* This function can be used while in master mode to communicate with another slave */
/* or change the data direction without losing the bus control.						*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_SENT_REPEATED_START: if repeated start condition was transmitted			*/
/*   successfully.																	*/
/* • I2C_REPEATED_START_ERROR: if repeated start condition was not transmitted		*/
/*   successfully																	*/
/*																					*/
/* Input: pointer to a variable to receive the status in	                        */
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8MasterRepeatedStart(u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: sends an address byte with a write operation as a master.			*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_RECEIVED_ACK: if the slave responded with an acknowledge pulse.			*/
/* • I2C_RECEIVED_NACK: if the slave responded with a not acknowledge pulse.		*/
/* • I2C_ARBITRATION_LOST: if arbitration with another master was lost.				*/
/* • I2C_ADDRESS_ERROR: if the address byte was not transmitted successfully		*/
/*																					*/
/* Input: address - pointer to a variable to receive the status in                  */
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8MasterSendAddressWrite(const u8 LOC_U8Address, u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: sends a data byte as a master. This function should be used after	*/
/* successfully pairing with a slave (i.e. sent the slave's address and the slave	*/
/* responded with an ACK pulse.														*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_RECEIVED_ACK: if data was transmitted successfully and the slave responded	*/
/*   with an acknowledge pulse.														*/
/* • I2C_RECEIVED_NACK: if data was transmitted successfully and the slave			*/
/*   responded with a not acknowledge pulse.										*/
/* • I2C_ARBITRATION_LOST: if arbitration with another master was lost.				*/
/* • I2C_DATA_ERROR: if the data byte was not transmitted successfully				*/
/*																					*/
/* Input: data - pointer to a variable to receive the status in                  	*/
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8MasterSendData (const u8 LOC_U8Data, u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: sends an address byte with a read operation as a master.			*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_RECEIVED_ACK: if the slave responded with an acknowledge pulse.			*/
/* • I2C_RECEIVED_NACK: if the slave responded with a not acknowledge pulse.		*/
/* • I2C_ARBITRATION_LOST: if arbitration with another master was lost.				*/
/* • I2C_ADDRESS_ERROR: if the address byte was not transmitted successfully		*/
/*																					*/
/* Input: address - pointer to a variable to receive the status in                  */
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8MasterSendAddressRead(const u8 LOC_U8Address, u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: receives a data byte as a master from a previously addressed slave.	*/
/* On receiving a data byte, it is optional to choose whether to send an ACK pulse	*/
/* if it is desired to receive more data bytes, or to send an NACK pulse if the		*/
/* last data byte was received. This is decided from the value passed in the second	*/
/* argument.																		*/
/* Possible arguments that can be passed to variable LOC_U8Response:				*/
/* • I2C_SEND_ACK: if it is desired to a receive more data bytes.					*/
/* • I2C_SEND_NACK: if it is desired not to receive data bytes anymore (i.e. the	*/
/*   last data byte was received).													*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_SENT_ACK: if the data byte was received successfully and an ACK pulse was	*/
/*   sent.																			*/
/* • I2C_SENT_NACK: if the data byte was received successfully and a NACK pulse was	*/
/*   sent.																			*/
/* • I2C_ARBITRATION_LOST: if arbitration with another master was lost.				*/
/* • I2C_DATA_ERROR: if the data byte was not received successfully					*/
/*																					*/
/* Input: pointer to a variable to receive the data  in - ACK or NACK response -	*/
/* pointer to a variable to receive the status in                  					*/
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8MasterReceiveData (u8* const LOC_U8Data, const u8 LOC_U8Response, u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: sends a stop condition as a master.									*/
/* Input: nothing																	*/
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8MasterStop(void);
/************************************************************************************/

/************************************************************************************/
/* Description: waits until being addressed by a master.							*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_SENT_ACK: if the slave was addressed and an ACK pulse was sent successfully*/
/* • I2C_ADDRESS_ERROR: if the slave was not addressed successfully					*/
/*																					*/
/* Input: pointer to a variable to receive the status in	                        */
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8SlaveWaitForAddress(u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: receives a data byte as a slave. On receiving a data byte, it is	*/
/* optional to choose whether to send an ACK pulse if it is desired to receive more	*/
/* data bytes, or to send an NACK pulse if the last data byte was received. This is	*/
/* decided from the value passed in the second argument.							*/
/* Possible arguments that can be passed to variable LOC_U8Response:				*/
/* • I2C_SEND_ACK: if it is desired to a receive more data bytes.					*/
/* • I2C_SEND_NACK: if it is desired not to receive data bytes anymore (i.e. the	*/
/*   last data byte was received).													*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_SENT_ACK: if the data byte was received successfully and an ACK pulse was	*/
/*   sent.																			*/
/* • I2C_SENT_NACK: if the data byte was received successfully and a NACK pulse was	*/
/*   sent.																			*/
/* • I2C_DATA_ERROR: if the data byte was not received successfully					*/
/*																					*/
/* Input: pointer to a variable to receive the data  in - ACK or NACK response -	*/
/* pointer to a variable to receive the status in                  					*/
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8SlaveReceiveData(u8* const LOC_U8Data, const u8 LOC_U8Response, u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: sends a data byte as a slave. This function should be used after	*/
/* successfully pairing with a master (i.e. received own slave address and responded*/
/* with an ACK pulse.																*/
/* Possible status that can be returned from function in variable LOC_U8Status:		*/
/* • I2C_RECEIVED_ACK: if data was transmitted successfully and the master responded*/
/*   with an acknowledge pulse.														*/
/* • I2C_RECEIVED_NACK: if data was transmitted successfully and the master			*/
/*   responded with a not acknowledge pulse.										*/
/* • I2C_DATA_ERROR: if the data byte was not transmitted successfully				*/
/*																					*/
/* Input: data - pointer to a variable to receive the status in                  	*/
/* Output: error checking		                                                    */
/************************************************************************************/
extern u8 I2C_U8SlaveSendData (const u8 LOC_U8Data, u8* const LOC_U8Status);
/************************************************************************************/

/************************************************************************************/
/* Description: This function clears the I2C interrupt flag. These are the cases	*/
/* where the I2C interrupt flag is fired:											*/
/* • After the I2C has transmitted a START/REPEATED START condition					*/
/* • After the I2C has transmitted SLA+R/W											*/
/* • After the I2C has transmitted an address byte									*/
/* • After the I2C has lost arbitration												*/
/* • After the I2C has been addressed by own slave address or general call			*/
/* • After the I2C has received a data byte											*/
/* • After a STOP or REPEATED START has been received while still addressed as a	*/
/* slave																			*/
/* • When a bus error has occurred due to an illegal START or STOP condition		*/
/* Note that this flag is not automatically cleared by hardware when executing the	*/
/* interrupt routine, so you need to use this function to clear it manually.		*/
/* Input: nothing		 		                                                    */
/* Output: error checking                                                      		*/
/************************************************************************************/
extern u8 I2C_U8ClearFlag(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables interrupt for I2C peripheral.			 					*/
/* Input      : nothing	                             		                        */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 I2C_U8EnableInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables interrupt for I2C peripheral.			 					*/
/* Input      : nothing			                                                    */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 I2C_U8DisableInterrupt(void);
/************************************************************************************/

/***********************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	   */
/* triggering the I2C interrupt.									 			   */
/* Inputs: pointer to a function that takes no arguments and returns no value	   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 I2C_U8SetCallBack( void (*ptrToFun) (void) );
/***********************************************************************************/

#endif /* MCAL_I2C_I2C_INTERFACE_H_ */
