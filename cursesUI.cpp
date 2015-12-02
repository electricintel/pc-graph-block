#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <math.h>
#include <queue>
#include <string.h>
#include "screen.h"
using namespace std;

// doesn't keep colors
void scroll_graph(Screen &graph){
    char buf;
    for(int i=2; i < (graph.width - 1); i++){
        for(int j=1; j < (graph.height- 1); j++){
            buf = graph.read_char(j, i);
            graph.add_char(buf, j, i-1);
        }
    }
    for(int j=1; j < (graph.height- 1); j++){
        graph.add_char(' ', j, graph.width-2);
    }

    graph.refresh();
}

void scroll_graph_q(Screen &graph, int* buffers[5], int bufsize, int bufpos, bool plot_on[5]){
    int x = 1;
    for(int i=0; i < graph.height-2; i++){
        graph.add_char(' ', i, x);
    }
    // turn old stuff off first
    for(int i=bufpos+1; i < bufsize; i++){
        for(int j=0; j < 5; j++){
            graph.add_char(' ', buffers[j][i], x+1, j);
        }
        x++;
    }

    for(int i=0; i < bufpos; i++){
        for(int j=0; j < 5; j++){
            graph.add_char(' ', buffers[j][i], x+1, j);
        }
        x++;
    }

    x = 1;
    // now turn new stuff on
    for(int i=bufpos+1; i < bufsize; i++){
        for(int j=0; j < 5; j++){
            if(plot_on[j]){
                graph.add_char('*', buffers[j][i], x, j);
            }
        }
        x++;
    }

    for(int i=0; i < bufpos; i++){
        for(int j=0; j < 5; j++){
            if(plot_on[j]){
                graph.add_char('*', buffers[j][i], x, j);
            }
        }
        x++;
    }

    graph.add_border();
    graph.refresh();
}


int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void redraw_info(Screen &info, bool* plot_on){

    char buf[50];

    char flag = ' ';
    for(int i=0; i < 3; i++){
        if(plot_on[i])
            flag = 'X';
        else
            flag = ' ';
        sprintf(buf, "[%c] V%c", flag, i + 97);
        for(unsigned int j=0; j < strlen(buf); j++){
            info.add_char(buf[j], i+1, j+3, i);
        }
    }
    for(int i=3; i < 5; i++){
        if(plot_on[i])
            flag = 'X';
        else
            flag = ' ';
        sprintf(buf, "[%c] I%c", flag, (i-3) + 97);
        for(unsigned int j=0; j < strlen(buf); j++){
            info.add_char(buf[j], (i-3)+1, j+20, i);
        }
    }
    info.refresh();
}

void legend_init(Screen &legend, int height){
    legend.add_line("75V", height - map(75, 0, 75, 0, height));
    legend.add_line("70V", height - map(70, 0, 75, 0, height));
    legend.add_line("60V", height - map(60, 0, 75, 0, height));
    legend.add_line("50V", height - map(50, 0, 75, 0, height));
    legend.add_line("40V", height - map(40, 0, 75, 0, height));
    legend.add_line("30V", height - map(30, 0, 75, 0, height));
    legend.add_line("20V", height - map(20, 0, 75, 0, height));
    legend.add_line("10V", height - map(10, 0, 75, 0, height));

    legend.add_line("20A", height - map(20, 0, 20, 0, height -1), 3);
    legend.add_line("15A", height - map(15, 0, 20, 0, height), 3);
    legend.add_line("10A", height - map(10, 0, 20, 0, height), 3);
    legend.add_line(" 5A", height - map(5, 0, 20, 0, height), 3);
    legend.refresh();
}

void info_init(Screen &info){
    info.add_border();
    char* message = "Use keys 1-5 to toggle plots.";
    char* message2 = "Press q to quit.";
    for(unsigned int j=0; j < strlen(message); j++){
        info.add_char(message[j], 1, j+35, 4);
    }
    for(unsigned int j=0; j < strlen(message2); j++){
        info.add_char(message2[j], 2, j+35, 4);
    }
    info.refresh();
}


int main(){

    bool run = true;
    bool plot_on[5];
    int x = 1;
    //char c;
    //clock_t start = clock();
    clock_t last = clock();
    clock_t now = clock();
    double t_refresh = 0.05;
    double dt;
    int freqadj = 20;
    int data[5];
    string line;
    char keypress;
    //double runt;
    //
    ifstream dataread;
    dataread.open("sinlut.csv");

    queue <int> sinlut;


    // init curses screen, height: maxh - 5, width: maxw - 2
    Screen graph = Screen(-7, -4, 0, 0);
    Screen info = Screen(5, -4, graph.height, 0);
    Screen legend = Screen(graph.height, 5, 0, graph.width);

    info_init(info);

    legend_init(legend, graph.height);


    graph.add_border();
    graph.refresh();

    int bufwidth = graph.width-2;
    int bufpos = 0;
    //int **head;

    int *buffers[5];
    for(int i=0; i < 5; i++){
        buffers[i] = new int[graph.width-2];
    }

    //int ***buffer = new int**[graph.width-2];
    //for(int i=0; i < graph.width-2; i++){
        //buffer[i] = new int*[graph.height-2];
        //for(int j=0; j < graph.height-2; j++){
            //buffer[i][j] = new int[2];
            //buffer[i][j][0] = 0;
            //buffer[i][j][1] = 0;
        //}
    //}
    //head = buffer[bufpos];

    for(int i=0; i < 5; i++)
        plot_on[i] = false;
    plot_on[0] = true;

    while(run){
        now = clock();
        dt = (double)(now - last)/(double)(CLOCKS_PER_SEC);
        // add a new point every 100ms
        if(dt > t_refresh){
            getline(dataread, line);
            if( sscanf(line.c_str(), "%d,%d,%d,%d,%d\n", &data[0], &data[1], &data[2], &data[3], &data[4]) == 5){
                for(int i=0; i < 5; i++){
                    if(plot_on[i]){
                        data[i] = map(data[i], 0, 65535, 2, graph.height-2);
                        buffers[i][bufpos] = data[i];
                    }
                }
                bufpos++;
                if(bufpos == bufwidth)
                    bufpos = 0;
                scroll_graph_q(graph, buffers, bufwidth, bufpos, plot_on);

                for(int i=0; i < freqadj; i++){
                    getline(dataread, line);
                }
            }
            last = clock();

            redraw_info(info, plot_on);

        }
        if(dataread.peek() == EOF){
            dataread.clear();
            dataread.seekg(0, ios::beg);
        }
        keypress = graph.get_char(false);
        switch(keypress){
            case '1':   
                plot_on[0] = !plot_on[0];
                break;
            case '2':   
                plot_on[1] = !plot_on[1];
                break;
            case '3':   
                plot_on[2] = !plot_on[2];
                break;
            case '4':   
                plot_on[3] = !plot_on[3];
                break;
            case '5':   
                plot_on[4] = !plot_on[4];
                break;
            case 'q':   
                run = false;
                break;
        }
    }

    dataread.close();
    graph.destroy();
    info.destroy();
    return 0;

}
