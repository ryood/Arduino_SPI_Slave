/*
 * SPI_Slave_LEDx8.c
 *
 * Created: 2017/08/26 9:16:53
 * Author : gizmo
 */ 

#define F_CPU	(8000000UL)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t sdata = 0;

ISR (SPI_STC_vect)
{
	// 受信データをLEDに出力
	PORTD = SPDR;
	
	// 次に送信するデータをセット
	SPDR = sdata;
	sdata++;
}

int main(void)
{
	// LEDs output
	DDRD = 0xFF;
	PORTD = 0xFF;
	_delay_ms(100);

	// LEDs check
	for (int i = 0; i < 8; i++) {
		PORTD = 1 << i;
		_delay_ms(100);
	}
	PORTD = 0x00;

	// SPI slave
	DDRB = 0x10;  // MISO(PB4)をoutputに設定

	// SPCRのビット設定
	// SPI有効:1 | SPI割り込み有効:1 | MSBから送信:0 | スレーブ:0
	// クロック極性:0 | クロック位相:0 | SPR1:0 | SPR0:0
	SPCR = (1 << SPIE) | (1 << SPE);

	sei();	// 割り込み許可
	
	while (1)
	{
	}
}



