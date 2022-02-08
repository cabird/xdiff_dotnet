#include "xdiff.h"
#include <wtypes.h>


// see https://stackoverflow.com/questions/5308584/how-to-return-text-from-native-c-code
// for why we do this
BSTR ANSItoBSTR(char* input)
{
	BSTR result = NULL;
	int lenA = lstrlenA(input);
	int lenW = MultiByteToWideChar(CP_ACP, 0, input, lenA, NULL, 0);
	if (lenW > 0)
	{
		result = SysAllocStringLen(0, lenW);
		MultiByteToWideChar(CP_ACP, 0, input, lenA, result, lenW);
	}
	return result;
}


// wrap the call to xdl_merge so that it's easier to call frm C# and also to avoid memory leaks.
// xdl_merge allocates a char *buffer and if we convert to a BSTR, then .net knows how to deallocate it
// and avoid a memory leak.
// TODO - make level and style something more than constants
BSTR merge(const char* orig_contents, const char* file1_contents, const char* file2_contents,
	const char* orig_filename, const char* file1_name, const char* file2_name,
	__int32 level, __int32 style)
{
	//TODO - all the error checking on these...
	mmfile_t f_o, f_1, f_2;

	f_o.ptr = orig_contents;
	f_o.size = strlen(orig_contents);

	f_1.ptr = file1_contents;
	f_1.size = strlen(file1_contents);

	f_2.ptr = file2_contents;
	f_2.size = strlen(file2_contents);

	mmbuffer_t out_buffer;
	xmparam_t params;
	params.ancestor = orig_filename;
	params.file1 = file1_name;
	params.file2 = file2_name;
	params.style = style;
	params.level = level;
	params.favor = 0;

	xdl_merge(&f_o, &f_1, &f_2, &params, &out_buffer);

	// the out_buffer is not null terminated, so allocate a string one byte longer,
	// copy out_buffer to it, and null_terminate it.
	// this isn't the most efficient, but it's safe and it's C, so I don't care.
	char* tmp_buf = (char*)malloc(out_buffer.size + 1);
	strncpy_s(tmp_buf, out_buffer.size + 1, out_buffer.ptr, out_buffer.size);
	tmp_buf[out_buffer.size] = '\0';
	


	BSTR result = ANSItoBSTR(tmp_buf);

	//deallocate things;
	if (out_buffer.ptr != NULL)
	{
		xdl_free(out_buffer.ptr);
		out_buffer.ptr = NULL;
		out_buffer.size = 0;
	}
	free(tmp_buf);
	
	return result;
}



