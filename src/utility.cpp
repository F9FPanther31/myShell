//define color
#define GREEN "\e[1;32m"
#define RED "\e[1;31m"
#define BLUE "\e[1;34m"
#define WHITE "\e[0m"

#include"myshell.h"

int print_prompt (config *config){
    string cwd=getcwd(NULL,0);
    string home=get_home(config);
    int start=cwd.find(home);
    cwd.replace(start,home.size(),"~");

    cout<<GREEN<<config->user->pw_name<<
    '@'<<config->host_name<<
    WHITE<<":"<<BLUE<<cwd<<
    WHITE<<"$ ";
}

string get_home(config *cfg){
    string home="/home/";
    return home.append(cfg->user->pw_name);
}

char ** Args_to_arglist(Args args){
    char **arg_list=new char*[args.size()+1];
    int i;
    for(i=0;i<args.size();i++){
        arg_list[i]=new char[args[i].size()+1];
        strcpy(arg_list[i],args[i].c_str());
    }
    arg_list[i]=NULL;
    return arg_list;
}

void free_arglist(char** list){
    int i=0;
    while (list[i])
    {
        free(list[i]);
        i++;
    }
    free(list);
}