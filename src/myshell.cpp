#include"myshell.h"

using namespace std;

int count;

int main (int argc,char const * argv[]){
    count =0;
    config *cfg=new config;
    load_config(cfg);
   
    /*  test for outer args
    for(int i=0;i<argc;i++)
        cout<<argv[i]<<" ";
    cout<<endl;
    */

    int signal;
    //outer args include parameter list,processing external commands
    if(argc>1){
        Args args;
        for(int i=1;i<argc;i++){
            args.push_back(argv[i]);
            //cout<<args[i-1]<<endl;
        }
        signal=cmd_analysis(args,cfg);
        Args().swap(args);
        if(signal==BACK_GROUND)return 0;

    }
    
    while(1){
        if(signal==BACK_GROUND)break;
        print_prompt(cfg);
        string cmd;
        getline(cin,cmd);
        if(cin.eof())
            kill(getpid(),SIGTERM);
        Args args = split_cmd(cmd);
        signal=cmd_analysis(args,cfg);
        
    }
    delete cfg;
    return 0;
}

