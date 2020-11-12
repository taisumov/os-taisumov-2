#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int y = 0x1;
int z;

int choose;

void protectCheck(DWORD level);

// GetSystemInfo()

SYSTEM_INFO SysInfo;

WORD wProcessorArchitecture;

DWORD     dwPageSize;
LPVOID    lpMinimumApplicationAddress;
LPVOID    lpMaximumApplicationAddress;
DWORD_PTR dwActiveProcessorMask;
DWORD     dwNumberOfProcessors;
DWORD     dwAllocationGranularity;
WORD      wProcessorLevel;
WORD      wProcessorRevision;

// GlobalMemoryStatus()

DWORD  dwLength;
DWORD  dwMemoryLoad;
SIZE_T dwTotalPhys;
SIZE_T dwAvailPhys;
SIZE_T dwTotalPageFile;
SIZE_T dwAvailPageFile;
SIZE_T dwTotalVirtual;
SIZE_T dwAvailVirtual;

// VirtualQuery()

LPCVOID                    VQlpAddress;
MEMORY_BASIC_INFORMATION   VQlpBuffer;
SIZE_T                     VQdwLength;

PVOID  BaseAddress;
PVOID  AllocationBase;
DWORD  AllocationProtect;
WORD   PartitionId;
SIZE_T RegionSize;
DWORD  State;
DWORD  Protect;
DWORD  Type;

//VirtualAlloc

LPCVOID add = (LPCVOID)0x00010000;
int offset = 4096 * 10;

int binary(int num) {
    int t = 0, d = 1;
    while (num)
    {
        t += (num % 2) * d;
        num = num / 2;
        d = d * 10;
    }
    return t;
}

void PrintMenu() {

    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "|   | Выберите один из пунктов:                                               |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 1 | получение информации о вычислительной системе                           |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 2 | определение статуса виртуальной памяти                                  |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 3 | определение состояния конкретного участка памяти                        |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 4 | резервирование региона                                                  |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 5 | резервирование региона и передача ему физической памяти                 |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 6 | запись данных в ячейки памяти                                           |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 7 | установка защиты доступа для заданного региона памяти                   |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 8 | возврат физической памяти и освобождение региона адресного пространства |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;
    cout << "| 0 | ВЫХОД ИЗ ПРОГРАММЫ                                                      |" << endl;
    cout << "+---+-------------------------------------------------------------------------+" << endl;

}

void Get_SI(SYSTEM_INFO info) {

    cout << "Архитектура процессора: ";

    if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)    cout << "x64 (AMD или INTEL)" << endl;
    if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )    cout << "Intel Itanium Processor Family (IPF)" << endl;
    if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)    cout << "x86" << endl;
    if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM)      cout << "ARM" << endl;
    if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64)    cout << "ARM64" << endl;
    if (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_UNKNOWN)  cout << "Неизвестная архитектура" << endl;

    cout << "Размер страницы и степень гранулярности защиты страниц и обязательств:                 "   << SysInfo.dwPageSize << endl;
    cout << "Указатель на самый низкий адрес памяти, доступный приложениям и библиотекам:           0x" << SysInfo.lpMinimumApplicationAddress << endl;
    cout << "Указатель на самый высокий адрес памяти, доступный приложениям и библиотекам:          0x" << SysInfo.lpMaximumApplicationAddress << endl;
    cout << "Маска, представляющая набор процессоров, настроенных в системе:                        "   << binary((int)SysInfo.dwActiveProcessorMask) << endl;
    cout << "Количество логических процессоров в текущей группе:                                    "   << SysInfo.dwNumberOfProcessors << endl;
    cout << "Гранулярность начального адреса, по которому может быть выделена виртуальная память:   "   << SysInfo.dwAllocationGranularity << endl;
    cout << "Уровень процессора:                                                                    "   << SysInfo.wProcessorLevel << endl;
    cout << "Версия процессора, зависящая от архитектуры:                                           "   << SysInfo.wProcessorRevision << endl;
}

