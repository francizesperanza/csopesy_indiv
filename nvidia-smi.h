#pragma once
extern void set_cursor_loc(int x, int y);
extern COORD get_cursor_loc();
extern void write_console(std::string text, int maxChar, std::string mode);
extern void write_process_name(std::string text, int maxChar, std::string mode);
extern void print_console_layout();
extern void print_datetime();
extern void print_gpu_summary();
extern void print_processes_list ();