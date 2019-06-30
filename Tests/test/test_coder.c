#include "unity.h"
#include "coder.h"
#include "adc.h"


coding_parameter test_uint16_5_5 ={.bits =16, .offset = 0,.range = 5.5};
coding_parameter test_int16_5_5 = {.bits = 16, .offset = 127,.range =5.5};
void setUp(void)
{
}

void tearDown(void)
{
}
void test_coder_proper_values(void){
	//arrange
	float test_float = 1.51;

	//act
	uint16_t test_result = encode_float_to_uint16(test_float,test_uint16_5_5);
	//assert

	TEST_ASSERT_EQUAL_UINT16(17992,test_result);
}

void test_coder_inproper_values(void){
	//arrange
	float test_float = 6.2;

	//act
	uint16_t test_result = encode_float_to_uint16(test_float,test_uint16_5_5);
	//assert

	TEST_ASSERT_EQUAL_UINT16(0,test_result);
}

void test_encode_frame_big_endian_proper_values(void){
	//arrange
	uint8_t* test_data = (uint8_t[]){0xFF,0xA1,0xB0};
	uint8_t test_data_length = 3;

	//act
	uint64_t test_results = encode_frame_big_endian(test_data,test_data_length);

	//assert
	TEST_ASSERT_EQUAL_UINT32(0xB0A1FF, test_results);
}

void test_encode_frame_big_endian_zero_length_value(void){
	//arrange
	uint8_t* test_data;
	uint8_t test_data_length = 0;

	//act
	uint64_t test_results = encode_frame_big_endian(test_data,test_data_length);

	//assert
	TEST_ASSERT_EQUAL_UINT32(0, test_results);
}

