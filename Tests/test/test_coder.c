#include "unity.h"
#include "coder.h"
#include "adc.h"


coding_parameter test_uint16_128 ={.bits =16, .offset = 0,.range = 128};
coding_parameter test_int16_5_5 = {.bits = 16, .offset = 127,.range =5.5};
void setUp(void)
{
}

void tearDown(void)
{
}
void test_coder_proper_values(void){
	//arrange
	float test_float = 78.0;

	//act
	uint16_t test_result = encode_float_to_uint16(test_float,test_uint16_128);
	//assert

	TEST_ASSERT_EQUAL_UINT16(39936,test_result);
}

void test_coder_inproper_values(void){
	//arrange
	float test_float = 150.0;

	//act
	uint16_t test_result = encode_float_to_uint16(test_float,test_uint16_128);
	//assert

	TEST_ASSERT_EQUAL_UINT16(0,test_result);
}

void test_encode_frame_big_endian_proper_values(void){
	//arrange
	uint8_t* test_data = (uint8_t[]){0xFF,0xA1,0xB0};
	uint8_t test_data_length = 3;

	//act
	uint8_t* test_results = encode_frame_big_endian(test_data,test_data_length);
	//assert
	TEST_ASSERT_EQUAL_HEX(0xB0, test_results[0]);
	TEST_ASSERT_EQUAL_HEX(0xA1, test_results[1]);
	TEST_ASSERT_EQUAL_HEX(0xFF, test_results[2]);
	free(test_results);
}

void test_encode_frame_big_endian_zero_length_value(void){
	//arrange
	uint8_t* test_data;
	uint8_t test_data_length = 0;

	//act
	uint64_t test_results = encode_frame_big_endian(test_data,test_data_length);

	//assert
	TEST_ASSERT_NULL(test_results);
}

