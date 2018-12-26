#ifndef kunal_shell
#define kunal_shell

#define delim1 ";"
#define delim2 " \t\n\a\r"
#define delimdash "-"
typedef long long ll;
char** pidnames;
int pidrunnings[1000000];
int pids[10000];
int pidcount;

char* root;
int saved_stdout;
int saved_stdin;
int fgpid;
char* fgcommand;

typedef struct node{
	ll time;
	char name[100000];
	char state[100000];
	char pid[100000];
}node;

char* displaypath(char* cwd);
void displayprompt();
char* readinput();
char** split_firstdelim(char* linegiven);
char** split_seconddelim(char* linegiven);
void execute_cd(char** args);
void execute_pinfo(char** args);
void execute_pwd();
void execute_echo(char** args);
void print_all(int flag_a,int flag_for_no,char* dirfile);
void print_files(int flag_a,char** dirs);
void print_detail(char* location,struct stat buff,char* dirname);
void print_all_l(int flag_a,int flag_for_no,char* dirfile);
void print_files_l(int flag_a,char** dirs);
void execute_ls(char** args);
void execute_remindme(char** args);
void execute_clock(char** args);
void execute(char** args);
void check_command(char** args);
void checkexit();
void interpretCommands(char* input_given);
char** redirect(char** args);
char** split_pipes(char* linegiven);
void funcsetenv(char** args);
void funcunsetenv(char** args);
void execute_jobs();
void kill_job(char** args);
void fg(char** args);
void bg(char** args);
void overkill();
void sigintHandler(int sig_num);
void sigintHandler2(int sig_num);
void sighandler(int sig_num); 
void sighandler2(int sig_num); 

#endif