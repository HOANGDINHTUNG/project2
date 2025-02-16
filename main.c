#include <stdio.h>
#include <stdlib.h>
#include "function.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
	int choice;
	while(1){
//		galaxyEffect();
		system("color E0");
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
			default:
						
				break;
		}
	}
}	
//	int choice;
//	while (1) {
//		system("color 4E");
//		showMenuMain();
//		printf("\tEnter The Choice : ");
//		scanf("%d", &choice);
//		switch(choice){
//		    case 1: {
//		    	system("cls");
//		        choiceMenuBook();
//		        break;
//		    }
//		    case 2: {
//		    	system("cls");
//			    choiceMenuCustomer();
//				break;
//			}
//			case 0: {
//				printf("\tExit the program!!!\n");
//			    return 0;
//			}
//		    default:
//				printf("\tYour selection is not on the menu!!!!\n");
//				break;
//		}
//	}
//	return 0;
