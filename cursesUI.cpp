#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <unistd.h>
#include <math.h>
#include <queue>
#include "screen.h"
using namespace std;

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

int main(){

    bool run = true;
    int x = 1;
    //char c;
    //clock_t start = clock();
    clock_t last = clock();
    clock_t now = clock();
    double t_refresh = 0.05;
    double dt;
    //double runt;

    queue <int> sinlut;

    // init curses screen, height: maxh - 5, width: maxw - 2
    Screen graph = Screen(-5, -2, 0, 0);
    graph.add_border();
    graph.refresh();

    for(int i=0; i < 1000; i++){
        sinlut.push(((graph.height-2)/2)*sin(.1 * i));
    }

    while(run){
        now = clock();
        dt = (double)(now - last)/(double)(CLOCKS_PER_SEC);
        //runt = (double)(now - start)/(double)(CLOCKS_PER_SEC);
        // add a new point every 100ms
        if(dt > t_refresh){
            graph.add_char('*', sinlut.front() + (graph.height/2), x);
            sinlut.pop();
            graph.refresh();
            x++;
            if(x > graph.width - 2){
                x = graph.width - 2;
                scroll_graph(graph);
            }
            last = clock();

        }
        // quit after 15 seconds
        //if(runt > 15)
            //run = false;
        if(sinlut.empty())
            run = false;
    }

    graph.destroy();
    return 0;

}
