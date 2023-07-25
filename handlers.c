#include "handlers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


//1 pra select
//2 pra send
//3 pra exit
//0 pra default
int handleCommand(char *msg)
{

    if (strstr(msg, "select file") != NULL)
    { // select file

        return 1;
        
    }
    else if (strstr(msg, "send file") != NULL)
    { //send file
        return 2;
        
    }
    else if (strstr(msg, "exit") != NULL)
    { // exit
        
        return 3;
    }
    
    else
    {
        return 0;
    }
}





//Verificar validade do arquivo

//1 para valido e 0 para nao valido 2 para nao existe
int handleFileValidation(char* filename){

    
    char *ext;
    FILE *arq;
    // selecionar o arq para envio ao servidor
    ext = strrchr(filename, '.');
    
    arq = fopen(filename, "r");
    
    if (arq == NULL) {
				
        return 2;
    }else {
	    fclose(arq);
				
				
	}

    //Extensoes

    if(strstr(ext, ".txt") != NULL){
       
        return 1;
    }

    else if(strstr(ext, ".c") != NULL){
        return 1;

    }
    else if(strstr(ext, ".cpp") != NULL){
        return 1;

    }
    else if (strstr(ext, ".py") != NULL ){
        return 1;

    }
    else if (strstr(ext, ".tex") != NULL){
        return 1;

    }
    else if(strstr(ext, ".java") != NULL){
        return 1;

    }
    else {
        return 0;
    }


}




void saveFile(const char* nomeArquivo, const char* conteudo, const char* pastaDestino) {
    
    char caminhoCompleto[1000]; 
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", pastaDestino, nomeArquivo);

    
    FILE* arquivo = fopen(caminhoCompleto, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    
    fprintf(arquivo, "%s", conteudo);

    
    fclose(arquivo);

}

bool endsWith(const char *str, const char *suffix) {
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (str_len < suffix_len) {
        return false;
    }

    return strncmp(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

void removeEnd(char *str) {
    char *endPtr = strstr(str, "\\end"); 

    if (endPtr != NULL) {
        
        *endPtr = '\0';
    }
}

void replaceNewline(char *str) {
    int i, j;
    int len = strlen(str);
    char result[2 * len];  
    
    for (i = 0, j = 0; i < len; i++) {
        if (str[i] == '\n') {
            result[j++] = '\\';
            result[j++] = 'n';
        } else {
            result[j++] = str[i];
        }
    }
    
    result[j] = '\0';  
    
    strcpy(str, result);  
}

void replaceEscapedNewline(char *str) {
    int i, j;
    int len = strlen(str);
    char result[len + 1];  
    
    for (i = 0, j = 0; i < len; i++) {
        if (str[i] == '\\' && str[i+1] == 'n') {
            result[j++] = '\n';
            i++;  
        } else {
            result[j++] = str[i];
        }
    }
    
    result[j] = '\0';  
    
    strcpy(str, result);  
}