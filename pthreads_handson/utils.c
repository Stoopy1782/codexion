void do_one_thing(int *pnum_times)
{
	int i, j, x;
	for (i=0; i<4; i++)
	{
		printf("doing one thing\n");
		for (j=0; j < 10000; j++)
		{
			x = x + i;
			(*pnum_times)++;
		}
	}
}
void do_another_thing(int *pnum_times)
{
	int i, j, x;
	for (i=0; i<4; i++)
	{
		printf("doing another\n");
		for (j=0; j < 10000; j++)
		{
			x = x + i;
			(*pnum_times)++;
		}
	}
}
void do_wrap_up(int one_times, int another_times){
	int total;

	total = one_times + another_times;
	printf("All done, one thing %d, another %d for a total of %d\n", one_times, another_times, total);
}
