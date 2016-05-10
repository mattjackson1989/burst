/*

	Matt Jackson
	burst.c
*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#define BUF_SIZE 512

struct threadCopy {

	
	int infd;
	int outfd;
	//current line count
	int lCount;
	// copies to make
	int copies;
	// actually lines of current file
	int fLines;
	// lines to write
	int linesToWrite;
	// start line
	int start;
	// finish line
	int finish;
	// File directories
	FILE* infile;
	FILE* outfile;
	// status
	int status;
	// pthread_t id
	pthread_t tid;

};
// ~THREAD F(x)
void* copyfile_thread(void* args){
	
	int linecount = 0;	
	
	char line[BUF_SIZE];
	struct threadCopy* filecopy = args;
	char copyLines[500][BUF_SIZE];
	char buffer[BUF_SIZE];
	ssize_t read_in, read_out;

	int i =0;

		
	while(i < 50 && fgets(copyLines[i], sizeof(copyLines[0]), filecopy->infile)){


		if(i <= filecopy->finish && i >= filecopy->start )
			fputs(copyLines[i], filecopy->outfile);
	
		i++;
	}
	// i equals the number of lines to get

	/*
	for(int i=0; i< filecopy->lCount && fgets(line, sizeof(line), filecopy->infile); i++)
		linecount = i;
		printf("%d", linecount);
		fputs(line, filecopy->outfile);
	*/
	/*
	while((read_in = read(filecopy->infd, &buffer, BUF_SIZE)) > 0){
	
		read_out = write (filecopy->outfd, &buffer, (ssize_t) read_in);
			
		if(read_out != read_in){
			perror("write");
			return 0;
		}	
	}
	*/
	printf("\nProcessed Thread\n");
	fclose(filecopy->infile);
	fclose(filecopy->outfile);
}

// ~MAIN~
int main(int argc, char* argv[]){ 
	
	int err;
	ssize_t ret_in, ret_out;
	char buffer[BUF_SIZE];
	
	// How many copies	
	int copies = atoi(argv[3]);
	struct threadCopy* fileCopy = calloc(copies,sizeof(struct threadCopy));

	int lines = 0;
	FILE* input_fd = fopen(argv[1], "r");	
	char ch;

	int dividedLines;
	// Get number of lines of file	
	while((ch=fgetc(input_fd))!=EOF){
		if(ch == '\n'){
			lines++;
		}
	}
	
	
	printf("lines used: %d", lines);
	fclose(input_fd);

	// SPAWN THE THREADS AND GIVE WORK
	for(int i = 0; i < copies; i++){

		fileCopy[i].lCount =atoi( argv[4]);
		fileCopy[i].linesToWrite = atoi( argv[4]);
		//fileCopy[i].fLines = 500; 
		// first case
		if(i == 0){
			fileCopy[i].start = 0;
			fileCopy[i].finish = fileCopy[i].linesToWrite;
		}
		if(i >0){
			fileCopy[i].start = fileCopy[i].linesToWrite * i;
			fileCopy[i].finish += fileCopy[i].linesToWrite *(i + 1);

			printf("%d", fileCopy[i].start);

		}

		char filename[512];
		
		// snprintf(filename, 512, "%s%d.txt", argv[2], i+1);

		// fprintf(stderr, "%s\n", filename);
		sprintf(filename, "%s%d", argv[2], i+1);
				

		// Open file locations
		fileCopy[i].infile = fopen(argv[1], "r");
		fileCopy[i].outfile = fopen(filename, "wb");
		

		// assign number of total lines of file
		fileCopy[i].fLines = lines;
		fileCopy[i].copies = copies; 

		//fileCopy[i].infd = input_fd;
		//fileCopy[i].outfd = output_fd;
	
		err = pthread_create(&(fileCopy[i].tid),NULL,&copyfile_thread,&(fileCopy[i]));

		if(err !=0){
			printf("\nCan't create thread: [%s]", strerror(err));
		}
		
		
	}
	/*
	// open file
	input_fd = open(argv[1], O_RDONLY);
	if(output_fd == -1){
		perror("open");
		return 2;
	}

	// form the output file
	output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
	if(output_fd == -1){
		perror("open");
		return 3;
	}

	// copy to new file
	while((ret_in = read(input_fd, &buffer, BUF_SIZE)) > 0){
		ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
		if(ret_out != ret_in){
			perror("write");
			return 4;
		}
	}

	close(input_fd);
	close(output_fd);
	*/

	sleep(5);
	free(fileCopy);
	return 0;
}
