#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
  int pipe_fd[2];
	int pipe_fd2[2];
  int pid; 
  int pid_2;

  char *cat_args[] = {"cat", "scores", NULL};
  
  
  char *grep_args[] = {"grep", argv[1], NULL};
	
  
  char *sort_args[] = {"sort", NULL};

  
	if (pipe(pipe_fd) == -1) { 
			fprintf(stderr, "The Pipe Failed" ); 
			return 1; 
	} 
	if (pipe(pipe_fd2) == -1) { 
			fprintf(stderr, "The Pipe Failed" ); 
			return 1; 
	} 

	pid = fork();

  if (pid == 0) {
		  
			pid_2 = fork();
			if (pid_2 == 0) {
				dup2(pipe_fd2[0], 0);

				
				close(pipe_fd[0]);
				close(pipe_fd[1]);
        
				close(pipe_fd2[0]);
				close(pipe_fd2[1]);
        
				execvp(sort_args[0], sort_args);

			} else {
			
				dup2(pipe_fd[0], 0);
				dup2(pipe_fd2[1], 1);
				
			
				close(pipe_fd[0]);
				close(pipe_fd[1]);
        
				close(pipe_fd2[0]);
				close(pipe_fd2[1]);

			
				execvp("grep", grep_args);
			}
    
    }else {
      
      dup2(pipe_fd[1], 1);

     
			close(pipe_fd[0]);
			close(pipe_fd[1]);
    
			close(pipe_fd2[0]);
			close(pipe_fd2[1]);

      execvp("cat", cat_args);
}
}