#include"internal_cmd.h"

int cmd_cd(Args args,config *cfg){
    if(args.size()==1){
        string home=get_home(cfg);
        chdir(home.c_str());
    } 
    else
    {
        if(chdir(args[1].c_str())==-1){
            cout<<"bash: "<<args[0]<<": "<<
            args[1]<<": Can not find file or dir"<<endl;       
        }
    }
    return CMD_EXIT_SUCCESS;
}
int cmd_clr(Args args,config *cfg){
    fflush(stdout);
    printf("\x1b[H\x1b[2J");
    return CMD_EXIT_SUCCESS;
}
int cmd_dir(Args args,config *cfg){
    DIR *dir=NULL;
    struct dirent *dirt=NULL;

    if (args.size()>1)
    {
        for(int i=1;i<args.size();i++){
            if(dir=opendir(args[i].c_str())){
                while((dirt=readdir(dir))!=NULL){
                    if (strcmp(dirt->d_name, ".") != 0 &&strcmp(dirt->d_name, "..") != 0)
                        cout<<dirt->d_name<<' ';
                }
                cout<<endl;
                closedir(dir);
            }
            else 
                cout<<args[0]<<": Can not visit'"<<
                args[i]<<"': Can not find file or dir"<<endl;
        }
    }
    else {
        dir=opendir(getcwd(NULL,0));
        while((dirt=readdir(dir))!=NULL){
            if (strcmp(dirt->d_name, ".") != 0 &&strcmp(dirt->d_name, "..") != 0)
                cout<<dirt->d_name<<' ';
        }
        cout<<endl;
        closedir(dir);
    }
    return CMD_EXIT_SUCCESS;    
}
int cmd_env(Args args,config *cfg){
    char** env_info=environ;
    while(*env_info){
        cout<<*env_info<<endl;
        *env_info++;
    }
    return CMD_EXIT_SUCCESS;
}
int cmd_echo(Args args,config *cfg){
    for(int i=1;i<args.size();i++){
        cout<<args[i]<<" ";
    }
    cout<<endl;
    return CMD_EXIT_SUCCESS; 
}
int cmd_help(){
    ifstream file("res/text.txt");
    string text;
    while(!file.eof()){
        getline(file,text);
        cout<<text<<endl;
    }
    return CMD_EXIT_SUCCESS; 
}
int cmd_pause(){
    char c;
    printf("press enter to continue\n");
    while ( (c = getchar()) != '\n' && c != EOF ) ; 
    clearerr(stdin); 
    
    return CMD_EXIT_SUCCESS; 
}
int cmd_exit(){
    
    pid_t pid=getpid();
    if(kill(pid,SIGTERM)==-1);
        return UNKNOWN_FAILD;
    return SIGNAL_EIXT;
}; 