void Global_MS() {

    MEMORYSTATUS lpBuffer;
    GlobalMemoryStatus(&lpBuffer);

    cout << "Размер структуры MEMORYSTATUS:                                                       "
            << lpBuffer.dwLength << " байт" << endl;
    cout << "Процент используемой физической памяти:                                              "                                          
            << lpBuffer.dwMemoryLoad << "%" << endl;
    cout << "Объем фактической физической памяти:                                                 "                                             
            << lpBuffer.dwTotalPhys << " байт" << endl;
    cout << "Объем физической памяти, доступной в данный момент:                                  "                              
            << lpBuffer.dwAvailPhys << " байт" << endl;
    cout << "Текущий размер ограничения фиксированной памяти:                                     "                                 
            << lpBuffer.dwTotalPageFile << " байт" << endl;
    cout << "Максимальный объем памяти, который может зафиксировать текущий процесс:              "          
            << lpBuffer.dwAvailPageFile << " байт" << endl;
    cout << "Размер части вирт. адресного пространства вызывающего процесса в польз. режиме:      "  
            << lpBuffer.dwTotalVirtual << " байт" << endl;
    cout << "Объем невыделенной и незафиксированной памяти:                                       "                                    
            << lpBuffer.dwAvailVirtual << " байт" << endl;
}

void Virtual_Q(MEMORY_BASIC_INFORMATION  VQlpBuffer) {

    cout << "Указатель на базовый адрес региона страниц:                                                        "
            << VQlpBuffer.BaseAddress << endl;
    cout << "Указатель на базовый адрес диапазона страниц, выделенных пользователем:                            "
            << VQlpBuffer.AllocationBase << endl;
    cout << "Опция защиты памяти при первоначальном выделении области:                                          " << endl << "\t";
    protectCheck(VQlpBuffer.AllocationProtect);
    cout << "Размер региона, начинающейся с базового адреса, в котором все страницы имеют одинаковые атрибуты:  "
            << VQlpBuffer.RegionSize << " байт" << endl;
    cout << "Защита доступа к страницам в области:                                                              "
            << VQlpBuffer.RegionSize << endl << endl;

    cout << "Состояние страниц в регионе:            ";

    if (VQlpBuffer.State == MEM_COMMIT)         
            cout << "зафиксированная страница" << endl;
    if (VQlpBuffer.State == MEM_FREE)           
            cout  << "свободные страницы, недоступные для вызывающего процесса и доступные для выделения" << endl;
    if (VQlpBuffer.State == MEM_RESERVE) {
            cout << "зарезервированные страницы, на которых зарезервирован диапазон виртуального адресного пространства процесса" << endl;
            cout << "                                        без выделения какого - либо физического хранилища" << endl;
    }

    cout << "Защита доступа к страницам в регионе:   ";

    if (VQlpBuffer.Type == MEM_IMAGE)
            cout << "страницы памяти в пределах региона отображаются в виде раздела изображения" << endl;
    if (VQlpBuffer.Type == MEM_MAPPED)
            cout << "страницы памяти в пределах региона сопоставляются с представлением раздела" << endl;
    if (VQlpBuffer.Type == MEM_PRIVATE)
            cout << "страницы памяти в пределах региона являются частными" << endl;


}

