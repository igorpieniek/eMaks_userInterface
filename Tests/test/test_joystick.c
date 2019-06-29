#include "unity.h"
#include "joystick.h"
#include "adc.h"

joystick test_joy ={
		.reference_voltage = 3.3,
		.bit_resolution = 12
};

void setUp(void)
{
		test_joy.measurements[0].raw_data = 0;
		test_joy.measurements[0].converted_data= 0.0;
		test_joy.measurements[1].raw_data = 0;
		test_joy.measurements[1].converted_data= 0.0;

}

void tearDown(void)
{
}

void test_get_adc_data(void){
	// arrange
	uint32_t test_data[]={3421,898};

	// act
	get_adc_data(&test_joy,test_data);

	// assert

	TEST_ASSERT_EQUAL_UINT32(3421,test_joy.measurements[0].raw_data);
	TEST_ASSERT_EQUAL_UINT32(898,test_joy.measurements[1].raw_data);
}


void test_convert_adc_values_normal_case(void){
	// arrange
	uint32_t test_data[]={3421,898};

	// act
	convert_adc_value(&test_joy,test_data);

	//assert
	TEST_ASSERT_FLOAT_WITHIN(0.1, 2.75, test_joy.measurements[0].converted_data);
	TEST_ASSERT_FLOAT_WITHIN(0.1, 0.72, test_joy.measurements[1].converted_data);

}

void test_calculate_percentages_voltage_percentage_in_range(void){
	//arrange
	test_joy.measurements[0].converted_data = 3.0;
	test_joy.measurements[1].converted_data = 0.2;

	// act
	calculate_percentages_voltage(&test_joy);

	// assert
	TEST_ASSERT_FLOAT_WITHIN(0.1, 90.9, test_joy.measurements[0].percentage_value);
	TEST_ASSERT_FLOAT_WITHIN(0.1, 6.06, test_joy.measurements[1].percentage_value);
}

void test_calculate_percetage_voltage_percentage_over_scale(void){
	//arrange
	test_joy.measurements[0].converted_data = 5.0;
	test_joy.measurements[1].converted_data = 4,2;

	// act
	calculate_percentages_voltage(&test_joy);

	// assert
	TEST_ASSERT_EQUAL_FLOAT( 100.0, test_joy.measurements[0].percentage_value);
	TEST_ASSERT_EQUAL_FLOAT( 100.0, test_joy.measurements[1].percentage_value);
}

