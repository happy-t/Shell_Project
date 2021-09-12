#include <iostream>
#include <dirent.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{

	DIR *dp;
	struct dirent *dirp;

	if(argc == 1)
	{
		dp = opendir(".");
	}

	else if (argc > 2)
	{
		cout<<"Usage: ./show directory_name \n";
		exit(0);
	}

	else
	{
		dp = opendir(argv[1]);
	}
	if (dp == NULL)
	{
		cout<<"can’t open \""<<argv[1]<<"\"\n";
		exit(0);
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		if(dirp->d_name[0] != '.')
			cout<<dirp->d_name<<"  ";
	}

	cout<<"\n";

	closedir(dp);
	exit(0);
}
