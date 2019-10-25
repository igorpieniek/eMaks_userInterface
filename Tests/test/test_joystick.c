#include "unity.h"
#include "joystick.h"
#include "adc.h"

joystick* test_joy;


/*tested for conditions (joystic.h)
#define V_NEUTRAL_X_AXIS 2.1f
#define V_NEUTRAL_Y_AXIS 2.1f
#define V_MAX_X_AXIS     3.0f
#define V_MIN_X_AXIS     1.2f
#define V_MAX_Y_AXIS     3.0f
#define V_MIN_Y_AXIS     1.2f
#define MEASUREMENT_ERROR 0.06f
 */

void setUp(void)
{

}

void tearDown(void)
{
	test_joy->measurements[0].raw_data = 0;
	test_joy->measurements[0].converted_data= 0.0;
	test_joy->measurements[1].raw_data = 0;
	test_joy->measurements[1].converted_data= 0.0;
}
void test_init(void){
	joy_params_init();
	test_joy = get_joy_pointer();
}

void test_calculate_joy_data_x_y_zeros(void){
	// arrange
	test_joy->measurements[X_AXIS_INDEX].converted_data = 2.12;
	test_joy->measurements[Y_AXIS_INDEX].converted_data = 2.12;

	//act
	calculate_joy_data();

	//assert
	TEST_ASSERT_TRUE(test_joy->measurements[X_AXIS_INDEX].sign);
	TEST_ASSERT_TRUE(test_joy->measurements[Y_AXIS_INDEX].sign);
	TEST_ASSERT_EQUAL_FLOAT(0.0, test_joy->measurements[X_AXIS_INDEX].percentage_value);
	TEST_ASSERT_EQUAL_FLOAT(0.0, test_joy->measurements[Y_AXIS_INDEX].percentage_value);

}

void test_calculate_joy_data_x_y_max(void){
	// arrange
	test_joy->measurements[X_AXIS_INDEX].converted_data = 3.0;
	test_joy->measurements[Y_AXIS_INDEX].converted_data = 3.0;

	//act
	calculate_joy_data();

	//assert
	TEST_ASSERT_TRUE(test_joy->measurements[X_AXIS_INDEX].sign);
	TEST_ASSERT_TRUE(test_joy->measurements[Y_AXIS_INDEX].sign);
	TEST_ASSERT_FLOAT_WITHIN(0.2,100.0, test_joy->measurements[X_AXIS_INDEX].percentage_value);
	TEST_ASSERT_FLOAT_WITHIN(0.2,100.0, test_joy->measurements[Y_AXIS_INDEX].percentage_value);
}


void test_calculate_joy_data_x_y_positive(void){
	// arrange
	test_joy->measurements[X_AXIS_INDEX].converted_data = 2.3;
	test_joy->measurements[Y_AXIS_INDEX].converted_data = 2.8;

	//act
	calculate_joy_data();

	//assert
	TEST_ASSERT_TRUE(test_joy->measurements[X_AXIS_INDEX].sign);
	TEST_ASSERT_TRUE(test_joy->measurements[Y_AXIS_INDEX].sign);
	TEST_ASSERT_FLOAT_WITHIN(0.2,22.22, test_joy->measurements[X_AXIS_INDEX].percentage_value);
	TEST_ASSERT_FLOAT_WITHIN(0.2,77.77, test_joy->measurements[Y_AXIS_INDEX].percentage_value);
}

void test_calculate_joy_data_x_y_negative(void){
	// arrange
	test_joy->measurements[X_AXIS_INDEX].converted_data = 1.8;
	test_joy->measurements[Y_AXIS_INDEX].converted_data = 1.3;

	//act
	calculate_joy_data();

	//assert
	TEST_ASSERT_FALSE(test_joy->measurements[X_AXIS_INDEX].sign);
	TEST_ASSERT_FALSE(test_joy->measurements[Y_AXIS_INDEX].sign);
	TEST_ASSERT_FLOAT_WITHIN(0.2,33.33, test_joy->measurements[X_AXIS_INDEX].percentage_value);
	TEST_ASSERT_FLOAT_WITHIN(0.2,88.88, test_joy->measurements[Y_AXIS_INDEX].percentage_value);
}

void test_calculate_joy_data_x_negative_y_positive(void){
	// arrange
	test_joy->measurements[X_AXIS_INDEX].converted_data = 2.9;
	test_joy->measurements[Y_AXIS_INDEX].converted_data = 1.76;

	//act
	calculate_joy_data();

	//assert
	TEST_ASSERT_TRUE(test_joy->measurements[X_AXIS_INDEX].sign);
	TEST_ASSERT_FALSE(test_joy->measurements[Y_AXIS_INDEX].sign);
	TEST_ASSERT_FLOAT_WITHIN(0.2,88.88, test_joy->measurements[X_AXIS_INDEX].percentage_value);
	TEST_ASSERT_FLOAT_WITHIN(0.2,37.77, test_joy->measurements[Y_AXIS_INDEX].percentage_value);

}

void test_calculate_joy_data_y_negative_x_positive(void){
	// arrange
	test_joy->measurements[X_AXIS_INDEX].converted_data = 1.59;
	test_joy->measurements[Y_AXIS_INDEX].converted_data = 2.79;

	//act
	calculate_joy_data();

	//assert
	TEST_ASSERT_FALSE(test_joy->measurements[X_AXIS_INDEX].sign);
	TEST_ASSERT_TRUE(test_joy->measurements[Y_AXIS_INDEX].sign);
	TEST_ASSERT_FLOAT_WITHIN(0.2,56.66, test_joy->measurements[X_AXIS_INDEX].percentage_value);
	TEST_ASSERT_FLOAT_WITHIN(0.2,76.66, test_joy->measurements[Y_AXIS_INDEX].percentage_value);
}


