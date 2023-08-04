#include <assert.h>
#include<stdio.h>

#include "src/life.c"

#define H_LEN 4
#define V_LEN 3

// initialize test grid as global variable
bool GRID[H_LEN * V_LEN] = { false, true, true, false,
                             true,  false, true, false, 
                             false, true, false, true };

void print_grid(bool *grid, size_t h_len, size_t v_len){
	for(size_t i=0; i<v_len; ++i){	
		for(size_t j=0; j<h_len; ++j){	
			if(grid[i*h_len + j]){
				printf("X ");
			} else {
				printf("O ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

bool test_moore_sum_index0(){
	return ( sum_moore_neighboorhood(GRID, 0, H_LEN, V_LEN) == 2 );	
}

bool test_moore_sum_index1(){
	return ( sum_moore_neighboorhood(GRID, 1, H_LEN, V_LEN) == 3 );	
}

bool test_moore_sum_index2(){
	return ( sum_moore_neighboorhood(GRID, 2, H_LEN, V_LEN) == 2 );	
}

bool test_moore_sum_index3(){
	return ( sum_moore_neighboorhood(GRID, 3, H_LEN, V_LEN) == 2 );	
}

bool test_moore_sum_index4(){
	return ( sum_moore_neighboorhood(GRID, 4, H_LEN, V_LEN) == 2 );	
}

bool test_moore_sum_index5(){
	return ( sum_moore_neighboorhood(GRID, 5, H_LEN, V_LEN) == 5 );	
}

bool test_moore_sum_index6(){
	return ( sum_moore_neighboorhood(GRID, 6, H_LEN, V_LEN) == 4 );	
}

bool test_moore_sum_index7(){
	return ( sum_moore_neighboorhood(GRID, 7, H_LEN, V_LEN) == 3 );	
}

bool test_moore_sum_index8(){
	return ( sum_moore_neighboorhood(GRID, 8, H_LEN, V_LEN) == 2 );	
}

bool test_moore_sum_index9(){
	return ( sum_moore_neighboorhood(GRID, 9, H_LEN, V_LEN) == 2 );	
}

bool test_moore_sum_index10(){
	return ( sum_moore_neighboorhood(GRID, 10, H_LEN, V_LEN) == 3 );	
}

bool test_moore_sum_index11(){
	return ( sum_moore_neighboorhood(GRID, 11, H_LEN, V_LEN) == 1 );	
}

bool test_update_index7(){
	bool next_gen_grid[H_LEN * V_LEN];
	update_grid(GRID, next_gen_grid, H_LEN*V_LEN, H_LEN, V_LEN); 
	print_grid(next_gen_grid, H_LEN, V_LEN);
	return ( next_gen_grid[7] == true );
}

int main(){

	// display grid
	printf("TESTGRID: \n");
	print_grid(GRID, H_LEN, V_LEN);

	bool (*tests[])() = { 
		test_moore_sum_index0,
                test_moore_sum_index1, 	
                test_moore_sum_index2, 	
                test_moore_sum_index3, 	
                test_moore_sum_index4, 	
                test_moore_sum_index5, 	
                test_moore_sum_index6, 	
                test_moore_sum_index7, 	
                test_moore_sum_index8, 	
                test_moore_sum_index9, 	
                test_moore_sum_index10, 	
	        test_moore_sum_index11,
		test_update_index7,
	};

	printf("RUNNING %zu TESTS...\n", sizeof(tests)/sizeof(tests[0]));
	for( size_t i=0; i<sizeof(tests)/sizeof(tests[0]); ++i){
		assert(tests[i]());
		printf("TEST %zu PASSED\n", i+1);
	}
		
    	size_t x_index, y_index;
    	for(size_t grid_index=0; grid_index<H_LEN*V_LEN; ++grid_index){
       		x_index = grid_index2x_index(grid_index, H_LEN, V_LEN);
       		y_index = grid_index2y_index(grid_index, H_LEN, V_LEN);
		printf("(%zu, %zu) \n", x_index, y_index);

       }
}
