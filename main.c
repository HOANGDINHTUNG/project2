#include <stdio.h>
#include "function.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	int choice;
	while(1){					
		system("color 40");
		showMenuAccount();
		printf("\t\t\t\t\t\tEnter The Choice : ");
		scanf("%d", &choice);
		switch(choice){
			case 1:{
				system("color 07");
				system("cls");
				registerAccount();
				break;
			}
			case 2:{
				system("color 07");
				system("cls");
				readAccountsFromTextFile();
				if(loginAccount()){
					system("cls");
					choiceMenuMain();						
				}			
				break;
			}
			case 3:{
				system("color 07");
				system("cls");
				GeneratePassword();
			}
			case 0:{
				galaxyEffect();
				return 0;
			}
			default:
				setColor(3);
				printf("\tYour selection is not on the menu!!!!\n");
				setColor(7);
				break;
		}
	}
}	
