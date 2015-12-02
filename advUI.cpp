#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

using namespace std;

#define RED "\033[31m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define YELLOW "\033[36m"

int main(){
    srand(time(NULL));
    ofstream data;
    string line;
    unsigned int us = 50000;
    data.open("data.txt");
    int Va, Vb, Vc, Ia, Ib, Vao, Vbo, Vco, Iao, Ibo;
    if(data.is_open()){
        for(int i = 0; i < 100; i++){
            Va = rand() % 75;
            Vb = rand() % 75;
            Vc = rand() % 75;
            Ia = rand() % 20;
            Ib = rand() % 20;

            data << Va << "," << Vb << "," << Vc << "," << Ia << "," << Ib << '\n';

        }
        data.close();
    }
    //char buffer[100];
 


    ifstream dataread;
    dataread.open("data.txt");
    //int place = 0;
    //int graph[5][100];
    /*string Vas;
    string Vbs;
    string Vcs;
    string Ias;
    string Ibs;
    int startpos = 0;
    int endpos = 0;
    string space = " ";
    string comma = ",";*/
    if(dataread.is_open()){
        while(getline(dataread,line)){
            //cout << line << endl;

            if(5 == sscanf(line.c_str(), "%d,%d,%d,%d,%d\n", &Va, &Vb, &Vc, &Ia, &Ib)){
                if(Va == 999){
                    cout << "Va not updated, keeping old value\n";
                    Va = Vao;
                }
                if(Vb == 999){
                    cout << "Vb not updated, keeping old value\n";
                    Vb = Vbo;
                }
                if(Vc == 999){
                    cout << "Vc not updated, keeping old value\n";
                    Vc = Vco;
                }
                if(Ia == 999){
                    cout << "Ia not updated, keeping old value\n";
                    Ia = Iao;
                }
                if(Ib == 999){
                    cout << "Ib not updated, keeping old value\n";
                    Ib = Ibo;
                }
                usleep(500000);
                //system("clear");

                //sprintf(buffer, "%sVa:%d%s,%sVb:%d%s,%sVc:%d%s,%sIa:%d%s,%sIb:%d%s",RED, Va, RESET, BLUE, Vb, RESET, GREEN, Vc, RESET, YELLOW, Ia, RESET, MAGENTA, Ib, RESET);
                //sprintf(buffer, "%99s\r", buffer);
                //cout << buffer;
                cout << RED << "Va: " << Va << RESET << ",\n" << BLUE << "Vb: " << Vb << RESET << ",\n" << GREEN << "Vc: " << Vc << RESET << ",\n" << YELLOW << "Ia: " << Ia << RESET << ",\n" << MAGENTA << "Ib: " << Ib << RESET << "                                     \n";
                cout << endl;
                Vao = Va;
                Vbo = Vb;
                Vco = Vc;
                Iao = Ia;
                Ibo = Ib;

            }

            /*startpos = 0;
            //endpos = strcspn(line, space);
            endpos = line.find(comma);
            Vas = line.substr(startpos, endpos);
            
            //startpos = endpos + 1;
            line = line.substr(endpos);
            //endpos = strcspn(line, space);
            endpos = line.find(comma);
            Vbs = line.substr(startpos, endpos);
            
            //startpos = endpos + 1;
            line = line.substr(endpos);
            //endpos = strcspn(line, space);
            endpos = line.find(comma);
            Vcs = line.substr(startpos, endpos);

            //startpos = endpos + 1;
            line = line.substr(endpos);
            //endpos = strcspn(line, space);
            endpos = line.find(comma);
            Ias = line.substr(startpos, endpos);

            //startpos = endpos + 1;
            line = line.substr(endpos);
            //endpos = strcspn(line, space);
            endpos = line.find(comma);
            Ibs = line.substr(startpos, endpos);*/

            //cout << RED << "Va: " << Vas << RESET << ", " << BLUE << "Vb: " << Vbs << RESET << ", " << GREEN << "Vc: " << Vcs << RESET << ", " << YELLOW << "Ia: " << Ias << RESET << ", " << MAGENTA << "Ib: " << Ibs << RESET << endl;

        }
        dataread.close();
    }
    
    else cout << "Unable to open file"; 
    cout << RESET << endl << endl;
    return 0;
    //data.close();
}