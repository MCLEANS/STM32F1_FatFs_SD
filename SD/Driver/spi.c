/*
		spi.c file is a hardware Driver.
    Copyright (C) 2018 Nima Mohammadi
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "spi.h"

void initSpi(void)
{		
	/* Enable SPI and GPIOB RCC */
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	/* Set SCK Pin to Alternate function Push_Pull */
	GPIOB->CRH &= ~GPIO_CRH_MODE13;
	GPIOB->CRH |= GPIO_CRH_MODE13;

	GPIOB->CRH &= ~GPIO_CRH_CNF13;
	GPIOB->CRH |= GPIO_CRH_CNF13_1;

	/* Set MOSI Pin to Alternate function Push-Pull */
	GPIOB->CRH &= ~GPIO_CRH_MODE15;
	GPIOB->CRH |= GPIO_CRH_MODE15;

	GPIOB->CRH &= ~GPIO_CRH_CNF15;
	GPIOB->CRH |= GPIO_CRH_CNF15_1;

	/* Set MISO pin to alternate function */
	GPIOB->CRH &= ~GPIO_CRH_MODE14;

	GPIOB->CRH &= ~GPIO_CRH_CNF14;
	GPIOB->CRH |= GPIO_CRH_CNF14_1;
	
	/* Set CS pin to General Purpose Output */
	GPIOB->CRH |= GPIO_CRH_MODE12;


	/* SPI Configuration */
	SPI2->CR1  &= ~SPI_CR1_SPE; //Disable SPI
	SPI2->CR1 &= ~ SPI_CR1_BR;
	SPI2->CR1 |=  SPI_CR1_BR_1 | SPI_CR1_BIDIOE ;
	SPI2->CR1 &= ~SPI_CR1_CPHA;
	SPI2->CR1 |= SPI_CR1_CPOL;
	SPI2->CR1 &= ~SPI_CR1_DFF;
	SPI2->CR1 |= SPI_CR1_LSBFIRST;
	SPI2->CR1  |= SPI_CR1_SSM | SPI_CR1_SSI; 
	SPI2->CR1 |= SPI_CR1_MSTR;
	SPI2->CR1  |= SPI_CR1_SPE;  // enable SPI

}

void SpiSendData(uint8_t data)
{
	SPI2->DR = data;
	while((SPI2->SR & SPI_SR_TXE) == RESET){}
}

uint8_t SpiTransceiveByte(uint8_t data)
{
	SPI2->DR = data;
	while ((SPI2->SR & SPI_SR_RXNE) == 0);
	return SPI2->DR;
}

uint8_t SpiReceive()
{
	while((SPI2->SR & SPI_SR_RXNE) == RESET){}
	return SPI2->DR;
}

void SpiCsLow(void)
{
		GPIOB->ODR &= ~GPIO_ODR_ODR12;
}

void SpiCsHigh(void)
{
		GPIOB->ODR |= GPIO_ODR_ODR12;
}
