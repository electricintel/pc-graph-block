/************************
* Brian Bove
* CS 162 Assignment 2 
* 10/24/2014
* Desc: Handles ncurses I/O
 * *********************/
#include <curses.h>
#include "screen.h"

void Screen::add_line(std::string line, int offset){
    if(cur_line > 25){
        waddstr(win, "\n");
    }
    wmove(win, cur_line + offset, 0);
    waddstr(win, line.c_str());
    getyx(win, last_pos[0], last_pos[1]);
    cur_line += 1 + offset;
    wrefresh(win);
}

void Screen::add_border(){
    box(win, 0, 0);
}

void Screen::refresh(bool reset){
    wrefresh(win);
    if(reset)
        cur_line = 0;
}

void Screen::clear(){
    werase(win);
    Screen::refresh();
}

char Screen::get_char(bool block){
    echosw(true);
    if(block)
        nodelay(stdscr, false);
    else
        nodelay(stdscr, true);
    echosw(false);

    return wgetch(win);
}

void Screen::echosw(bool status){
    if(status)
        echo();
    else
        noecho();
}

void Screen::cur_print(std::string line, int offset){
    int y,x;
    getyx(win, y, x);
    wmove(win, y, x + offset);
    waddstr(win, line.c_str());
}

void Screen::last_print(std::string line){
    wmove(win, last_pos[0], last_pos[1]);
    waddstr(win, line.c_str());
}

char* Screen::get_string(){
    char* str = new char[80];
    wgetstr(win, str);
    return str;
}

void Screen::destroy(){
    endwin();
    delwin(win);
}

void Screen::add_char(char ch){
    waddch(win, ch);
}

void Screen::add_char(char ch, int y, int x){
    wmove(win, y, x);
    waddch(win, ch);
}

char Screen::read_char(int y, int x){
    return mvwinch(win, y, x);
}
