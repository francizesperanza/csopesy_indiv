#include <Windows.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <cstring>
#include "nvidia-smi.h"

void set_cursor_loc(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD loc;
    loc.X = x;
    loc.Y = y;
    SetConsoleCursorPosition(hConsole, loc);
}

COORD get_cursor_loc() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD loc;

    GetConsoleScreenBufferInfo(hConsole, &csbi);

    loc.X = csbi.dwCursorPosition.X;
    loc.Y = csbi.dwCursorPosition.Y;
    return loc;
}

void write_console(std::string text, int maxChar, std::string mode) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD charsWritten;
    const char* result = "";

    if (text.size() > maxChar) {
        result = text.c_str();
        WriteConsole(hConsole, result, maxChar, &charsWritten, NULL);
    }
    else {
        int paddingSize = maxChar - text.length();
        std::string padding(paddingSize, ' ');
        std::string paddedText;

        if (mode == "right") {
            std::string paddedText = padding + text;
            result = paddedText.c_str();
            WriteConsole(hConsole, result, maxChar, &charsWritten, NULL);
        }
        else if (mode == "left") {
            std::string paddedText = text + padding;
            result = paddedText.c_str();
            WriteConsole(hConsole, result, maxChar, &charsWritten, NULL);
        }

    }
}

void write_process_name(std::string text, int maxChar, std::string mode) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD charsWritten;
    const char* result = "";

    if (text.size() > maxChar) {
        std::string lastpart = text.substr(text.length() - maxChar, maxChar);
        lastpart.replace(0, 3, "...");
        result = lastpart.c_str();
        WriteConsole(hConsole, result, maxChar, &charsWritten, NULL);
    }
    else {
        int paddingSize = maxChar - text.length();
        std::string padding(paddingSize, ' ');
        std::string paddedText;

        if (mode == "right") {
            std::string paddedText = padding + text;
            result = paddedText.c_str();
            WriteConsole(hConsole, result, maxChar, &charsWritten, NULL);
        }
        else if (mode == "left") {
            std::string paddedText = text + padding;
            result = paddedText.c_str();
            WriteConsole(hConsole, result, maxChar, &charsWritten, NULL);
        }

    }
}

void print_datetime(){
    auto timenow = std::chrono::system_clock::now();

    std::time_t formatted_time = std::chrono::system_clock::to_time_t(timenow);

    std::cout << std::ctime(&formatted_time);
}

