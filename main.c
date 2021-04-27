#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/iom8.h>
#include <util/delay.h>
#include <stdio.h>
#include "avr-ds18b20-master/include/ds18b20/ds18b20.h"
#include <avr/interrupt.h>
#define START_MOTOR  PORTB |= (1<<PB0)
#define STOP_MOTOR   PORTB &= ~(1<<PB0)
#define LED_UP       PORTD |= (1<<PD0)
#define LED_DOWN     PORTD &= ~(1<<PD0)
#define GOOD_POWER   PORTD |= (1<<PD1)
#define FAIL_POWER   PORTD &= ~(1<<PD1)
//********************************//
uint16_t get_ADC();
uint16_t get_Limit(float voltage, uint8_t maxTemp, float ref);
uint16_t get_Temperature();
float calcVoltage(uint16_t adc, float ref, uint16_t ADC_CONST);
void startConvertion();
void initMCU();
//********************************//

int main(void){
//*******************************//
float voltage;
const float ref_voltage = 3.75;
const uint8_t maxTemp = 125;
const uint16_t ADC_CONST = 1024;
uint16_t temp_limit;
uint16_t adc_result;
uint16_t temp;
//*******************************//
initMCU();
while(1){
     temp = get_Temperature()/16;
     startConvertion();
     while(ADCSRA & (1<<ADSC));
     adc_result = get_ADC();
     voltage = calcVoltage(adc_result, ref_voltage, ADC_CONST);
     temp_limit = get_Limit(voltage, maxTemp, ref_voltage) ;
     if(temp > temp_limit){
    	 START_MOTOR;
    	 LED_UP;
    	 FAIL_POWER;
     }else if(temp < (temp_limit -15)){
    	 STOP_MOTOR;
    	 LED_DOWN;
    	 GOOD_POWER;
     }
}
return 0;
}
//*************************************************//
uint16_t get_ADC(){
	return (uint16_t) ADC;
}
//*************************************************//
float calcVoltage(uint16_t adc, float ref, uint16_t ADC_CONST){
	return ((adc * ref)/ADC_CONST);
}
//*************************************************//
void startConvertion(){
	ADCSRA |= (1<<ADSC);
}
//*************************************************//
uint16_t get_Limit(float voltage, uint8_t maxTemp, float ref){
	return ((uint16_t)((voltage * maxTemp)/ref));
}
//*************************************************//
void initMCU(){
	DDRD = 0x03;
	DDRC = 0x00;
	DDRB = 0x01; //motor gate
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}
//*************************************************//
 uint16_t get_Temperature(){
	uint16_t a;
	ds18b20convert( &PORTB, &DDRB, &PINB, ( 1 << 6 ), NULL );
	_delay_ms( 1000 );
	ds18b20read( &PORTB, &DDRB, &PINB, ( 1 << 6 ), NULL, &a );
	return a;
}
//*************************************************//







