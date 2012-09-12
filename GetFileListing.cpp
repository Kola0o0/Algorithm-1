#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <list>
using namespace std;


std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

string wchar_t2string(const wchar_t *wchar)
{
    string str = "";
    int index = 0;
    while(wchar[index] != 0)
    {
        str += (char)wchar[index];
        ++index;
    }
    return str;
}
void searchPatternFiles()
{
	string path = "E:\\OpenGLES2\\ehsan-opengles-book-samples-2d994e6\\Windows";
	string searchPattern = "*.c";
	string fullSearchPath = path + searchPattern;
	ifstream inputFile;
	WIN32_FIND_DATA FindData;
	HANDLE hFind;
	hFind = FindFirstFile(s2ws(fullSearchPath).c_str(), &FindData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		cout<<"Error searching";
		return;
	}
	while(FindNextFile(hFind,&FindData))
	{
		cout<<FindData.cFileName<<endl;
	}
	inputFile.close();
}

// This recursively gets all the filenames that match the filter, and adds
// them to the std list passed in
void GetFileListing(std::list<std::string>& listing, std::string directory, std::string fileFilter, bool recursively=true)
{
  // If we are going to recurse over all the subdirectories, first of all
  // get all the files that are in this directory that match the filter
  if (recursively)
    GetFileListing(listing, directory, fileFilter, false);

  directory += "\\";

  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = INVALID_HANDLE_VALUE;

  // Setup the filter according to whether we are getting the directories
  // or just the files
  std::string filter = directory + (recursively ? "*" : fileFilter);

  // Find the first file in the directory.
  hFind = FindFirstFile(s2ws(filter).c_str(), &FindFileData);

  if (hFind == INVALID_HANDLE_VALUE)
  {
    DWORD dwError = GetLastError();
    if (dwError!=ERROR_FILE_NOT_FOUND)
    {
      std::cout << "Invalid file handle for filter "<<filter<<". Error is " << GetLastError() << std::endl;
    }
  }
  else
  {
    // Add the first file found to the list
    if (!recursively)
    {
      listing.push_back(directory + wchar_t2string(FindFileData.cFileName));
    }

    // List all the other files in the directory.
    while (FindNextFile(hFind, &FindFileData) != 0)
    {
      if (!recursively)
      {
        listing.push_back(directory + wchar_t2string(FindFileData.cFileName));
      }
      else
      {
        // If we found a directory then recurse into it
        if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)>0 && FindFileData.cFileName[0]!='.')
        {
          GetFileListing(listing, directory + wchar_t2string(FindFileData.cFileName), fileFilter);
        }
      }
    }

    DWORD dwError = GetLastError();
    FindClose(hFind);
    if (dwError != ERROR_NO_MORE_FILES)
    {
      std::cout << "FindNextFile error. Error is "<< dwError << std::endl;
    }
  }
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::list<std::string> listing;
	GetFileListing(listing, "E:\\OpenGLES2", "*.c");
	for(std::list<std::string>::iterator it = listing.begin(); it!=listing.end();++it)
	{
		std::cout << *it << std::endl;
	}

	cin.get();
	return 0;
}