void print_gpu_summary() {
    COORD starting_pos = get_cursor_loc();

    int start_x = starting_pos.X;
    int start_y = starting_pos.Y;

    std::string smi_version = "551.86";
    std::string driver_version = "551.86";
    std::string cuda_version = "12.4";
    std::string gpu_number = "0";
    std::string fan = "28%";
    std::string temp = "37C";
    std::string gpu_name = "NVIDIA GeForce GTX 1080";
    std::string gpu_model = "WDDM";
    std::string perf = "P8";
    std::string power_usage = "11W";
    std::string power_cap = "180W";
    std::string bus_id = "00000000:26:00.0";
    std::string disp_a = "On";
    std::string memory_usage = "701MiB";
    std::string memory_cap = "8192MiB";
    std::string volatile_cpu_util = "0%";
    std::string uncorr_ecc = "N/A";
    std::string compute_m = "Default";
    std::string mig_m = "N/A";


    std::cout << "+-----------------------------------------------------------------------------------------+" << std::endl;

    starting_pos = get_cursor_loc();
    start_y = starting_pos.Y;

    std::cout << "| NVIDIA-SMI ";
    write_console(smi_version, 22, "left");

    set_cursor_loc(36, start_y);
    std::cout << "Driver Version: ";
    write_console(driver_version, 14, "left");

    set_cursor_loc(67, start_y);
    std::cout << "CUDA Version: ";
    write_console(cuda_version, 7, "left");

    set_cursor_loc(90, start_y);
    std::cout << "|" << std::endl;

    std::cout << "|-----------------------------------------+------------------------+----------------------+" << std::endl;

    std::cout << "| GPU  Name                     TCC/WDDM  | Bus-Id          Disp.A | Volatile Uncorr. ECC |" << std::endl;
    std::cout << "| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |" << std::endl;
    std::cout << "|                                         |                        |               MIG M. |" << std::endl;
    std::cout << "|=========================================+========================+======================|" << std::endl;

    starting_pos = get_cursor_loc();
    start_y = starting_pos.Y;

    std::cout << "| ";
    set_cursor_loc(2, start_y);
    write_console(gpu_number, 3, "right");

    set_cursor_loc(7, start_y);
    write_console(gpu_name, 23, "left");

    set_cursor_loc(31, start_y);
    write_console(gpu_model, 9, "right");

    std::cout << "  | ";
    write_console(bus_id, 18, "right");
    std::cout << " ";
    write_console(disp_a, 3, "right");
    std::cout << " | ";
    write_console(uncorr_ecc, 20, "right");
    std::cout << " |" << std::endl;

    starting_pos = get_cursor_loc();
    start_y = starting_pos.Y;

    std::cout << "| ";
    write_console(fan, 4, "left");
    std::cout << " ";
    write_console(temp, 4, "right");
    set_cursor_loc(15, start_y);
    write_console(perf, 2, "right");

    set_cursor_loc(28, start_y);
    write_console(power_usage, 5, "right");
    std::cout << " / ";
    write_console(power_cap, 5, "right");
    std::cout << " |  ";

    write_console(memory_usage, 9, "right");
    std::cout << " / ";
    write_console(memory_cap, 9, "right");
    std::cout << " |";

    set_cursor_loc(72, start_y);
    write_console(volatile_cpu_util, 4, "right");
    set_cursor_loc(79, start_y);
    write_console(compute_m, 10, "right");
    std::cout << " |" << std::endl;

    starting_pos = get_cursor_loc();
    start_y = starting_pos.Y;

    std::cout << "|";
    set_cursor_loc(42, start_y);
    std::cout << "|";
    set_cursor_loc(67, start_y);
    std::cout << "| ";
    write_console(uncorr_ecc, 20, "right");
    std::cout << " |" << std::endl;

    std::cout << "+-----------------------------------------+------------------------+----------------------+" << std::endl;
    std::cout.flush();
}

void print_processes_list() {

    std::string processes[5][7] = {
        {"0", "N/A", "N/A", "1368", "C+G", "C:\\Windows\\System32\\dwm.exe", "N/A"},
        {"0", "N/A", "N/A", "3546", "C+G", "C:\\Users\\ASUS\\AppData\\Local\\Programs\\Opera GX\\opera.exe", "N/A"},
        {"0", "N/A", "N/A", "3998", "C+G", "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe", "N/A"},
        {"0", "N/A", "N/A", "4532", "C+G", "C:\\Users\\ASUS\\AppData\\Local\\Programs\\Notion\\Notion.exe", "N/A"},
        {"0", "N/A", "N/A", "6555", "C+G", "C:\\Users\\ASUS\\AppData\\Local\\Discord\\app-1.0.9164\\Discord.exe", "N/A"},
    };

    std::cout << "\n+-----------------------------------------------------------------------------------------+\n";
    std::cout << "| Processes:                                                                              |\n";
    std::cout << "|  GPU   GI   CI        PID   Type   Process name                              GPU Memory |\n";
    std::cout << "|        ID   ID                                                               Usage      |\n";
    std::cout << "|=========================================================================================|\n";
    
    COORD starting_pos;

    for (int i = 0; i < 5; i++) {

        starting_pos = get_cursor_loc();

        int start_x = starting_pos.X;
        int start_y = starting_pos.Y;

        std::cout << "|";

        set_cursor_loc(3, start_y);
        write_console(processes[i][0], 3, "right");

        set_cursor_loc(9, start_y);
        write_console(processes[i][1], 3, "left");

        set_cursor_loc(14, start_y);
        write_console(processes[i][2], 3, "left");

        set_cursor_loc(18, start_y);
        write_console(processes[i][3], 9, "right");

        set_cursor_loc(28, start_y);
        write_console(processes[i][4], 6, "right");

        set_cursor_loc(37, start_y);
        write_process_name(processes[i][5], 38, "left");

        set_cursor_loc(81, start_y);
        write_console(processes[i][6], 3, "right");

        set_cursor_loc(90, start_y);
        std::cout << "|" << std::endl;
    }

    std::cout << "+-----------------------------------------------------------------------------------------+" << std::endl;
}

void print_console_layout() {
    print_datetime();
    print_gpu_summary();
    print_processes_list();
}
