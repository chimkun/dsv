#include "browse.h"
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>

bool browseForFile(std::string &fileContent) {
    char curPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, curPath);

    TCHAR szFileName[MAX_PATH] = { 0 };
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = _T("txt");

    if (GetOpenFileName(&ofn) == TRUE) {
        std::ifstream file(ofn.lpstrFile);
        std::string line;
        std::getline(file, line);
        fileContent = line;

        SetCurrentDirectory(curPath);
        return true;
    }
    else {
        return false;
    }
}
