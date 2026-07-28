#include "sample.h"

int main(void){
	int r1 = 0;
	int r2 = 0;

	do_one_thing(&r1);
	do_another_thing(&r2);
	do_wrap_up(r1, r2);
	return 0;
}
