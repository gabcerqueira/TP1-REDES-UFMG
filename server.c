#include "common.h"
#include "handlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 500


//Passagens de parametros de entrada
void usage(int argc, char **argv)
{
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

void sendResponse(int csock, char *msg)
{
    size_t msgSize = strlen(msg);
    char content[msgSize + 4];

    sprintf(content, "%ld-%s", msgSize, msg);
    size_t count = send(csock, content, strlen(content) + 1, 0);
    if (count != strlen(content) + 1)
    {
        logexit("error while sending message to client");
    }
}

void substringFromNChar(const char *str, char *result,int n) {
    if (strlen(str) >= n) {
        strcpy(result, str + (n -1));
    }
}

int exec(int csock)
{
    
    char buf[BUFSZ];
    char reader[BUFSZ];
    int exitCode = 0;
    char response[BUFSZ];
    char filename[100];
    char content[500];
    char contentAux[500];
    char* dirDest = "serverFiles";
    FILE *file;

    for (;;)
    {
        
        bzero(buf, BUFSZ);
        bzero(reader, BUFSZ);
        size_t count = recv(csock, reader, BUFSZ - 1, 0);
        
        strcpy(buf,reader);
        bzero(filename,100);
        bzero(content,500);
        bzero(contentAux,500);
        bzero(response,BUFSZ);

        if(count != 0){
            printf("[SERVER] received: %s\n", buf);
            replaceEscapedNewline(buf);
        }
        


         if ((strlen(buf) == 4) && (strcmp(buf, "exit") == 0)){
            sprintf(response,"exit");
            exitCode = 1;
            return exitCode;
        }

        while(1){

            //VERIFICAÇÃO DA EXTENSÃO DO DADO RECEBIDO E TRATAMENTO DO FILENAME E CONTENT
            if (strstr(buf, ".txt") != NULL || endsWith(buf, ".txt")) {


            char *separator = strstr(buf, ".txt");

             if (separator != NULL) {
            
            size_t filename_len = separator - buf;

            
            strncpy(filename, buf, filename_len);
            filename[filename_len] = '\0';

            
            strcpy(content, separator + 1);

            //FORMATAÇÃO DA ENTRADA    
            substringFromNChar(content,contentAux,4);
            removeEnd(contentAux);
            
            }

            char caminhoCompleto[1000]; // Ajuste o tamanho conforme necessário
            snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", dirDest, strcat(filename,".txt"));
            file = fopen(caminhoCompleto,"r");

            if (file == NULL) {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s received", filename);
                sendResponse(csock, response);
                break;
                
            }else {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s overwritten", filename);
                sendResponse(csock, response);
                break;
            }


            



        } 
        else if (strstr(buf, ".cpp") != NULL || endsWith(buf, ".cpp")) {

        
            char *separator = strstr(buf, ".cpp");

             if (separator != NULL) {
            
            size_t filename_len = separator - buf;

            
            strncpy(filename, buf, filename_len);
            filename[filename_len] = '\0';

            
            strcpy(content, separator + 1);

           
            substringFromNChar(content,contentAux,4);
            removeEnd(contentAux);
            
            }

             char caminhoCompleto[1000]; 
            snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", dirDest, strcat(filename,".cpp"));
            file = fopen(caminhoCompleto,"r");

            if (file == NULL) {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s received", filename);
                sendResponse(csock, response);
                break;
                
            }else {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s overwritten", filename);
                sendResponse(csock, response);
                break;
            }





        } 
        else if (strstr(buf, ".c") != NULL || endsWith(buf, ".c")) {

            char *separator = strstr(buf, ".c");

             if (separator != NULL) {
            
            size_t filename_len = separator - buf;

            
            strncpy(filename, buf, filename_len);
            filename[filename_len] = '\0';

            
            strcpy(content, separator + 1);

           
            substringFromNChar(content,contentAux,2);
            removeEnd(contentAux);
            
            }

             char caminhoCompleto[1000]; 
            snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", dirDest, strcat(filename,".c"));
            file = fopen(caminhoCompleto,"r");

            if (file == NULL) {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s received", filename);
                sendResponse(csock, response);
                break;
                
            }else {
               
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s overwritten", filename);
                sendResponse(csock, response);
                break;
            }

        
        } else if (strstr(buf, ".py") != NULL || endsWith(buf, ".py")) {

            char *separator = strstr(buf, ".py");

             if (separator != NULL) {
            
            size_t filename_len = separator - buf;

            
            strncpy(filename, buf, filename_len);
            filename[filename_len] = '\0';

            
            strcpy(content, separator + 1);

            
            substringFromNChar(content,contentAux,3);
            removeEnd(contentAux);
            
            }

             char caminhoCompleto[1000]; 
            snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", dirDest, strcat(filename,".py"));
            file = fopen(caminhoCompleto,"r");

            if (file == NULL) {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s received", filename);
                sendResponse(csock, response);
                break;
                
            }else {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s overwritten", filename);
                sendResponse(csock, response);
                break;
            }

        
        } else if (strstr(buf, ".tex") != NULL || endsWith(buf, ".tex")) {

            char *separator = strstr(buf, ".tex");

             if (separator != NULL) {
            
            size_t filename_len = separator - buf;

            
            strncpy(filename, buf, filename_len);
            filename[filename_len] = '\0';

            
            strcpy(content, separator + 1);

            
            substringFromNChar(content,contentAux,4);
            removeEnd(contentAux);
            
            }

             char caminhoCompleto[1000]; 
            snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", dirDest, strcat(filename,".tex"));
            file = fopen(caminhoCompleto,"r");

            if (file == NULL) {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s received", filename);
                sendResponse(csock, response);
                break;
                
            }else {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s overwritten", filename);
                sendResponse(csock, response);
                break;
            }

        
        } else if (strstr(buf, ".java") != NULL || endsWith(buf, ".java")) {

            char *separator = strstr(buf, ".java");

             if (separator != NULL) {
            
            size_t filename_len = separator - buf;

            
            strncpy(filename, buf, filename_len);
            filename[filename_len] = '\0';

           
            strcpy(content, separator + 1);

            
            substringFromNChar(content,contentAux,5);
            removeEnd(contentAux);
            
            }

             char caminhoCompleto[1000]; 
            snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", dirDest, strcat(filename,".java"));
            file = fopen(caminhoCompleto,"r");

            if (file == NULL) {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s received", filename);
                sendResponse(csock, response);
                break;
                
            }else {
                
                
                saveFile(filename,contentAux,dirDest);
                sprintf(response, "file %s overwritten", filename);
                sendResponse(csock, response);
                break;
            }


        } else {

       
        }

        }

    }

    return exitCode;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage))
    {
        usage(argc, argv);
    }

    int serversock = socket(storage.ss_family, SOCK_STREAM, 0);
    if (serversock == -1)
    {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(serversock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)))
    {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(serversock, addr, sizeof(storage)))
    {
        logexit("bind");
    }

    if (0 != listen(serversock, 10))
    {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);

    
    
    while (1)
    {
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(serversock, caddr, &caddrlen);
        if (csock == -1)
        {
            logexit("accept");
        }

        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);
        printf("[SERVER] connection from %s\n", caddrstr);
        
        if (exec(csock))
            break;

        close(csock);
    }

    printf("Shutting down server...\n");
    close(serversock);
    exit(EXIT_SUCCESS);
}