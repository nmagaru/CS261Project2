#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
 // debug mode code
 bool debugmode;
 int stringcompare;

 // loop through possible ARGuments
 for (int h = 0; h < argc; h++)
 {
	stringcompare = strcmp(argv[h], "-d");

	// update debug boolean if debug flag found
	if (stringcompare == 0)
	{
		debugmode = true;
		break;
	}

	// debug booleon is false otherwise, do not show debug statements
	debugmode = false;
 }


 // implement stack struct as dynamic array
 typedef struct stack {
	char* stackarr;
	int stacktop;
	int stacksize;
	int maxstacksize;
 } Stack;


 // function for initializing stack
 void init (Stack* curstack)
 {
	curstack->stacktop = -1;
	curstack->stacksize = 0;
	curstack->maxstacksize = 10;
	// allocate memory for the stack array of characters
	curstack->stackarr = (char *)malloc(sizeof(char) * curstack->maxstacksize);
 }


 // function to check if stack is empty
 bool is_empty (Stack* curstack)
 {
	// check if stack is empty (stack size is 0)
	if (curstack->stacksize == 0) 
		return true;
	
	return false;
 }


 // function to push in input character into the stack
 void push (Stack* curstack, char inputchar)
 {
	int copycount = 0;
	int prevmaxsize = curstack->maxstacksize;

	// check if stack is full, dynamically grow array if full
 	if (curstack->stacksize == curstack->maxstacksize) 
	{
		char* tempstack = curstack->stackarr;
		curstack->stackarr = (char * )malloc(sizeof(char) * curstack->maxstacksize * 2);
		
		for (int i = 0; i < curstack->maxstacksize; i++ )
		{	
			curstack->stackarr[i] = tempstack[i];
			copycount++;
		}	
		free(tempstack);
		curstack->maxstacksize *= 2;

	// debug: show old/new max array sizes and how many values are copied over
	if (debugmode)
		printf("\n[DEBUG] Previous Max Size: %d\nCurrent Max Size: %d\nNum Values Copied: %d\n", prevmaxsize, 				curstack->maxstacksize, copycount);
	}

	// debug: show item pushed into stack
	if (debugmode)
		printf("\n[DEBUG] Pushed: %c\n", inputchar);

	// push in value into stack and update respective stack values
	curstack->stacktop++;
	curstack->stacksize++;
	curstack->stackarr[curstack->stacktop] = inputchar;	
 }


 // function to pop/remove top stack element
 void pop (Stack* curstack)
 {
	// only pop element if the stack is not empty
	if (!is_empty(curstack)) 
	{
		// debug: show item popped from stack
		if (debugmode)
			printf("\n[DEBUG] Popped: %c\n", curstack->stackarr[curstack->stacktop]);

		// subtract from stack size and from stack top to remove top element
		curstack->stacksize--;
		curstack->stacktop--;
	}
 }


 // function to access/return top stack element
 char top (Stack* curstack)
 {
	// only return top element if top element exists (stack is not empty)
	if (!is_empty(curstack))
		return curstack->stackarr[curstack->stacktop];
 }


 // function to clear stack
 void clear (Stack* curstack)
 {	
	// free allocated array memory to clear the stack
	free(curstack->stackarr);
 }


 // function to remove letters from decoded words
 void RemoveExtraLetters (char *str, int strlength)
 {
	// loop through the given string
	int j = 0;
 	for (int i = 0; i < strlength; i++)
       	{
		// check for L alphabet, put all letters in the front of the string consecutively
       		if (( (str[i] == 'a') || (str[i] == 'b') || (str[i] == 'c') || (str[i] == 'd') )) 
		{
			str[j] = str[i];
			j++;
		}
	}
	
	str[j] = '\0';	
 }


 char input[300];

 // debug: starting message to indiccate debug mode
 if (debugmode)
	 printf("Debug mode: ON\n");
	
	 /* set up an infinite loop */
 while (1)
 {
   /* BASE CODE */
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';


   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;
 
   /*Start tokenizing the input into words separated by space
    We use strtok() function from string.h*/
   /*The tokenized words are added to an array of words*/
   
   char delim[] = " ";
   char *ptr = strtok(input, delim);
   int j = 0 ; 
   char *wordList[15];
   int wordcount = 0; // added word count to loop through word list

	while (ptr != NULL)
	{	
		wordList[j++] = ptr;
		ptr = strtok(NULL, delim);
		wordcount++;
	}

   /* END BASE CODE */
   
   /*Run the algorithm to decode the message*/
	Stack mystack;
	init(&mystack);

	char curchar;
	int wordlength;
	
	// loop through word list from input
	for (int k = 0; k < wordcount; k++) 
	{
		wordlength = strlen(wordList[k]);
		
		// loop through the word itself
		for (int l = 0; l < wordlength; l++) 
		{
			curchar = wordList[k][l];
			
			// check if the char is part of L, push into the stack
			if ((curchar == 'a') || (curchar == 'b') || (curchar == 'c') || (curchar == 'd'))
				push(&mystack, curchar);
			
			// check if the char is part of L2, compare if matched to top of stack char
			switch (curchar)
			{	
			        case 'm': if (top(&mystack) == 'a')
						pop(&mystack);

					  break;
				case 'n': if (top(&mystack) == 'b')
						pop(&mystack);

					  break;
				case 'o': if (top(&mystack) == 'c')
						pop(&mystack);
					  
					  break; 
				case 'p': if (top(&mystack) == 'd')
						pop(&mystack);

					  break;
				default:  break;
			}
		}
			
		// check if stack is empty: stack emptiness determines if word is completely mapped
		if(is_empty(&mystack)) 
		{
			RemoveExtraLetters(wordList[k], wordlength);
			printf("%s ", wordList[k]);
		}
		else
		{
			clear(&mystack);
			init(&mystack);
		}
	}

	printf("\n");
 }


 printf ("\nGoodbye\n");





	return 0;
}
