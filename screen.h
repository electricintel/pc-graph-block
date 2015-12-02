/************************
* Brian Bove
* CS 162 Assignment 2 
* 10/24/2014
* Desc: Definition of Screen class.
 * *********************/
#include <iostream>
#include <curses.h>

#ifndef __SCREEN__
#define __SCREEN__

class Screen{

    public:
        Screen(){
            // initialize ncurses screen
            initscr();
            cbreak();
            noecho();

            int h, w;
            getmaxyx(stdscr, h, w);
            win = newwin(h, w, 0, 0);
            idlok(win, true);
            scrollok(win, true);
            Screen::refresh();
            getmaxyx(win, height, width);
        }
        
        Screen(int h, int w, int off_y, int off_x){
            // initialize ncurses screen
            initscr();
            cbreak();
            noecho();
            curs_set(0);
            int maxh, maxw;
            getmaxyx(stdscr, maxh, maxw);

            if(h == 0)
                h = maxh;
            if(w == 0)
                w = maxw;

            if(h < 0)
                h = maxh + h;
            if(w < 0)
                w = maxw + w;

            win = newwin(h, w, off_y, off_x);
            idlok(win, true);
            scrollok(win, true);
            Screen::refresh();
            getmaxyx(win, height, width);
        }
        void add_border();
        void destroy();
        void cur_print(std::string line, int offset=0);
        void add_line(std::string line, int offset = 0);
        void refresh(bool reset=true);
        void clear();
        void echosw(bool status);
        char get_char(bool block=true);
        int cur_line;
        char* get_string();
        int last_pos[2];
        void last_print(std::string line);
        void add_char(char ch);
        void add_char(char ch, int y, int x);
        int height;
        int width;
        char read_char(int y, int x);

    private:
        WINDOW* win;
};

#endif
