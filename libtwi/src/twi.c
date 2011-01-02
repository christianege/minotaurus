#include "twi.h"
#include "TWI_Master.h"

uint8_t twi_init(uint32_t bitrate)
{
	TWIM_Init(bitrate);
}


int twi_probe(uint8_t chip)
{
	return 0;	
}


int twi_read(uint8_t slaveAdress, uint8_t addr, uint8_t *buffer, int len)
{
	if(NULL == buffer)
	{
          return 1;
	}

	/* start the read sequence with a address write!*/
	if (!TWIM_Start (SlaveAddress, TWIM_WRITE))
	{
		TWIM_Stop ();
		printf ("Could not start TWI Bus for READ\n");
		return 1;
	}

	/* write address to slave, this points the address pointer a the given address on the slave */
	if(!TWIM_Write(addr))
	{
		TWIM_Stop ();
		printf ("Could not write the target address onto the bus \n");
		return 1;
	}
	
	/* send repeated start sequence */
	if (!TWIM_Start (SlaveAddress, TWIM_READ))
	{
		TWIM_Stop ();
		printf ("Could not start TWI Bus for READ\n");
		return 1;
	}
	/* read the data */	
	for(int i = 0; i < len; i++)
	{
		buffer[i] = TWIM_ReadAck();
	}
	/* the last byte is followed by a NACK */
	TWIM_ReadNack();
	/* Stop the */	
	TWIM_Stop();	
	return 0;
}

int twi_write(uint8_t chip, uint8_t addr, uint8_t *buffer, int len)
{
	if(NULL == buffer )
	{
		return 1;
	}
	/* start the read sequence with a address write!*/
	if (!TWIM_Start (SlaveAddress, TWIM_WRITE))
	{
		TWIM_Stop ();
		printf ("Could not start TWI Bus for READ\n");
		return 1;
	}

	/* write address to slave, this points the address pointer a the given address on the slave */
	if(!TWIM_Write(addr))
	{
		TWIM_Stop ();
		printf ("Could not write the target address onto the bus \n");
		return 1;
	}	
	for(int i = 0; i < len; i++ )
	{
		if(!TWIM_Write(addr))
		{
			TWIM_Stop ();
			printf ("Could not write the target address onto the bus \n");
			return 1;
		}
	}
	/* stop the write sequence */
	TWIM_Stop (void);
	return 0;
}


uint8_t twi_reg_read (uint8_t chip, uint8_t reg)
{
	return 0;
}

void  twi_reg_write(uint8_t chip, uint8_t reg, uint8_t val)
{

}
