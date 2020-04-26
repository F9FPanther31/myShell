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

        int signal=cmd_analysis(args,cfg);
        Args().swap(args);
    }
    while(1){
        print_prompt(cfg);
        string cmd;
        getline(cin,cmd);
        Args args = split_cmd(cmd);
        int signal=cmd_analysis(args,cfg);
        if(signal==SIGNAL_EIXT)break;
    }
    delete cfg;
    return 0;
}

