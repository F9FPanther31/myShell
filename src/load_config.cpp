#include "myshell.h"

int load_config(config *config){
    //get work dir
    string path =getcwd(NULL,0);
    path+="mesh";
    setenv("myshell",path.c_str(),0);
    //get hostname
    gethostname(config->host_name,sizeof(config->host_name));
    //get user_info
    config->user=getpwuid(getuid());
}