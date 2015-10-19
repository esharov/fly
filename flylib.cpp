#include "flylib.hpp"


entry_t Entry;

void VoidFunc() {}


case_m Case;


uint8_t				Stack_Data[Stack_Size];
uint8_t*			Stack_Cur = Stack_Data;
const uint8_t*		Stack_End = &Stack_Data[Stack_Size];


bool Stack_Set(void* p)
{
	if (p >= Stack_Data && p < Stack_End)
	{
		Stack_Cur = (uint8_t*)p;
		return 1;
	}
	return 0;
}

