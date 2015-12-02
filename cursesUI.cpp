#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <math.h>
#include "screen.h"
using namespace std;

int main(){

    bool run = true;
    int x = 1;
    char c;
    clock_t start = clock();
    clock_t last = clock();
    clock_t now = clock();
    double t_refresh = 0.1;
    double dt;
    double runt;

    // init curses screen, height: maxh - 5, width: maxw - 2
    Screen graph = Screen(-5, -2, 0, 0);
    graph.add_border();
    graph.refresh();

    while(run){
        now = clock();
        dt = (double)(now - last)/(double)(CLOCKS_PER_SEC);
        runt = (double)(now - start)/(double)(CLOCKS_PER_SEC);
        // add a new point every 100ms
        if(dt > t_refresh){
            graph.add_char('*', 10 * sin(.1 * x) + (graph.height/2), x);
            graph.refresh();
            x++;
            if(x > graph.width - 2)
                x = graph.width - 2;
            last = clock();

        }
        // quit after 15 seconds
        if(runt > 15)
            run = false;
    }

    graph.destroy();
    return 0;

}
