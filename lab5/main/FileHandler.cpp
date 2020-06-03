#include "FileHandler.h"
#include"FileThreads.h"

FileHandler::FileHandler(char* mainDir_)
{
	this -> subDirsCount = 0;
	this -> mainDir = mainDir_;
}

FileHandler::~FileHandler(void)
{
	
}

bool FileHandler::getDirectories()
{
	return getDirectories(mainDir);
}

bool FileHandler::getDirectories(char* mainDir)
{
	WIN32_FIND_DATA ffd;
	size_t length_of_arg;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	//�������� ������ ����������
	StringCchLength((TCHAR*)mainDir, MAX_PATH, &length_of_arg);
	if (length_of_arg > (MAX_PATH - 3))
	{
		std::cout<<"\nDirectory path is too long.\n";
		return false;
	}
	
	std::cout<<"\nTarget directory is \n"<< mainDir;
	
	//���������� � ������ � findFile. 
	StringCchCopy(szDir, MAX_PATH, (TCHAR*)mainDir);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
	
	// ���������� ������� ����� � ����������
	hFind = FindFirstFile(szDir, &ffd);
	
	if (INVALID_HANDLE_VALUE == hFind) 
	{
		std::cout<<" Error finding first file.\n The program would be terminated";
		return false;
	} 
   
	//����������� ��������� ����������

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!strcmp(ffd.cFileName, ".") || !strcmp(ffd.cFileName, ".."))
			{
				continue;
			}

			std::cout<<"\n	"<<ffd.cFileName;
			strcat(strcat(strcpy(this -> subDirs[subDirsCount], mainDir), "\\"),ffd.cFileName);
			this->subDirsCount++;

			/*if (!getDirectories(subDirs[subDirsCount - 1]))
			{
				return false;
			}*/
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);
 
	//��������� ������ ��� ������ ���� ����������

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) 
	{
		std::cout<<" Error finding first file.\n The program would be terminated";
		return false;
	}

	FindClose(hFind);
	return true;
}

bool FileHandler::getFiles()
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	size_t length_of_arg;
	TCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	

	for(int i = 0; i < subDirsCount; i++)
	{
		//�������� ������ ����������
		StringCchLength((TCHAR*)subDirs[i], MAX_PATH, &length_of_arg);
		if (length_of_arg > (MAX_PATH - 3))
		{
			std::cout<<"\nDirectory path is too long.\n";
			return false;
		}
	
		std::cout<<"\nTarget directory is \n"<< subDirs[i]<<std::endl;
		
		//���������� � ������ � findFile. 
		StringCchCopy(szDir, MAX_PATH, (TCHAR*)subDirs[i]);
		StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
	
		// ���������� ������� ����� � ����������
		hFind = FindFirstFile(szDir, &ffd);

		if (INVALID_HANDLE_VALUE == hFind) 
		{
			return false;
		} 
   
		// List all the files in the directory with some info about them.
		char rootDir[MAX_PATH];
		strcpy(rootDir,subDirs[i]);
		strcat(rootDir,".txt");
		
		FileThreads ft(subDirs[i],rootDir,ffd, hFind);
		
		/*if (GetLastError() != ERROR_NO_MORE_FILES) 
		{
			return false;
		}*/
	}
		FindClose(hFind);
		return true;
}
