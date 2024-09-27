#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int isgreen(int size, int green[size+1], int pos){
    if(green[pos]) return 1;
    return 0;
}

int check(int size, char number[size+1], char attempt[size+1], int *g, int *y){
    if(strcmp(attempt,number)==0) return 1;
    *g=*y=0;
    int green[size+1], used[size+1];

    for(int i=0;i<size;i++){
        green[i]=used[i]=0;
    }
    green[size]=used[size]='\0';

    for(int i=0;i<size;i++){ //green 
        if(attempt[i]==number[i]){
            *g+=1;
            green[i]=used[i]=1;
        }
    }
    
    for(int i=0;i<size;i++){ //yellow
        if(!isgreen(size, green, i)){
            for(int j=0;j<size;j++){
                if(!used[j] && (attempt[i]==number[j])){
                    *y+=1;
                    used[j]=1;
                    break;
                }
            }
        }
    }
    return 0;
}

int main(void){
    system("chcp 65001");
    system("cls");
    //rules
    printf("----------------------\n");
    printf("   Guess The Number   \n");
    printf("----------------------\n");
    printf("\nR U L E S\n\n");
    printf("1. The game generates a secret number made up of digits (0-9) with a size defined by the player;\n\n");
    printf("2. After each attempt, the game will provide feedback:\n\n");
    printf("\t -Green: How many digits are correct and in the right position;\n\n");
    printf("\t -Yellow: How many digits are correct but in the wrong position;\n\n");
    printf("3. Exemple:\n\n");
    printf("\tSecret number: 0430\n\n");
    printf("\tPlayer's guess: 0734\n\n");
    printf("Feedback:\n\n");
    printf("\tGreen: 2 (The first digit '0' and the digit '3' are correct and in the right position);\n\n");
    printf("\tYellow: 1 (The digit '4' is correct but in the wrong position);\n\n");
    printf("4. Good luck!\n\n");
    printf("\n");
    printf("Press enter to start: "); getchar();
    system("cls");
    int size;
    printf("Enter the size of the secret number: ");
    scanf("%d", &size);
    char secretNumber[size+1];
    srand(time(NULL));
    for(int i=0;i<size;i++){
        secretNumber[i]=rand()%10+48;
    }
    secretNumber[size]='\0';
    printf("\n");
    int count=0, wrong=1, green, yellow;
    char attempt[size+1];
    do{
        count++;
        printf("%d° attempt: ", count);
        scanf("%s", attempt);
        printf("\n");
        if(strcmp(attempt,"=")==0) printf("Number: %s\n", secretNumber); //reveals secret number
        if(check(size, secretNumber, attempt, &green, &yellow)) wrong=0;
        else{
            printf("Green digits: %d\n", green);
            printf("Yellow digits: %d\n", yellow);
            printf("\n");
        }
    }while(wrong);
    system("cls");
    printf("Congratulations! \nYou won in %d attempts. \nThe secret number was %s.\n", count, secretNumber);
    sleep(15);

    return 0;
}