void Virtual_A1(SYSTEM_INFO info) {

    LPVOID  BasicAddr = NULL;
    LPVOID  BasicAddr1 = NULL;

    BasicAddr = VirtualAlloc(NULL, info.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (BasicAddr != NULL)
    {
        cout << "Автоматическое резервирование успешно! Базовый адрес региона: 0х" << BasicAddr << endl << endl;
        cout << "Резервирование в режиме ввода адреса начала региона..." << endl;
        cout << "Введите адрес: 0x";
        cin >> BasicAddr1;

        BasicAddr = VirtualAlloc(BasicAddr1, info.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);

        if (BasicAddr != NULL)
             cout << "Резервирование успешно! Базовый адрес региона:     0x" << BasicAddr << endl << endl;
        else cout << "Ошибка резервирования." << endl;
    }
    else cout << "Ошибка резервирования." << endl;
    
    cout << endl << endl;
}

void Virtual_A2(SYSTEM_INFO info) {

    LPVOID  BasicAddr = NULL;
    LPVOID  BasicAddr1 = NULL;

    BasicAddr = VirtualAlloc(NULL, info.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (BasicAddr != NULL)
    {
        cout << "Автоматические резервирование и передача успешны! Базовый адрес региона: 0х" << BasicAddr << endl << endl;
        cout << "Резервирование и передача в режиме ввода адреса начала региона..." << endl;
        cout << "Введите адрес: 0x";
        cin >> BasicAddr1;

        BasicAddr = VirtualAlloc(BasicAddr1, info.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        
        if (BasicAddr != NULL)
             cout << "Резервирование и передача успешны! Базовый адрес региона 0x" << BasicAddr << endl << endl;
        else cout << "Резервирование и передача не прошли" << endl;
    }
    else cout << "Резервирование и передача не прошли" << endl;

    cout << endl << endl;

}

void Write_D() {

    string  source = "";
    LPVOID  address = NULL;
    CHAR*   destination = NULL;

    cout << "Введите данные для записи:" << endl;
    cin >> source;

    cout << "Введите адрес для записи: 0x";
    cin >> address;

    if (address != NULL)
    {
        MEMORY_BASIC_INFORMATION WD;

        VirtualQuery(address, &WD, 256);
        if (WD.AllocationProtect && (PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_READWRITE | PAGE_WRITECOPY))
        {
            destination = (CHAR*)address;
            CopyMemory(destination, source.c_str(), source.length() * sizeof(char));
            cout << endl << "Ячейка памяти 0x" << address << " заполнена успешно. Введённая информация:" << endl;
            for (size_t i = 0; i < source.length(); i++)
                cout << destination[i];
        }
        else {
            cout << "Уровень доступа не соответствует требованиям!";
        }
        cout << endl << endl;
    }
    else cout << "Нулевой адрес." << endl;

}

void protectMenu() {

    cout << "+---+----------------------------+" << endl;
    cout << "|   | Выберите один из пунктов:  |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 1 | PAGE_EXECUTE               |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 2 | PAGE_EXECUTE_READ          |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 3 | PAGE_EXECUTE_READWRITE     |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 4 | PAGE_EXECUTE_WRITECOPY     |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 5 | PAGE_NOACCESS              |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 6 | PAGE_READONLY              |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 7 | PAGE_READWRITE             |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 8 | PAGE_WRITECOPY             |" << endl;
    cout << "+---+----------------------------+" << endl;
    cout << "| 9 | PAGE_TARGETS_INVALID       |" << endl;
    cout << "+---+----------------------------+" << endl;


}

DWORD protectChoose(int x) {

    DWORD level;

    switch (x) {
    case 1:
        level = PAGE_EXECUTE;
        break;
    case 2:
        level = PAGE_EXECUTE_READ;
        break;
    case 3:
        level = PAGE_EXECUTE_READWRITE;
        break;
    case 4:
        level = PAGE_EXECUTE_WRITECOPY;
        break;
    case 5:
        level = PAGE_NOACCESS;
        break;
    case 6:
        level = PAGE_READONLY;
        break;
    case 7:
        level = PAGE_READWRITE;
        break;
    case 8:
        level = PAGE_WRITECOPY;
        break;
    case 9:
        level = PAGE_TARGETS_INVALID;
        break;
    }

    return level;
}

void protectCheck(DWORD level) {

    switch (level)
    {
    case 0:
        cout << "Отсутствие доступа" << endl;
        break;
    case PAGE_EXECUTE:
        cout << "Включено выполнение доступа к зафиксированной области страниц \n\t(PAGE_EXECUTE)" << endl;
        break;
    case PAGE_EXECUTE_READ:
        cout << "Включен доступ только для выполнения или чтения к зафиксированной области страниц. " << endl;
        cout << "Попытка записи в зафиксированный регион приводит к нарушению доступа \n\t(PAGE_EXECUTE_READ)" << endl;
        break;
    case PAGE_EXECUTE_READWRITE:
        cout << "Включен доступ только для выполнения, чтения или чтения/записи к зафиксированной области страниц \n\t(PAGE_EXECUTE_READWRITE)" << endl;
        break;
    case PAGE_EXECUTE_WRITECOPY:
        cout << "Включает доступ только для выполнения, чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов \n\t(PAGE_EXECUTE_WRITECOPY)" << endl;
        break;
    case PAGE_NOACCESS:
        cout << "Отключен весь доступ к зафиксированной области страниц \n\t(PAGE_NOACCESS)" << endl;
        break;
    case PAGE_READONLY:
        cout << "Включен доступ только для чтения к зафиксированной области страниц \n\t(PAGE_READONLY)" << endl;
        break;
    case PAGE_READWRITE:
        cout << "Включает доступ только для чтения или чтения/записи к зафиксированной области страниц \n\t(PAGE_READWRITE)" << endl;
        break;
    case PAGE_WRITECOPY:
        cout << "Включает доступ только для чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов \n\t(PAGE_WRITECOPY)" << endl;
        break;
    case PAGE_TARGETS_INVALID:
        cout << "Все местоположения на страницах установлены в качестве недопустимых целевых объектов для CFG \n\t(PAGE_TARGETS_INVALID)" << endl;
        break;
    }
    if ((level & PAGE_GUARD) != 0)
    {
        cout << "Страницы в регионе защищены \n(PAGE_GUARD)" << endl;
    }
    if ((level & PAGE_NOCACHE) != 0)
        cout << "Страницы не кэшируются \n(PAGE_NOCACHE)" << endl;
    if ((level & PAGE_WRITECOMBINE) != 0)
    {
        cout << "Страницы в установлены в режим комбинированной записи \n(PAGE_WRITECOMBINE)" << endl;
    }

}

void Virtual_F()
{
    LPVOID address = NULL;
    BOOL B = FALSE;
    cout << "Введите адрес для возврата физ. памяти";
    cout << " и освобождения региона адресного пространства: 0x";
    cin >> address;
    B = VirtualFree(address, 0, MEM_RELEASE);
    if (B)
        cout << "Регион успешно освобожден" << endl << endl;
    else cerr << "Ошибка: " << GetLastError();
    cout << endl << endl;
}

void Virtual_P() {

    BOOL B;
    LPVOID address = NULL;

    int inputLevel;

    DWORD oldLevel = NULL;
    DWORD newLevel = NULL;

    cout << "Введите адрес: 0x";
    cin >> address;

    if (address != NULL) {
        protectMenu();
        cin >> inputLevel;

        system("cls");

        newLevel = protectChoose(inputLevel);
        cout << "Новый уровень защиты: ";
        protectCheck(newLevel);
        cout << endl;
        if (VirtualProtect(address, sizeof(DWORD), newLevel, &oldLevel))
        {
            cout << "Старый уровень защиты:" << endl;
            protectCheck(oldLevel);
        }
        else cout << "Ошибка: " << GetLastError() << endl;

    }
    else cout << "Нулевой адрес (NULL)" << endl;
    cout << endl << endl;

}

int main()
{
    GetSystemInfo(&SysInfo);
    

    system("chcp 1251");
    system("cls");
    
    do {

        system("cls");
        PrintMenu();
        cin >> choose;

        system("cls");

        switch (choose) {

        case 1:

            Get_SI(SysInfo);
            system("pause");

            break;

        case 2:

            Global_MS();
            system("pause");

            break;

        case 3:

            cout << "+---+----------------------------------+" << endl;
            cout << "|   | Выберите один из пунктов:        |" << endl;
            cout << "+---+----------------------------------+" << endl;
            cout << "| 1 | информация о выбранном адресе    |" << endl;
            cout << "+---+----------------------------------+" << endl;
            cout << "| 2 | проверка всех адресов            |" << endl;
            cout << "+---+----------------------------------+" << endl;

            cin >> choose;

            switch (choose) {
            case 1:

                int     address;
                SIZE_T  x;
                cout << "Введите необходимый адрес: 0x";
                cin >> hex >> address;
                VQlpAddress = (LPCVOID)address;
                x = VirtualQuery(VQlpAddress, &VQlpBuffer, 256);
                cout << x << endl;
                Virtual_Q(VQlpBuffer);

                break;

            case 2:

                while (VirtualQuery(add, &VQlpBuffer, 256))
                {
                    cout << add << ' ';
                    switch (VQlpBuffer.State)
                    {
                    case MEM_COMMIT:
                        cout << "MEM_COMMIT\n";
                        break;
                    case MEM_FREE:
                        cout << "MEM_FREE\n";
                        break;
                    case MEM_RESERVE:
                        cout << "MEM_RESERVE\n";
                        break;
                    default:
                        cout << "Error!\n";
                        break;
                    }
                    add = (LPCVOID)((int)add + offset);
                }

                break;
            }

            system("pause");

            break;

        case 4:

            Virtual_A1(SysInfo);
            system("pause");

            break;

        case 5:

            Virtual_A2(SysInfo);
            system("pause");

            break;

        case 6:

            Write_D();
            system("pause");

            break;

        case 7:

            Virtual_P();
            system("pause");

            break;

        case 8:

            Virtual_F();
            system("pause");

            break;

        case 0:

            break;
        }
    } while (choose != 0);
    
    return 0;
}