#define _CRT_SECURE_NO_WARNINGS          
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

struct PAGE {
	int memory_location;
	int valid_bit;
};
struct MEMORY {
	int page_num;
	int reference_bit;
	int dirty_bit;
};
struct PAGE page[200000];
int main(int argc, char *argv[]) {
	int memory_size = atoi(argv[1]);
	FILE *input_file = fopen("a.txt", "r");

	struct MEMORY *memory = (struct MEMORY*)malloc(memory_size * sizeof(struct MEMORY));
	int i;
	int page_fault_count = 0;
	int disk_write_count = 0;
	int disk_moving_dist = 0;

	int clock = 0, empty = 0;
	int head = 0, new_head = 0;
	int exit_pg;

	for (i = 0; i < memory_size; i++) {
		memory[i].reference_bit = 0;
		memory[i].dirty_bit = 0;
	}
	for (i = 0; i < 200000; i++) page[i].valid_bit = 0;
	while (!feof(input_file)) {
		int pg, op;
		fscanf(input_file, "%d %d", &pg, &op);

		if (page[pg].valid_bit == 1) {
			memory[page[pg].memory_location].reference_bit = 1;
			if (op == 1)memory[page[pg].memory_location].dirty_bit = 1;
		}
		else {
			page_fault_count++;

			if (empty >= memory_size) {
				while (1) {
					if (memory[clock].reference_bit == 1) {
						memory[clock].reference_bit = 0;
					}
					else if (memory[clock].reference_bit == 0) {
						exit_pg = clock;
						break;
					}
					clock++;
					if (clock >= memory_size) clock = 0;
				}
				page[memory[exit_pg].page_num].valid_bit = 0;
				if (memory[exit_pg].dirty_bit == 1) {
					disk_write_count++;
					new_head = memory[exit_pg].page_num / 1000;
					disk_moving_dist += abs(new_head - head);
					head = new_head;
				}
			}
			empty++;
			new_head = pg / 1000;
			disk_moving_dist += abs(new_head - head);
			head = new_head;
			memory[clock].page_num = pg;
			if (op == 1) memory[clock].dirty_bit = 1;
			else if (op == 0) memory[clock].dirty_bit = 0;
			memory[clock].reference_bit = 0;
			page[pg].memory_location = clock;
			page[pg].valid_bit = 1;
			clock++;
			if (clock >= memory_size) {
				clock = 0;
			}
		}
	}
	printf("%d\n", page_fault_count);
	printf("%d\n", disk_write_count);
	printf("%d\n", disk_moving_dist);

}