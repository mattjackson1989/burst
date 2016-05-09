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
	int status;
	pthread_t tid;

};

void* copyfile_thread(void* args){
	
	struct threadCopy* filecopy = args;
	char buffer[BUF_SIZE];
	ssize_t ret_in, ret_out;
	printf("Thread processed\n");
	
		while((ret_in = read(filecopy->infd, &buffer, BUF_SIZE)) > 0){
			ret_out = write (filecopy->outfd, &buffer, (ssize_t) ret_in);
			
			if(ret_out != ret_in){
				perror("write");
				return 0;
			}	
		}

}
int main(int argc, char* argv[]){ 
	
	int err;
	ssize_t ret_in, ret_out;
	char buffer[BUF_SIZE];
	
	
	int copies = atoi(argv[3]);
	struct threadCopy* fileCopy = calloc(copies,sizeof(struct threadCopy));
	
	for(int i = 0; i < copies; i++){
		int input_fd = open(argv[1], O_RDONLY);	
	
		char filename[512];
	
		int test;
	
		snprintf(filename, 512, "%s%d.txt", argv[2], i+1);

		fprintf(stderr, "%s\n", filename);

		int output_fd =open(filename,(O_WRONLY | O_CREAT), (S_IRUSR | S_IWUSR)); 
	

		fileCopy[i].infd = input_fd;
		fileCopy[i].outfd = output_fd;
	
		err = pthread_create(&(fileCopy[i].tid),NULL,&copyfile_thread,&(fileCopy[i]));

		if(err !=0){
			printf("\nCan't create thread: [%s]", strerror(err));
		}
		else{
			printf("\nSecond thread processing\n");
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

	sleep(10);
	return 0;
}
