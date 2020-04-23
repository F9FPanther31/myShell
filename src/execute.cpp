#include"internal_cmd.h"

Args split_cmd(string cmd);
int cmd_execute(Args args ,config *cfg);
int outer_cmd_excute(Args args ,config *cfg);
int background_excute(Args args ,config *cfg);

int cmd_execute(string cmd,config *cfg){
    Args args = split_cmd(cmd);
    int signal;
    if(args.size()==0)return EXCUTE_SUCCESS;

    if(args[args.size()-1]=="&")
        signal=background_excute(args,cfg);
    else
        signal=cmd_execute(args,cfg);

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
    else  return outer_cmd_excute(args,cfg);

    
}

int outer_cmd_excute(Args args ,config *cfg){
    char** arg_list = Args_to_arglist(args);
    
    /*  test for arg_list
    int i=0;
    while(arg_list[i]){
        cout<<arg_list[i]<<endl;
        i++;
    }
    */

   pid_t pid;
   pid=fork();
   if(pid>0){
       int stat;
       waitpid(pid,&stat,0);
       return WEXITSTATUS(stat);
   }
   else if(pid<0){
       printf("Failed to create child process.\n");
       return UNKNOWN_FAILD;
   }
   else{
       execvp(arg_list[0],arg_list);

       printf("file can not be executed or does not exist.\n");
       return CMD_CAN_NOT_EXCUTE;
   }
   free_arglist(arg_list);
   return CMD_EXIT_SUCCESS;
}

int background_excute(Args args ,config *cfg){
    Args bg_args=args;
    bg_args.erase(bg_args.end()-1);

    pid_t pid=fork();
    int i;
    signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGHUP,SIG_IGN);

    if(pid>0)
        return CMD_EXIT_SUCCESS;
    else if(pid<0){
        printf("Failed to create child process.\n");
        return UNKNOWN_FAILD;
    }
    else{
        setsid();
        chdir("/");
        umask(0);
        signal(SIGCHLD,SIG_IGN); 
        return cmd_execute(bg_args,cfg);
    }
}
/* isspace for testing
int isspace(int i){
    if(i=='/0'||i=='/t'||i=='/n'||i==' ')return 1;
    else return 0;  
}
*/
