#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>

using namespace std;

int main()
{
    system("color 02");
    system("chcp 1251");
    system("cls");

    wstring nameFile;
    wstring mapFile;
    HANDLE File = NULL;
    HANDLE FileMap = NULL;
    LPCWSTR  lpFileName;
    LPCWSTR  lpMapName = L"";
    LPVOID lpFileMap = NULL;
    string fileInput;

    cout << "+----------------------------+" << endl;
    cout << "| Введите имя файла:         |" << endl;
    cout << "+----------------------------+" << endl << endl << " >>> ";
    wcin >> nameFile;

    lpFileName = nameFile.c_str();

    File = CreateFile(lpFileName, GENERIC_WRITE | GENERIC_READ, NULL, NULL, CREATE_ALWAYS, NULL, NULL);

    if (File != INVALID_HANDLE_VALUE) {

        cout << endl << "+----------------------------+" << endl;
        cout << "| Введите имя отображения:   |" << endl;
        cout << "+----------------------------+" << endl << endl << " >>> ";
        wcin >> mapFile;

        lpMapName = mapFile.c_str();

        FileMap = CreateFileMapping(File, NULL, PAGE_READWRITE, 0, 128, (LPCTSTR)lpMapName);
        lpFileMap = MapViewOfFile(FileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

        if (lpFileMap != NULL) cout << "Файл успешно спроецирован." << endl << endl;

        cout << endl << "+----------------------------+" << endl;
        cout << "| Введите данные для записи: |" << endl;
        cout << "+----------------------------+" << endl << endl << " >>> ";
        cin >> fileInput;

        CopyMemory((LPVOID)lpFileMap, (CHAR*)fileInput.c_str(), fileInput.length() * sizeof(char));

        cout << endl << "Данные записаны. Не закрывайте программу-писатель: для дальнейшей работы запустите программу-читатель.";

        _getch();

    }
    else {
        cout << "Ошибка создания файла. Код ошибки: " << GetLastError() << endl;
    }
    
    if (lpFileMap != NULL && File != NULL) {

        UnmapViewOfFile(lpFileMap);
        CloseHandle(File);

    }
        

    return 0;
}
