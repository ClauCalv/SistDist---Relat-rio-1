/*
 * Produtor.
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
  long type;
  char content[100];
} message;

#define MAILBOX 453

int main() {
	int flag, msqid;
	message m;

	/* cria estrutura de mensagem */
	msqid = msgget(MAILBOX, 0666 | IPC_CREAT);
	if(msqid <= 0) {
  		perror("erro na criacao de mailbox");
  	}

	/* preenche estrutura de mensagem */
	m.type = 1;
	sprintf(m.content, "%s", "Esta eh uma mensagem de teste");

	/* envia */
	flag = msgsnd(msqid, &m, strlen(m.content) + 1, 0);
	printf("o resultado eh: %d\n", flag);
}

