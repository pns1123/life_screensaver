// https://medium.com/@savas/template-metaprogramming-compile-time-loops-over-class-methods-a243dc346122
#include <assert.h>
#include <stdio.h>

#include "../src/parser.c"
#include "utils.c"

#define TEST_CASE(TEST_NAME, FILENAME, HORIZONTAL, VERTICAL, REFERENCE_ARR)    \
bool TEST_NAME() {                                                             \
	struct GridSize grid_size = parse_grid_size(FILENAME);                 \
                                                                               \
	if  (grid_size.horizontal != HORIZONTAL ||                             \
	     grid_size.vertical != VERTICAL){                                  \
		return false;                                                  \
	}                                                                      \
                                                                               \
	bool pattern_arr[HORIZONTAL * VERTICAL];                               \
	parse_pattern(FILENAME, pattern_arr, HORIZONTAL, VERTICAL);            \
                                                                               \
	return bool_array_equal(REFERENCE_ARR, pattern_arr,                    \
			        grid_size.horizontal * grid_size.vertical);    \
}                                                                              \


bool reference_arr1[1 * 1] = {true};
TEST_CASE(test1, "tests/test_patterns/test1.rle", 1, 1, reference_arr1)

bool reference_arr2[1 * 1] = {false};
TEST_CASE(test2, "tests/test_patterns/test2.rle", 1, 1, reference_arr2)

bool reference_arr3[5 * 1] = {false, true, false, false, true};
TEST_CASE(test3, "tests/test_patterns/test3.rle", 5, 1, reference_arr3)

bool reference_arr4[5 * 1] = {false, true, false, false, true};
TEST_CASE(test4, "tests/test_patterns/test4.rle", 5, 1, reference_arr4)

bool reference_arr5[5 * 1] = {false, false, false, false, false};
TEST_CASE(test5, "tests/test_patterns/test5.rle", 5, 1, reference_arr5)

bool reference_arr6[5 * 1] = {false, true, true, true, true};
TEST_CASE(test6, "tests/test_patterns/test6.rle", 5, 1, reference_arr6)

bool reference_arr7[5 * 1] = {true, true, true, true, true};
TEST_CASE(test7, "tests/test_patterns/test7.rle", 5, 1, reference_arr7)

bool reference_arr8[5 * 2] = {false, false, false, false, false, 
	                      true, true, true, true, true};
TEST_CASE(test8, "tests/test_patterns/test8.rle", 5, 2, reference_arr8)

bool reference_arr9[2 * 4] = {false, true, 
	                      true, true, 
			      true, false, 
			      false, false};
TEST_CASE(test9, "tests/test_patterns/test9.rle", 2, 4, reference_arr9)

bool reference_arr10[4 * 4] = {true, true, true, true, 
	                      false, true, true, true, 
                              false, false, true, true, 
                              false, false, false, true};
TEST_CASE(test10, "tests/test_patterns/test10.rle", 4, 4, reference_arr10)

bool reference_arr11[3 * 3] = {false, true, false,
	                       false, false, true, 
			       true, true, true};
TEST_CASE(test11, "tests/test_patterns/test11_glider.rle", 3, 3, reference_arr11)

bool reference_arr12[5*5] = {false, false, false, false, false,
			     false, false, true, false, false,
                             false, false, false, true, false,
                             false, true, true, true, false,
                             false, false, false, false, false};

bool test_initialization(){

	unsigned int NOF_HORIZONTAL_BOXES = 5;
	unsigned int NOF_VERTICAL_BOXES = 5;

	bool grid[5 * 5] = { false };

	char *filename = "/home/philipp/.life_patterns/glider.rle";

	struct GridSize pattern_size = parse_grid_size(filename);                 
                                                                               
	bool pattern_arr[pattern_size.vertical * pattern_size.horizontal];                               
	parse_pattern(filename, pattern_arr, pattern_size.horizontal, 
		      pattern_size.vertical); 

	initialize_grid(grid, NOF_HORIZONTAL_BOXES, NOF_VERTICAL_BOXES,
	                pattern_arr, 
			pattern_size.horizontal, pattern_size.vertical);

	return bool_array_equal(reference_arr12, grid,                    
			        NOF_HORIZONTAL_BOXES * NOF_VERTICAL_BOXES);    


}

int main() {

	bool (*tests[])() = {test1, 
		             test2, 
			     test3, 
			     test4,
	                     test5,
	                     test6,
	                     test7,
	                     test8,
	                     test9,
	                     test10,
	                     test11,
			     test_initialization};



	set_purple();
	set_bold();
	printf("TESTING src/parser.c: RUNNING %zu TESTS...\n", sizeof(tests) / sizeof(tests[0]));
	reset_printf();
	for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i) {
		if (tests[i]()) {
			set_green();
			printf("TEST %2zu PASSED\n", i + 1);
			reset_printf();
		} else {
			set_red();
			printf("TEST %2zu FAILED\n", i + 1);
			reset_printf();
		}
	}

	//bool pattern_arr[2 * 4];                               
	//parse_pattern("tests/test_patterns/test9.rle", pattern_arr, 2, 4);            
	//for(unsigned int i=0; i<8; ++i){
	//	putchar(pattern_arr[i] ? 'X' : 'O');
	//}
	//putchar('\n');

}

