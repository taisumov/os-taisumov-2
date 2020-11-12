#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>

using namespace std;

int main()
{
    system("chcp 1251");
    system("cls");

    wstring nameFile;
    HANDLE FileMap = NULL;
    LPCWSTR  lpFileName = L"";
    LPVOID lpFileMap = NULL;
    string fileInput;

    cout << endl << "+------------------------------+" << endl;
    cout << "| Введите имя отображения:     |" << endl;
    cout << "+------------------------------+" << endl << endl << " >>> ";
    wcin >> nameFile;

    lpFileName = nameFile.c_str();

    FileMap = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, (LPCTSTR)lpFileName);

    if (FileMap != NULL)
    {
        lpFileMap = MapViewOfFile(FileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);


        cout << endl << "+------------------------------+" << endl;
        cout << "| Получены следующие данные:   |" << endl;
        cout << "+------------------------------+" << endl << endl << " >>> ";

        cout << (char*)lpFileMap << endl << endl;

        cout << "Работа обеих программ завершена. Можете закрыть как читатель, так и писатель.";

        _getch();
  
    }

    UnmapViewOfFile(lpFileMap);
    CloseHandle(FileMap);

    return 0;
}

