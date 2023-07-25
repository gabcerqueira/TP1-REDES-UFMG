#include "common.h"
#include "handlers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSZ 500

void usage(int argc, char **argv)
{
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

// Receber a resposta do server
int receiveResponse(int sfd)
{
	char buf[BUFSZ];
	char reader[BUFSZ];

	bzero(buf, BUFSZ); // resets buffer
	bzero(reader, BUFSZ);
	size_t count = recv(sfd, reader, BUFSZ - 1, 0);

	getWholeMsg(sfd, reader, buf, count);

	if (strcmp(buf, "b") == 0)
	{ // multiple returns are expected
		while (1)
		{
			bzero(buf, BUFSZ);
			bzero(reader, BUFSZ);

			count = recv(sfd, reader, BUFSZ - 1, 0);
			getWholeMsg(sfd, reader, buf, count);

			if (strcmp(buf, "e") == 0)
				return 1;

			printf("< %s\n", buf);

			if (strcmp(buf, "error") == 0)
				return 0;
		}
	}
	else
	{
		printf("< %s\n", buf);
	}

	if (strcmp(buf, "error") == 0)
		return 0;

	return 1;
}

void run(int sfd)
{
	FILE *file;
	char filenameAux[100];
	char buf[BUFSZ];
    char *filename;
    char content[BUFSZ];
	int command;
	int arquivoValido = 0;
	int fileSelected = 0;
	
	for (;;)
	{
		arquivoValido = 0;
		
		bzero(buf, BUFSZ); 
		bzero(content, BUFSZ);
		printf("> ");

		fgets(buf, BUFSZ - 1, stdin);

		//Formatar a entrada do fgets
		buf[strcspn(buf, "\n")] = '\0';

		command = handleCommand(buf);

		
		
		//SELECT FILE
		if(command == 1){
	
			

			//Recuperar o nome do arquivo
			filename = strrchr(buf, ' ');
			if (filename != NULL) {
    		filename++;
			}
			
			//Verificar validade do arquivo
			arquivoValido = handleFileValidation(filename);

			if(arquivoValido == 1){

				//arquivo selecionado
				printf("%s selected\n",filename);
				fileSelected = 1;
				strcpy(filenameAux, filename);
				
			}

			else if(arquivoValido == 0){
				//invalido o arquivo
				
				printf("%s not valid!\n",filename);
				
			}
			else if(arquivoValido == 2){
				//Arquivo nao existe
				printf("%s does not exist\n",filename);
			}



		}
		//SEND FILE
		else if (command == 2){


			if(fileSelected == 1){
				fileSelected = 0;


				//enviar arquivo

				file = fopen(filenameAux, "r");

				if (file == NULL) {
        			printf("Erro ao abrir o arquivo.\n");
					break;
        		
    			}

				char line[BUFSZ];
				bzero(line, sizeof(line));

				while (fgets(line, BUFSZ, file) != NULL) {
        			
					strcat(content,line);
    			}

				fclose(file);
				char end[] = "\\end";
				
				char trimmed[strlen(filenameAux) + strlen(content) + strlen(end)];
				bzero(trimmed, sizeof(trimmed));
				strcat(trimmed, filenameAux);
				strcat(trimmed, content);
				strcat(trimmed, end);
				replaceNewline(trimmed);
				size_t count = send(sfd, trimmed, strlen(trimmed) + 1, 0);
				

				if (count != strlen(trimmed) + 1)
				{
					logexit("error sending message to server");
				}

				if (!receiveResponse(sfd)) 
				break;

				bzero(filenameAux,100);

			}
			
			else {

				printf("no file selected!\n");
			}

		}
		//EXIT
		else if(command == 3){

			char *exit = "exit";
			//exit
			send(sfd, exit, strlen(exit) + 1, 0);
			break;

		}else {
			//exit
			break;
		}

	};
}

int main(int argc, char **argv)
{

	//VERIFICAR PARAMETROS DO TERMINAL (QUANTIDADE)
	if (argc < 3)
	{
		usage(argc, argv);
	}

	struct sockaddr_storage storage;
	//VERIFICAR CORRETUDE DE PARAMETROS
	if (0 != addrparse(argv[1], argv[2], &storage))
	{
		usage(argc, argv);
	}

	int sockfd = socket(storage.ss_family, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		logexit("socket");
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(sockfd, addr, sizeof(storage)))
	{
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	printf("connected to %s\n", addrstr);
	
	run(sockfd);

	printf("connection closed\n");
	close(sockfd);
	exit(EXIT_SUCCESS);
}