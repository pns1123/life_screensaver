// ROADMAP
// 1) write tests
// 2) simplify parser:
//    - use max to merge conditional cases
//    - goal 1: only write through function
//    - goal 2: invoke write function from as few distinct positions as possible
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void write_k(bool *arr, bool literal, int k){
	for(int i=0; i<k; ++i){
		arr[i] = literal;
	}
}


int grid_pos(int row_index, int col_index, int H_LEN){
	return row_index * H_LEN + col_index;
}

bool literal2flag(char literal){
	switch (literal){
		case 'b': return true; break;
	        case 'o': return false; break;
	        //default: return false; break;
	}
}

int main()
{
    char *filename = "test.rle";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    int H_LEN, V_LEN;
    char rule[10];
    fscanf(fp, "x = %d, y = %d, rule = %s", &H_LEN, &V_LEN, rule);
    printf("x = %d, y = %d \n\n", H_LEN, V_LEN);
    // read one character at a time and
    // display it to the output

    bool GRID[H_LEN * V_LEN];
    int row_index = 0;
    int col_index = 0;
    int block_len = 0;
    int char_digit;
    char last_literal;

    char c;
    block_len = 0;
    while ((c = fgetc(fp)) != EOF)
    {
	printf("%d, %d\n", col_index, H_LEN);
	if(c == '\n'){
		continue;
	} 
	else if (c == '$' || c == '!'){
		if (col_index < H_LEN-1){
			last_literal = GRID[grid_pos(row_index, col_index, H_LEN)-1];

			printf("write %c from pos. %d to %d\n", 
			       literal2flag(last_literal),
			       grid_pos(row_index, col_index, H_LEN), 
			       grid_pos(row_index, col_index, H_LEN) + H_LEN-col_index);
			write_k(&GRID[grid_pos(row_index, col_index, H_LEN)],
			        literal2flag(last_literal), 
				H_LEN- col_index );
			//write H_LEN-1-col_index of previous symbol
		}
		col_index = 0;
		row_index += 1;
		assert(row_index <= V_LEN);
	}
    	else if(c == 'b'){
		if (block_len==0){
			printf("write X to pos. %d\n", grid_pos(row_index, col_index, H_LEN));
			GRID[grid_pos(row_index, col_index, H_LEN)] = true;
			col_index += 1;
		} else {
			printf("write X from pos. %d to %d\n", 
			       grid_pos(row_index, col_index, H_LEN), 
			       grid_pos(row_index, col_index, H_LEN)+block_len);
			write_k(&GRID[grid_pos(row_index, col_index, H_LEN)],
			        true, 
				block_len );
			col_index += block_len;
			block_len = 0;
		}
		//printf("CHECK: col_index = %d, block_len = %d, sum= %d\n", col_index, block_len, col_index + block_len);
		assert(col_index <= H_LEN);
	}
	else if(c == 'o'){

		if (block_len==0){
			printf("write O to pos. %d\n", grid_pos(row_index, col_index, H_LEN));
			GRID[grid_pos(row_index, col_index, H_LEN)] = false;
			col_index += 1;
		} else {
			printf("write O from pos. %d to %d\n", 
			       grid_pos(row_index, col_index, H_LEN), 
			       grid_pos(row_index, col_index, H_LEN));
			write_k(&GRID[grid_pos(row_index, col_index, H_LEN)],
			        false, 
				block_len );
			//printf("CHECK: col_index = %d, block_len = %d, sum= %d\n", col_index, block_len, col_index + block_len);
			col_index += block_len;
			block_len = 0;
		}
		assert(col_index <= H_LEN);
	}
	else if(isdigit(c)){
		char_digit = (int)(c-'0');
		block_len = block_len * 10 + (unsigned char)char_digit;	
	}
	else {
        	break;
	}
    }

    // print linear view of grid
    for (int i=0; i<V_LEN; ++i){
	    for (int j=0; j<H_LEN; ++j){
	    	putchar(GRID[i * H_LEN + j] ? 'X' : 'O');
	    }
	    putchar('\n');
    }
    putchar('\n');
    return 0;
}

