#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_FILESIZE 1

void displayMenu(int mode);
void strparseHex(char *str);
void strASCII(char *str);


int main (){

    //variables declaration
    int fd = 0;
    int mode = 0;
    char input;
    char *fileName = malloc(sizeof(char)*255); 
    char *buffer = malloc(sizeof(char)*3);     
    char *str = NULL;
 
    while (1){    

        displayMenu(mode);  
        printf("Enter your choice: ");
        //scanning the user input
        scanf (" %c", &input);   
        
        switch (input)
        {  
            //In case the user input is 'o'
            case 'o':       
                printf ("Enter the file name: ");
                scanf (" %s", fileName); 

                //openning the file for reading 
                fd = open(fileName, O_RDONLY);  

                if (fd < 0){
                    fprintf(stderr, "Cannot open file %s\n", fileName);
                    displayMenu(mode);      
                    printf("Enter your choice: ");
                    scanf (" %c", &input);   
                }

                str = malloc(sizeof(char)*2);   
                strcpy (str, "");
                strcpy (buffer, "");

                //reading the file
                while (read(fd, buffer, MAX_FILESIZE) > 0){   
                    str = realloc (str, sizeof(char)*(strlen(str)+2)); 
                    strcat (str, buffer);
                    strcpy (buffer, "");
                }
                break;

            //In case the user input is 'd'
            case 'd':     
                printf ("Enter a mode 'a' for ASCII, 'h' for hex: ");
                scanf (" %c", &input);     

                if(input ==  'a'){
                    //the mode equals to 0 so it's on ASCII mode
                    mode = 0;        
                    strASCII(str); 

                    printf ("Mode is in ASCII\n");
                    printf ("Enter 'm' to return to the main menu or 'x' to exit: ");
                    //scanning the user input
                    scanf(" %c", &input);  

                    if (input == 'm'){
                        displayMenu(mode);     
                        printf("Enter your choice: ");
                        //scanning the user input
                        scanf (" %c", &input);   
                        close(fd);  
                    }
                    else if (input == 'x'){
                        free(fileName);  
                        free(buffer);    
                        free(str);   
                        //exit the program    
                        exit (0);    
                    }
                    else {
                        printf ("Invalid Input\n");
                        displayMenu(mode);   
                        printf("Enter your choice: ");
                        //scanning the user input
                        scanf (" %c", &input);   
                    }   
                }
                else if(input == 'h'){

                    //the mode equals to 1 so it's on hexa mode 
                    mode = 1;     
                    strparseHex(str); 

                    printf ("\nMode is in Hex\n");
                    printf ("Enter 'm' to return to the main menu or 'x' to exit: ");
                    //scanning the user input
                    scanf(" %c", &input);   

                    if (input == 'm'){
                        displayMenu(mode);  
                        printf("Enter your choice: ");
                        //scanning the user input
                        scanf (" %c", &input);
                        close(fd); 
                    }
                    else if (input == 'x'){
                        free(fileName);  
                        free(buffer);   
                        free(str);  
                        //exit the program
                        exit (0);  
                    }
                    else {
                        printf ("Invalid Input\n");
                        displayMenu(mode);  
                        printf("Enter your choice: ");
                        //scanning the user input
                        scanf (" %c", &input);    
                    }
                }
                else {
                    printf ("\nInvalid Input\n");
                    displayMenu(mode);    
                    printf("Enter your choice: ");
                    //scanning the user input
                    scanf ("%c", &input);     
                }
                break;

            //In case the user input is 'x'
            case 'x':    
                free(fileName); 
                free(buffer); 
                free(str); 
                //exit the program   
                exit (0);    
                break;
            
            default:
                printf ("Invalid Input\n");
                displayMenu(mode);    
                printf("Enter your choice: ");
                //scanning the user input
                scanf (" %c", &input);    
        }
    }
    close(fd);  
    free (fileName);
    free(buffer);
    free(str);
    return 0;
}

void displayMenu(int mode){    
    
    //if the mode equals zero
    if (mode == 0){     
        //print ASCII mode
        printf ("Mode is in ASCII\n");  
    }
    else if (mode!= 0){  
        //print hex mode 
        printf ("\nMode is in Hex\n");  
    }
    //print the main menu
    printf ("press 'o' to enter a file name\n");     
    printf ("press 'd' to select display mode\n");
    printf ("press 'x' to exit the program\n");
}

void strASCII(char *str){    

    if (str == NULL){                       //checking if str is NULL
        fprintf(stderr, "No open file\n");  //print a message to the user
        return;                              //return
    }
    for (int j = 0; j < strlen(str); j++){    //looping around the length of the string
        if (str[j] >= 0x0 && str[j] <= 0x9){    //checking if the characters are in this range
            printf (" ");                       //incase they are, replace with a space
        }
        else if (str[j] >= 0xB && str[j] <= 0x1F){   //checking if the characters are in this range
            printf (" ");                            //incase they are, replace with a space
        }
        else if (str[j] >= 0x7F){    //checking if the characters are bigger than 0x7F
            printf ("?");            //incase they are, replace with '?'
        }
        else{                            //else
            printf ("%c", str[j]);      //print the string
        }
    }
}

void strparseHex(char *str){

    if (str == NULL){        //checking if str is NULL
        fprintf(stderr, "No open file\n");   //print a message to the user
        return;   //return
    }
    int maxchar = 16;            //setting the max characters at a time to 16
    int k = maxchar + 1;    //setting k to the maxchar plus 1
    unsigned char index[k];  //declaring unsigned char
    int i;         
    for (i = 0; i < strlen(str); i++){     //looping around the length of the string
        if ((i % maxchar) == 0) {  //checking if i modullus maxchar equals 0

            if (i > 0){  //if i is bigger than 0 
                printf ("\n%s", index);     //print the character index in hex
            }
            printf ("%07x ", i);     //print leading zeros so it can be displayed as 7 characters
        }
        if (i > 0){    //if i is bigger than 0
            if (i % 8 == 0 && (i % maxchar) != 0){   //by the 8th char in the line
                printf (" ");  //print an extra space
            }  
        }
        printf("%02x ", str[i]);  //printing the string in hex
    }
    printf("\n%07x", i); //printing the index of the last char + 1 in the last line
}

