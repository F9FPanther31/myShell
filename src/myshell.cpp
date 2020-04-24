#include"myshell.h"

using namespace std;

int loop(config *cfg);

int main (int argc,char const * argv[]){
    config *cfg=new config;
    load_config(cfg);

    /*  test for outer args
    for(int i=0;i<argc;i++)
        cout<<argv[i]<<" ";
    cout<<endl;
    */

    //outer args include parameter list,processing external commands
    if(argc>1){
        Args args;
        for(int i=1;i<argc;i++)
            args.push_back(argv[i]);

        cmd_execute(args,cfg);
        Args().swap(args);
    }
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
    return cmd_analysis(cmd,cfg);
}