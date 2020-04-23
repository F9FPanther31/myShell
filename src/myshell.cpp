#include"myshell.h"

using namespace std;

int loop(config *cfg);

int main (int argc,char const * argv[]){
    config *cfg=new config;
    load_config(cfg);
    while(1){
        int signal=loop(cfg);
        if(signal==SIGNAL_EIXT)break;
    }
    delete cfg;
    return 0;
}

int loop(config *cfg){
    print_prompt(cfg);
    string cmd;
    getline(cin,cmd);
    return cmd_execute(cmd,cfg);
}