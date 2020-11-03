#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h> 
#include <signal.h>

void tratador_SIGINT(int signum) {

	printf("Tratando sinal SIGINT do processo %d!\n", getpid());
	printf("Na verdade, acho que vou ignorá-lo! :-) \n");
	
} 

int main() {

	int pid;
	int status;
	sigset_t so_quit, mask;

	//Instalando tratador do sinal SIGINT
	signal(SIGINT, tratador_SIGINT);	

	//Instalando máscara para SIGQUIT
	sigemptyset(&so_quit);
	sigaddset(&so_quit, SIGKILL);
	sigaddset(&so_quit, SIGSTOP);
	sigprocmask(SIG_SETMASK, &so_quit, &mask);	

	//Chamada de sistema fork
	pid = fork();

	if (pid==0) { //Filho
	
		printf("Filho (PID %d) vai dormir por 10 segundos.\n", getpid());
		sleep(10);
		printf("Filho terminando a execução.\n");
		return 0;
		
	} else { //Pai
	
		printf("Pai com filho com PID %d.\n", pid);
		printf("Aguardando término do filho!\n");
		
		int p = waitpid(pid, &status, 0);
		printf("Pai viu filho com PID %d terminar.\n",p);
		
 		if (WIFEXITED(status)) {
        	printf("Filho terminou com status = %d.\n", WEXITSTATUS(status));
    	} else if (WIFSIGNALED(status)) {
        	printf("Filho foi morto por sinal %d.\n", WTERMSIG(status));
    	}
    	
		printf("Pai terminando a execução.\n");
	}


}

