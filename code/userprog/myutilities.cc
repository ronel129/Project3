// myutilities.cc
//	Method for compare two buffer.
//
//  Created on: 2009-12-11
//      Author: hyper

#include "myutilities.h"

//----------------------------------------------------------------------
// strcmp
// 	Do little endian to big endian conversion on the bytes in the
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//
//	Return TRUE if the "first" char is the same as the "second" char, or
//	  Return FALSE if they are different.
//
//	"first" is the pointer to the char to be compared.
//	"second" is the pointer to the char compared with.
//----------------------------------------------------------------------

bool strcmp(char* first,char * second){

	while((*first)!=0)
	{
		if(*first != *second)
			return false;
		first++;
		second++;
	}
	return *second == 0;
}
