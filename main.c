/*
 * avrapp1.c
 *
 * Created: 8/31/2023 2:41:38 PM
 * Author : 20115
 */ 

#include "main.h"


pwm_config my_pwm;
push_button_config increment_btn;
push_button_config decrement_btn;
push_button_config change_direction_btn;
gpio_pin_config in1_pin;
gpio_pin_config in2_pin;


gpio_logic increment_btn_logic;
gpio_logic decrement_btn_logic;
gpio_logic change_direction_btn_logic;
int main(void)
{
	uint8 motor_speed=0;
	increment_btn.connection_type=push_button_activ_high;
	increment_btn.push_button_pin.port=portC;
	increment_btn.push_button_pin.pin=pin0;
	increment_btn.push_button_pin.direction=input;
	ecu_push_button_intiallize(&increment_btn);
	
	decrement_btn.connection_type=push_button_activ_high;
	decrement_btn.push_button_pin.port=portC;
	decrement_btn.push_button_pin.pin=pin1;
	decrement_btn.push_button_pin.direction=input;
	ecu_push_button_intiallize(&decrement_btn);
	
	change_direction_btn.connection_type=push_button_activ_high;
	change_direction_btn.push_button_pin.port=portD;
	change_direction_btn.push_button_pin.pin=pin7;
	change_direction_btn.push_button_pin.direction=input;
	ecu_push_button_intiallize(&change_direction_btn);
	
	in1_pin.direction=output;
	in1_pin.port=portA;
	in1_pin.pin=pin0;
	in1_pin.logic=high;
	mcal_gpio_pin_direction_intiallize(&in1_pin);
	mcal_gpio_pin_output_write_logic(&in1_pin,in1_pin.logic);
	
	in2_pin.direction=output;
	in2_pin.port=portA;
	in2_pin.pin=pin1;
	in2_pin.logic=low;
	mcal_gpio_pin_direction_intiallize(&in2_pin);
	mcal_gpio_pin_output_write_logic(&in2_pin,in2_pin.logic);
	
	my_pwm.clock_prescale=no_prescalar;
	my_pwm.mode=pwm_mode;	
	mcal_PWM0_intiallize(&my_pwm);
	
	
    while (1) 
    {
		OCR0=motor_speed;
		_delay_ms(2);
		ecu_push_button_read_logic(&increment_btn,&increment_btn_logic);
		
		ecu_push_button_read_logic(&decrement_btn,&decrement_btn_logic);
		_delay_ms(10);
		if(increment_btn_logic==high)
		{
			motor_speed+=50;
		}
		else if(decrement_btn_logic==high)
		{
			if (OCR0==0)
			{
				motor_speed=0;
			}
			else{
				motor_speed-=50;
			}
		}
		ecu_push_button_read_logic(&change_direction_btn,&change_direction_btn_logic);
		if (change_direction_btn_logic==high)
		{
			mcal_gpio_pin_toggle_logic(&in1_pin);
			mcal_gpio_pin_toggle_logic(&in2_pin);
			_delay_ms(2);
		}
		
	}
}
