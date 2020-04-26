#include"internal_cmd.h"


int external_cmd_excute(Args args ,config *cfg);
int background_excute(Args args ,config *cfg);

int cmd_analysis(Args args,config *cfg){
    
    int signal;
    if(args.size()==0)return EXCUTE_SUCCESS;

    if(args[args.size()-1]=="&")
        signal=background_excute(args,cfg);
    else
        signal=redirection(args,cfg);

    Args().swap(args);
    
    return signal;
}

Args split_cmd(string cmd){
    Args args;
    int size=cmd.size();
    int start=0,end=0;
    while(start<size&&end<size){
        for(;isspace(cmd[start])&&start<size;start++);
        end=start;
        for(;!isspace(cmd[end])&&end<size;end++);
        if(start!=end)
            args.push_back(cmd.substr(start,end-start));
        start=end;
    }
    return args;
}


int cmd_execute(Args args,config *cfg){

    string cmd0=args[0];
    
    //command is interal command
    if(cmd0=="cd"){
        return cmd_cd(args,cfg);
    }
    else if(cmd0=="clr"||cmd0=="clear"){
        return cmd_clr(args,cfg);
    }
    else if(cmd0=="dir"){
        return cmd_dir(args,cfg);
    }
    else if(cmd0=="environ"||cmd0=="env"){
        return cmd_env(args,cfg);
    }
    else if(cmd0=="echo"){
        return cmd_echo(args,cfg);
    } 
    else if(cmd0=="help"){
        return cmd_help();
    }
    else if(cmd0=="pause"){
       return cmd_pause(); 
    }
    else if(cmd0=="exit"||cmd0=="quit"){
       return cmd_exit(); 
    }
    //cannot find in internal command,go to extrnal command
    else return external_cmd_excute(args,cfg);

    
}

int external_cmd_excute(Args args ,config *cfg){
    char** arg_list = Args_to_arglist(args);
    
    /*  test for arg_list
    int i=0;
    while(arg_list[i]){
        cout<<arg_list[i]<<endl;
        i++;
    }
    */

   //creat child process
   pid_t pid;
   pid=fork();
   if(pid>0){
       //parent
       //wait for child exit
       int stat;
       waitpid(pid,&stat,0);
       return WEXITSTATUS(stat);
   }
   else if(pid<0){
       printf("Failed to create child process.\n");
       return UNKNOWN_FAILD;
   }
   else{
    //child
    //execute extrnal command success,return to parent
       execvp(arg_list[0],arg_list);
    //cannot execute command,continue to run
       printf("Can not find command.\n");
       return CMD_CAN_NOT_FIND;
   }
   free_arglist(arg_list);
   return CMD_EXIT_SUCCESS;
}

int background_excute(Args args ,config *cfg){
    Args bg_args=args;
    bg_args.erase(bg_args.end()-1);

    //creat a daemon
    pid_t pid=fork();
    int i;
    //ignore signal
    signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGHUP,SIG_IGN);

    if(pid>0)
    //parent
        return CMD_EXIT_SUCCESS;
    else if(pid<0){
    //child
        printf("Failed to create child process.\n");
        return UNKNOWN_FAILD;
    }
    else{
        //new session
        setsid();
        //change directry
        chdir("/");
        //new mask code
        umask(0);
        //ignore child signal to exit
        signal(SIGCHLD,SIG_IGN); 
        return redirection(bg_args,cfg);
    }
}
/* isspace for testing
int isspace(int i){
    if(i=='/0'||i=='/t'||i=='/n'||i==' ')return 1;
    else return 0;  
}
*/