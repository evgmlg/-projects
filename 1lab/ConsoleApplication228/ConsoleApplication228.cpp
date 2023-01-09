#include <iostream>
using namespace std;

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>

void listDirecrtory(LPCWSTR path);
void createDir(LPCWSTR path2);
void createFile(LPCWSTR path3);
void deleteDir(LPCWSTR path4);
void deleteFile(LPCWSTR path5);
void copyFile(LPCWSTR path6, LPCWSTR path7);
void moveFile(LPCWSTR path8, LPCWSTR path9);

int _tmain()
{	
	int input;
	wcout <<"1. List Directory" << endl;
	wcout <<"2. Create Directory" << endl;
	wcout <<"3. Create File" << endl;
	wcout <<"4. Delete Directory" << endl;
	wcout <<"5. Delete File" << endl;
	wcout <<"6. Copy File" << endl;
	wcout <<"7. Move File" << endl;

	cin >> input;

	switch (input){
	case 1:
		wchar_t firstDir[MAX_PATH];
		wcout << "1stDirectory: " << endl;
		wchar_t secondDir[MAX_PATH];
		wcout << "2ndDirectory: " << endl;
		wcin >> firstDir;
		wcin >> secondDir;
		listDirecrtory(firstDir);
		listDirecrtory(secondDir);
		break;
	case 2:
		wchar_t Dir[MAX_PATH];
		wcout << "Write Directory: " << endl;
		wcin >> Dir;
		createDir(Dir);
		break;
	case 3:
		wchar_t File1[MAX_PATH];
		wcout << "Name File: " << endl;
		wcin >> File1;
		createFile(File1);
		break;
	case 4:
		wchar_t delDir[MAX_PATH];
		wcout << "Name Delete Directory: " << endl;
		wcin >> delDir;
		deleteDir(delDir);
		break;
	case 5:
		wchar_t delFile[MAX_PATH];
		wcout << "Name Delete File: " << endl;
		wcin >> delFile;
		deleteFile(delFile);
		break;
	case 6:
		wchar_t cFile1[MAX_PATH];
		wchar_t cFile2[MAX_PATH];
		wcout << "Name Copy File 1: " << endl;
		wcin >> cFile1;
		wcout << "Name Copy File 2: " << endl;
		wcin >> cFile2;
		copyFile(cFile1,cFile2);
		break;
	case 7:
		wchar_t mFile1[MAX_PATH];
		wchar_t mFile2[MAX_PATH];
		wcout << "Name Move File 1: " << endl;
		wcin >> mFile1;
		wcout << "Name Move File 2: " << endl;
		wcin >> mFile2;
		moveFile(mFile1, mFile2);
		break;
	}

}
void listDirecrtory(LPCWSTR path) //функция вывода нужной директории
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(path, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			wcout << FindFileData.cFileName << endl;
		} while (FindNextFile(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
}

void createDir(LPCWSTR path2) //создание директории
{
	if (CreateDirectory(path2, NULL))
		wcout << "directory create" << endl;
	else
		wcout << "error create directory" << endl;
}

void createFile(LPCWSTR path3) //создание файла
{
	if (CreateFile(path3, FILE_READ_DATA,
		FILE_SHARE_READ,
		NULL, OPEN_ALWAYS,
		0, NULL))
		wcout << "file create" << endl;
	else
		wcout << "error create file" << endl;
}

void deleteDir(LPCWSTR path4) //удаление директории
{
	if (RemoveDirectory(path4))
		wcout << "directory delete" << endl;
	else
		wcout << "error delete directory" << endl;
}

void deleteFile(LPCWSTR path5) //удаление файла
{
	if (DeleteFile(path5))
		wcout << "file delete" << endl;
	else
		wcout << "error delete file" << endl;
}

void copyFile(LPCWSTR path6, LPCWSTR path7) // копирование файла
{
	BOOL cFile;
	cFile = CopyFile(path6, path7, TRUE);
	if (cFile == FALSE)
	{
		wcout << "Copy error " << GetLastError() << endl;
	}
	wcout << "File copy" << endl;
}

void moveFile(LPCWSTR path8, LPCWSTR path9) //перемещение файла
{
	BOOL mFile;
	mFile = MoveFile(path8, path9);
	if (mFile == FALSE)
	{
		wcout << "Move error " << GetLastError() << endl;
	}
	wcout << "File move" << endl;
}