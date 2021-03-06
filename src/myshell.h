//define statement code
#define CMD_EXIT_SUCCESS 0
#define UNKNOWN_FAILD 1
#define CMD_INTERNAL 4
#define CMD_EXTERNAL 5
#define BACK_GROUND 8
#define CMD_CAN_NOT_EXCUTE 126
#define CMD_CAN_NOT_FIND 127
#define SIGNAL_EIXT 128
#define EXCUTE_FAILD 129
#define SUCCESS 255

#include<unistd.h>
#include<sys/wait.h>
#include<sys/signal.h>
#include<sys/types.h>
#include<pwd.h>
#include<ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include<string.h>
#include <errno.h>

#include<iostream>
#include<cstdio>
#include<string>
#include<fstream>
#include<vector>
#include<cstdio>
#include<cstdlib>

using namespace std;

//config
typedef struct config
{
    struct passwd *user;
    char host_name[64];
}config;

//environment variable
extern char **environ;

typedef vector<string> Args;

int load_config(config *config);
string get_home(config *cfg);
int print_prompt(config *config);
Args split_cmd(string cmd);

int cmd_analysis(Args args,config* cfg);
int cmd_execute(Args args ,config *cfg);
int redirection(Args args,config *cfg);

char ** Args_to_arglist(Args args);
void free_arglist(char** list);