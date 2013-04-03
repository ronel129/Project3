// useropenfile.h
//	Defines UserOpenFile class contains an index into the global SysOpenFile table 

#ifndef USEROPENFILE_H_
#define USEROPENFILE_H_
class UserOpenFile{
public:
	int fileIndex;	//an index into the global SysOpenFile table
	int offset;		//a process's current position in the pointing file.
};

#endif /* USEROPENFILE_H_ */
