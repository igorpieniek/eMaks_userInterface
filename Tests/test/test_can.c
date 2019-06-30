#include "unity.h"
#include "can_frames.h"
#include "joystick.h"
#include "coder.h"
#include "adc.h"
extern can_functions hardware_can;

void setUp(void)
{
}
void tearDown(void)
{
}
void hal_transmit_mock(uint16_t id, uint64_t data){}
void test_fill_joy_data_frame_valid_lenght(void){
	// arrange
	can_message test_msg;
	joystick test_joy;
	uint8_t test_axis_number = 0;

	test_joy.measurements[0].percentage_value = 54.9;
	test_msg.data_lenght = 4;
	// act
	fill_joy_data_frame(&test_msg,&test_joy,test_axis_number);
	// assert


	TEST_ASSERT_EQUAL_UINT64(0x8B8C0000,test_msg.data);

}
void test_fill_joy_data_frame_not_valid_length(void){

}
void test_is_hardware_attached_to_pointers_false(void){
	//arrange
	hardware_can.can_transmit = NULL;

	//act
	// assert
	TEST_ASSERT_EQUAL_UINT8(0,is_hardware_attached_to_pointers());
}
void test_is_hardware_attached_to_pointers_true(void){
	//arrange
	hardware_can.can_transmit = hal_transmit_mock;

	//act
	// assert
	TEST_ASSERT_EQUAL_UINT8(1,is_hardware_attached_to_pointers());
}



