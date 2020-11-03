/*
 * Consumidor.
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

#define PROD_MAILBOX 453
#define CONS_MAILBOX 454
#define BOX_SIZE 10
#define MAX_MSGS 200

int flag, msgflg, msqid_cons, msqid_prod;

void send_request(int msqid, int* index, message m){

	/* preenche estrutura de mensagem */
	m.type = 1;
	sprintf(m.content, "%s %d", "Requisitando resposta",(*index)++);

	/* envia */
	flag = msgsnd(msqid, &m, strlen(m.content) + 1, 0);
	printf("o resultado eh: %d\n", flag);

}

void get_response(int msqid, message* m){

	/* recebe mensagem */
	msgflg = MSG_NOERROR;
	flag = msgrcv(msqid, m, 100, 0, msgflg);

	if(flag >= 0) {
  		printf("o tipo da mensagem eh: %ld\n", m->type);
  		printf("o conteudo da mensagem eh: %s\n", m->content);
	} else {
  		perror("erro na recepcao");
	}

}

int main() {

	int index = 0;

	message m;

	/* cria estrutura de mensagem */
	msqid_cons = msgget(CONS_MAILBOX, 0666 | IPC_CREAT);
	if(msqid_cons <= 0) {
  		perror("erro na criacao de mailbox consumidor");
  	}

	/* cria estrutura de mensagem */
	msqid_prod = msgget(PROD_MAILBOX, 0666 | IPC_CREAT);
	if(msqid_prod <= 0) {
  		perror("erro na criacao de mailbox produtor");
  	}

	for(int i=0; i < BOX_SIZE; i++)
		send_request(msqid_prod, &index, m);

	while(index < MAX_MSGS + BOX_SIZE){
		get_response(msqid_cons, &m);
		if(index < MAX_MSGS)
			send_request(msqid_prod, &index, m);
	}
}

