#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <iostream>
#include <strsafe.h>
#include "FileHandler.h"

void DisplayErrorBox(LPTSTR lpszFunction);

int _tmain(int argc, TCHAR *argv[])
{
	char directory[] = {"A:\\TEST"};
	FileHandler fh(directory);
	
	if(!fh.getDirectories())
	{
		std::cout<<"\nError in operation with files 1\n";
		std::cin.get();
		return -1;
	}
	if(!fh.getFiles())
	{
		std::cout<<"\nError in operation with files 2\n";
		std::cin.get();
		return -1;
	}
	std::cout<<"\n\ndirsCount = "<<fh.subDirsCount;
	
	std::cin.get();
	return 0;
}