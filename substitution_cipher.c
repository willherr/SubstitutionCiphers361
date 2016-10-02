/***********************************************************************
 * Substitution Cipher - Project 1
 *
 * William Herrmann
 * September 26th, 2016
 **********************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE      1
#define FALSE     0
#define NUMALPHA 26

/************************************************************************
 * remove duplicate characters in array word and return the result string
 ***********************************************************************/

char * removeDuplicates(char word []);


/************************************************************************
 * search for a target character in array charArray found at an index 
 * less than num. return a non-zero integer if found, otherwise return 0
 ***********************************************************************/

int targetFound(char charArray[], int num, char target);


/***********************************************************************
 * initialize the encrypt array with appropriate cipher letters 
 * according to the given key
 **********************************************************************/

void initializeEncryptArray(char key[], char encrypt[]);


/***********************************************************************
 * initialize the decrypt array with appropriate substitute letters 
 * based on the encrypt array
 **********************************************************************/

void initializeDecryptArray(char encypt[], char decrypt[]);


/***********************************************************************
 * process data from the input file and write the result to the output 
 * file. pass the encrypt array to parameter substitute if encryption is 
 * intended pass the decrypt array to parameter substitute if decryption
 * is intended
 **********************************************************************/

void processInput(FILE * inf, FILE * outf, char substitute[]);


/***********************************************************************
 * main function to complete encryption/decryption of given files.
 * command line arguments are cipher option, key, infile, outfile
 **********************************************************************/
int main(int argc, char* argv[])
{
  int encrypting = TRUE;
  char *key, encrypt[NUMALPHA+1], decrypt[NUMALPHA+1];
  FILE *fin, *fout;
  
  if (argc != 5){
    printf ("\nUsage: cipher option, key (as uppercase string), infile, outfile\n");
    printf ("Option 1 for encryption and 2 for decryption\n\n");
    exit(1);
  }
  
  if(atoi(argv[1]) == 2)
    encrypting = FALSE;

  fin = fopen(argv[3], "r");
  fout = fopen(argv[4], "w");
  if (fin ==  NULL || fout == NULL){
    printf("File could not be opened\n");
    exit(1);
  }

  key = removeDuplicates(argv[2]);
  if(strlen(key) > NUMALPHA){
    fprintf(stdout, "\nYour key cannot be greater than 26 characters.\n");
    exit(1);
  }
  
  initializeEncryptArray(key, encrypt);
  initializeDecryptArray(encrypt, decrypt);
 
  
  if(encrypting){              
    processInput(fin, fout, encrypt);
    fprintf(stdout, "The encrypted file %s has been created\n\n", argv[4]);
  } else {                          
    processInput(fin, fout, decrypt);
    fprintf(stdout, "The decrypted file %s has been created\n\n", argv[4]);
  }
  
  fclose(fin);
  fclose(fout);
  free(key);
 
  return 0;
}



//reading and writing encrypting/decrypting operation
void processInput(FILE * inf, FILE * outf, char substitute[]){
  char ch;
  int i = 0;

  while (fscanf(inf, "%c", &ch) != EOF){
    fprintf(outf, "%c", substitute[ch-'A']);
    i++;
  }
}



//decrypt array initialization
void initializeDecryptArray(char encrypt[], char decrypt[]){
  int i;
  
  for(i=0; i < NUMALPHA; i++){
    decrypt[encrypt[i]-'A'] = 'A' + i;
  }
  decrypt[i] = '\0';

  fprintf(stdout, "decrypt substitution: %s\n\n", decrypt);
}



//encrypt array initialization
void initializeEncryptArray(char key[], char encrypt[]){
  int i, k = 0;

  for(i=0; i < NUMALPHA; i++){
    if(i < strlen(key)){
      encrypt[i] = key[i];
    } else {
      if(!targetFound(key, NUMALPHA + 1, 'Z' - k))
	encrypt[i] = 'Z' - k;
      else
	i--;
      k++;
    }
  }
  encrypt[i] = '\0';
  fprintf(stdout,"\nencrypt substitution: %s\n", encrypt);
}



//helper to search array and find duplicate letter
int targetFound(char charArray[], int num, char target){
  int i;

  for(i=0; i < strlen(charArray); i++){
    if(i < num && charArray[i] == target)
      return TRUE;
  }

  return FALSE;  
}



//helper to fill a new array the order of the letters from word without duplicates
char * removeDuplicates(char word []){
  char *key = (char*) malloc(sizeof(char)*26);
  int i, k = 0;

  for(i=0; i < strlen(word); i++){
    if(!targetFound(word, i, word[i])){
      key[k++] = word[i];
    }
  }
  key[k] = '\0';

  printf("\nword in: %s\nkey: %s\n", word, key);
  return key;
}
