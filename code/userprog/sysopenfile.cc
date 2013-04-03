#include "sysopenfile.h"
#include "utilities.h"

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
//----------------------------------------------------------------------

SysOpenFileManager::SysOpenFileManager() :
	bitMap(SOFILETABLE_SIZE) {
}

SysOpenFileManager::~SysOpenFileManager() {

}

//----------------------------------------------------------------------
// SysOpenFileManager::Add
//	Add a SysOpenFile to the array of all SysOpenFile.
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
//----------------------------------------------------------------------

SysOpenFile* SysOpenFileManager::Get(char* fileName, int& index) 
{
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
//----------------------------------------------------------------------

void SysOpenFileManager::closeOne(int index) {
	ASSERT(bitMap.Test(index));
	sysOpenFileTable[index].closeOne();
	if (sysOpenFileTable[index].userOpens == 0)
		bitMap.Clear(index);
}
