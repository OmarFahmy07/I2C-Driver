/*
 * I2C_Configure.h
 *
 *  Created on: Oct 17, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_I2C_I2C_CONFIGURE_H_
#define MCAL_I2C_I2C_CONFIGURE_H_

/*****************************************************************************/
/*   BIT RATE CONFIGURATION - SHOULD BE 10 OR HIGHER (FOR MASTER MODE ONLY)  */
/* BIT RATE AND PRESCALER ARE USED TO CALCULATE THE SCL FREQUENCY AS FOLLOW: */
/* SCL FREQUENCY = CPU CLOCK FREQUENCY / (16 + (2 * BIT RATE * PRESCALER) )  */
/*****************************************************************************/
#define BIT_RATE								32
/*****************************************************************************/


/*****************************************************************************/
/*     		    OPTIONS FOR PRESCALER (FOR MASTER MODE ONLY):				 */
/*		  PRESCALER_1 - PRESCALER_4 - PRESCALER_16 - PRESCALER_64			 */
/*																			 */
/* BIT RATE AND PRESCALER ARE USED TO CALCULATE THE SCL FREQUENCY AS FOLLOW: */
/* SCL FREQUENCY = CPU CLOCK FREQUENCY / (16 + (2 * BIT RATE * PRESCALER) )  */
/*****************************************************************************/
#define PRESCALER								PRESCALER_1
/*****************************************************************************/


/*****************************************************************************/
/*   		  SLAVE ADDRESS CONFIGURATION - RANGE OF OPTIONS:				 */
/*								  0x01 ~ 0x77								 */
/*****************************************************************************/
#define SLAVE_ADDRESS							0b00000011
/*****************************************************************************/


/*****************************************************************************/
/*     		      OPTIONS FOR GENERAL CALL CONFIGURATION:					 */
/*				ENABLE_GENERAL_CALL - DISABLE_GENERAL_CALL					 */
/*****************************************************************************/
#define GENERAL_CALL							ENABLE_GENERAL_CALL
/*****************************************************************************/


#endif /* MCAL_I2C_I2C_CONFIGURE_H_ */
