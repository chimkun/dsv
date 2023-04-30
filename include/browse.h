#ifndef BROWSE_H
#define BROWSE_H

#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>

bool browseForFile(std::string& selectedFile);

#endif // BROWSE_H