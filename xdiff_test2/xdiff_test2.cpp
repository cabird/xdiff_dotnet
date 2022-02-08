// xdiff_test2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "xdiff.h"

int main()
{
	std::cout << "size of int is " << sizeof(int);
	
	for (int i = 0; i < 1000 * 1000; i++)
	{ 
	char str_o[] = "I\nlike\nlooking\nat\nthose\ntraffic\nlights\n";
	char str_a[] = "I\nlove\nlooking\nat\nthose\ntraffic\nlightsasdf\n";
	char str_b[] = "I\nhate\nlooking\nat\nthose\ntraffic\ncameras\n";

	mmfile_t f_o, f_a, f_b;

	f_o.ptr = str_o;
	f_o.size = strlen(str_o);

	f_a.ptr = str_a;
	f_a.size = strlen(str_a);

	f_b.ptr = str_b;
	f_b.size = strlen(str_b);

	mmbuffer_t out_buffer;

	xmparam_t params;
	params.ancestor = "o";
	params.file1 = "a";
	params.file2 = "b";
	params.style = XDL_MERGE_DIFF3;
	params.level = XDL_MERGE_ZEALOUS;
	params.favor = 0;

	std::cout << "running merge" << std::endl;
	xdl_merge(&f_o, &f_a, &f_b, &params, &out_buffer);

	char *output2; 
	output2 = (char *)malloc(out_buffer.size + 1);
	strncpy_s(output2, out_buffer.size+1, out_buffer.ptr, out_buffer.size);
	output2[out_buffer.size] = '\0';

	std::cout << output2;
	std::cout << "\nHello World!\n";
}
