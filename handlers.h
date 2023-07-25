#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int handleCommand(char *msg);

int handleFileValidation(char* filename);

void handleSelect(char *filename);

void saveFile(const char* nomeArquivo, const char* conteudo, const char* pastaDestino);

bool endsWith(const char *str, const char *suffix);

void removeEnd(char *str);

void replaceNewline(char *str);

void replaceEscapedNewline(char *str);

