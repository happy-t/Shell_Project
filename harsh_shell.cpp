#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cstring>
#define MAX_SIZE 2048
#define TKSIZE 64
#define DELMT " \t\a\n\r"
char *init_dir;
char *current_dir;
#define clear() printf("\033[H\033[J")

using namespace std;

void displayPrompt(char s[])
{
	static int a = 1;
	if(a)
	{
		clear();
		a = 0;
	}
	cout<<s<<" >>";
}


char *takeInput()
{
	int bfs = MAX_SIZE;
	int position = 0;
	char *buffer = (char*) malloc(sizeof(char) * bfs);
	int c;

	if(!buffer)
	{
		//allocation error
	}
	while (1) {
		c = getchar();
		if(c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return buffer;
		}
		else
		{
			buffer[position] = c;
		}

		position++;

		if(position >= bfs)
		{
			buffer = (char*) realloc(buffer, bfs + MAX_SIZE);

			if(!buffer)
			{
				//allocation error
			}
		}
	}
}

char **split_cmd(char *line)
{
	int tks = TKSIZE;
	char **tokens = (char**) malloc(sizeof(char*)*tks);
	char *token;
	int position = 0;

	if(!tokens)
	{
		//allocation Error
	}

	token = strtok(line, DELMT);
	while(token != NULL)
	{
		tokens[position] = token;
		position++;

		if(position >= tks)
		{
			tokens = (char**) realloc(tokens, tks + TKSIZE);
			if(!tokens)
			{
				cout<<"Allocation Error\n";
				exit(1);
			}
		}

		token = strtok(NULL, DELMT);
	}

	tokens[position] = NULL;
	return tokens;

}

// int run(char **args)
// {
// 	int pid;
// 	int status;
//
// 	pid = fork();
// 	if(pid == 0)
// 	{
// 		if(execvp(args[0], args) == -1)
// 		{
// 			cout<<"Error\n";
// 			exit(1);
// 		}
// 		exit(1);
// 	}else if(pid < 0)
// 	{
// 		exit(0);
// 	}
// 	else{
// 		do
// 		{
// 			wait(&status);
// 		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
// 	}
//
// 	return 1;
// }

int happy_cd(char **args);
int happy_help(char **args);
int happy_exit(char **args);
int happy_ls(char **args);
int happy_clear(char **args);
int happy_mycat(char **args);

char *b_str[] = {(char*)"mycd", (char*)"help", (char*)"exit"
				, (char*)"show", (char*)"clear", (char*)"mycat"};

int (*b_func[])(char **) = {
	&happy_cd,
	&happy_help,
	&happy_exit,
	&happy_ls,
	&happy_clear,
	&happy_mycat
};

int nums_b()
{
	int k = sizeof(b_str)/sizeof(char *);
	return k;
}

int happy_cd(char **args)
{
	if(args[1] == NULL)
	{
		cout<<"Argument Expected\n";
		return 1;
	}
	else
	{
		if(chdir(args[1]) != 0)
			cout<<"Error\n";
	}

	return 1;
}

int happy_help(char **args)
{
	int i;
	cout<<"\t Harsh Tripathi\n";
	cout<<" This Shell belongs to Harsh Tripathi\n";
	cout<<" The Following Commands are built in till now\n";

	for(i=0; i<nums_b(); i++)
	{
		cout<<"-->"<<b_str[i]<<endl;
	}

	cout<<"\t Use at your own risk ;)\n";
	return 1;
}

int happy_exit(char **args)
{
	return 0;
}

int happy_ls(char **args)
{
	int pid;
	int status;
	char *path = (char*) malloc(sizeof(char)*MAX_SIZE);
	pid = fork();
	if(pid == 0)
	{
		strncpy(path, init_dir, MAX_SIZE);
		strcat(path, "/show");
		if(execvp(path, args) == -1)
		{
			cout<<"Error\n";
			return 1;
		}
		exit(1);
	}else if(pid < 0)
	{
		exit(0);
	}
	else{
		do
		{
			wait(&status);
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(path);
	return 1;
}

int happy_clear(char **args)
{
	clear();
	return 1;
}

int happy_mycat(char **args)
{
	int pid;
	int status;
	char *path = (char*)malloc(sizeof(char)*MAX_SIZE);
	pid = fork();

	if(pid == 0)
	{
		strncpy(path, init_dir, MAX_SIZE);
		strcat(path, "/mycat");

		if(execvp(path, args) == -1)
		{
			cout<<"Error\n";
			return 1;
		}

	}
	else if(pid < 0)
	{
		cout<<"Error\n";
		return 1;
	}
	else
	{
		do
		{
			wait(&status);
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(path);
	return 1;
}

int execute(char **args)
{
	int i;

	if(args[0] == NULL)
		return 1;

	for(i=0; i<nums_b(); i++)
	{
		if(strcmp(args[0], b_str[i]) == 0)
			return (*b_func[i])(args);
	}

	cout<<"Invalid Command, Try help\n";
	return 1;
}


int main()
{

	char *line;
	char **args;
	int status;

	current_dir = (char*) malloc(sizeof(char) * MAX_SIZE);
	init_dir = (char*) malloc(sizeof(char) * MAX_SIZE);
	getcwd(init_dir, MAX_SIZE);
	do
	{
		displayPrompt(getcwd(current_dir, MAX_SIZE));
		line = takeInput();
		args = split_cmd(line);
		status = execute(args);

	}while(status);

	exit(0);

}
