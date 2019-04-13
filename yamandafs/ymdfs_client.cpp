#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdint.h>


#include "ymdfs.h"

void print_usage()
{
	printf("Use:\nbfs_client <command> path\n");
	printf("\t command:\n");
	printf("\t    ls <path> : list the directory\n");
	printf("\t    cat <path>... : cat the file\n");
	printf("\t    mkdir <path>... : make directory\n");
	printf("\t    mv <srcpath> <destpath> : rename directory or file\n");
	printf("\t    touchz <path>... : create a new file\n");
	printf("\t    rm <path>... : remove a file\n");
	printf("\t    get <bfsfile> <localfile> : copy file to local\n");
	printf("\t    put <localfile> <bfsfile> : copy file from local to bfs\n");
	printf("\t    rmdir <path>... : remove empty directory\n");
	printf("\t    rmr <path>... : remove directory recursively\n");
	printf("\t    du <path>... : count disk usage for path\n");
	printf("\t    stat : list current stat of the file system\n");
	printf("\t    ln <src> <dst>: create symlink\n");
	printf("\t    chmod <mode> <path> : change file mode bits\n");
}


int YmdfsTouchz(yamanda::ymdfs::ymdfs *ymdfs,int argc,char *argv[])
{
	if (argc < 1)
	{
		print_usage();
		return 0;
	}
	int32_t ret = 0;
	int i = 0;
	yamanda::ymdfs::File *file;

	for (i = 0;i < argc;i++)
	{
		ret = ymdfs->OpenFile(argv[i],O_WRONLY,0644,&file,yamanda::ymdfs::WriteOption());
		if (0 != ret)
		{
			fprintf(stderr,"open %s failed\n",argv[i]);
			return 1;
		}
	}
	return 0;
}

int YmdRm(yamanda::ymdfs::ymdfs *ymdfs,int argc,char *argv[])
{
	if (argc < 1)
	{
		print_usage();
		return 0;
	}
	int32_t ret = 0;
	int i = 0;

	for (i = 0; i < argc; i++)
	{
		ret = ymdfs->DeleteFile(argv[i]);
		if (0 != ret)
		{
			fprintf(stderr, "delete %s failed\n", argv[i]);
			return 1;
		}
	}
	return 0;
}
