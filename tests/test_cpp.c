#define TEST_CASE(SIZE_TEST_NAME, PATTEN_TEST_NAME,                            \
                  FILENAME, HORIZONTAL, VERTICAL, REFERENCE_ARR)               \
bool SIZE_TEST_NAME() {                                                        \
	struct GridSize grid_size = parse_grid_size(FILENAME);                 \
	return (grid_size.horizontal = HORIZONTAL &&                           \
	       grid_size.vertical == VERTICAL);                                \
}                                                                              \
                                                                               \
bool PATTERN_TEST_NAME() {                                                     \
	struct GridSize grid_size = parse_grid_size(FILENAME);                 \
                                                                               \
	bool reference_arr[HORIZONTAL * VERTICAL]  = REFERENCE_ARR;            \
                                                                               \
	bool pattern_arr[HORIZONTAL * VERTICAL];                               \
	parse_pattern(FILENAME, pattern_arr, HORIZONTAL, VERTICAL);            \
                                                                               \
	return bool_array_equal(reference_arr, pattern_arr,                    \
			        grid_size.horizontal * grid_size.vertical);    \
} \


TEST_CASE(test_size1, test_grid1, "test/test_patterns/test1.rle", 1, 1, {false})
