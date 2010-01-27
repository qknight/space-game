#ifndef MYLOGGER_H
#define MYLOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
class mylogger {
  public:
    static const void reset(){
	fstream f;
	f.open("/home/billy/projects/hihi/logfile", ios::out);
	f.clear();
	f.close();
    }
    
    static const void logTime(){
      
      time_t t;
      time(&t);
      fstream f;
      f.open("/home/billy/projects/hihi/logfile", ios::out|ios::app);
      f << endl;
      f << ctime(&t);
      f.close();  
    }
    static const void log(string str){
      fstream f;
      f.open("/home/billy/projects/hihi/logfile", ios::out|ios::app);
      f << str.c_str() << endl;
      f.close();  
    }
};
#endif // MYLOGGER_H
