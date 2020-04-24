#include "myshell.h"

int load_config(config *config){
    //get work dir
    string cwd =getcwd(NULL,0);
    //set shell env dir
    cwd.append("/myshell");
    setenv("shell",cwd.c_str(),1);
    //get hostname
    gethostname(config->host_name,sizeof(config->host_name));
    //get user_info
    config->user=getpwuid(getuid());
}

string get_home(config *cfg){
    string home="/home/";
    return home.append(cfg->user->pw_name);
}