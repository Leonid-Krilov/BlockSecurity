 #include "autorun.h"

#include <QString>

Autorun::Autorun(){}

void Autorun::start(){
    wchar_t szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, MAX_PATH);

    HKEY hKey;
    RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
    RegSetValueEx(hKey, L"Diplom.exe", 0, REG_SZ, (LPBYTE)szPath, lstrlen(szPath) * 2);
    RegCloseKey(hKey);
}

void Autorun::stop(){
    HKEY hKey;
    RegOpenKey(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
    RegDeleteValue(hKey, L"Diplom.exe");
    RegCloseKey(hKey);
}
