// sysopenfile.cc
//	Defines SysOpenFile class that contains a pointer to the file system's OpenFile object
//	and (char *)fileName for that file and the number of user processes currently accessing
//	it. Declare an array of SysOpenFile objects for use by all system calls implemented.
//
//	Defines SysOpenFile Manager class that manage all SysOpenFile.
//
//  Created on: Dec 10, 2009
//      Author: qi

#include "sysopenfile.h"
#include "myutilities.h"

//----------------------------------------------------------------------
// SysOpenFile::closeOne
//	close a SysOpenFile and accessing processes
//----------------------------------------------------------------------

void SysOpenFile::closeOne() {
	if (userOpens <= 0)
		return;
	userOpens--;
	if (userOpens == 0) {
		delete fileName;
		delete file;
	}
}

//----------------------------------------------------------------------
// SysOpenFile::close
//	close all SysOpenFile and accessing processes
//----------------------------------------------------------------------

void SysOpenFile::close() {
	if (userOpens <= 0)
		return;
	userOpens = 0;
	delete fileName;
	delete file;
}

//----------------------------------------------------------------------
// SysOpenFileManager::SysOpenFileManager
//	Initialize a SysOpenFileManager with initialize a bitmap with
//	"SOFILETABLE_SIZE"
//----------------------------------------------------------------------

SysOpenFileManager::SysOpenFileManager() :
	bitMap(SOFILETABLE_SIZE) {
}

//----------------------------------------------------------------------
// SysOpenFileManager::~SysOpenFileManager
//	De-allocate a SysOpenFileManager
//----------------------------------------------------------------------

SysOpenFileManager::~SysOpenFileManager() {

}

//----------------------------------------------------------------------
// SysOpenFileManager::Add
//	Add a SysOpenFile to the array of all SysOpenFile.
//
//	Return the index of the added SysOpenFile
//
//	"soFile" is the SysOpenFile to be added.
//----------------------------------------------------------------------

int SysOpenFileManager::Add(SysOpenFile soFile) {
	int i = bitMap.Find();
	if (i < 0)
		return i;//Fail to add, full
	sysOpenFileTable[i] = soFile;
	return i;
}

//----------------------------------------------------------------------
// SysOpenFileManager::Get
//	Get SysOpenFile by "fileName" and stored its index.
//
//	Return the added SysOpenFile
//
//	"fileName" is the name of the SysOpenFile to get.
//	"index" is the index of the SysOpenFile to get in the array.
//----------------------------------------------------------------------

SysOpenFile* SysOpenFileManager::Get(char* fileName, int& index) 
{
	printf("here");
	for (int i = 2; i < SOFILETABLE_SIZE; i++){
		
		if (bitMap.Test(i) && strcmp(fileName, sysOpenFileTable[i].fileName)) {
			index = i;
			return &sysOpenFileTable[i];
		}
	}
	return NULL;
}

//----------------------------------------------------------------------
// SysOpenFileManager::Get(index)
//	Get SysOpenFile by "index" of the array
//
//	Return the got SysOpenFile if existed, or
//	 Return NULL
//
//	"index" is the number of index in the array to get.
//----------------------------------------------------------------------

SysOpenFile* SysOpenFileManager::Get(int index) {
	if (bitMap.Test(index)) {
		return sysOpenFileTable + index;
	}
	return NULL;
}

//----------------------------------------------------------------------
// SysOpenFileManager::closeOne
//	Close a SysOpenFile by "index" of the array
//
//	"index" is the number of index in the array to get.
//----------------------------------------------------------------------

void SysOpenFileManager::closeOne(int index) {
	ASSERT(bitMap.Test(index));
	sysOpenFileTable[index].closeOne();
	if (sysOpenFileTable[index].userOpens == 0)
		bitMap.Clear(index);
}
