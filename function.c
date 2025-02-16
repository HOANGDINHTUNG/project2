#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <windows.h>
#include"datatype.h"
#define MAX 1000
#include "C:\Users\HOANG DINH TUNG\Documents\Projects\Project5\function.h"
Book book1[MAX];
Member member1[MAX];
Account nick1;
const char *FILE_NAME = "C:\\Users\\HOANG DINH TUNG\\Documents\\Projects\\Project6\\listBook.bin";
const char *FILE_NAME1 = "C:\\Users\\HOANG DINH TUNG\\Documents\\Projects\\Project6\\listCustomer.bin";
const char *FILE_NAME2 = "C:\\Users\\HOANG DINH TUNG\\Documents\\Projects\\Project6\\abc.txt";
int numBooks=0;// So luong khach
int numMember=0;// So luong khach hang
int numAccount=0;// So luong tai khoan
// HAM BO TRO TINH CHAC CHE LOGIC CUA CHUONG TRINH
// Ham doi mau
void setColor(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Ham chuyen doi dinh dang thang dd/mm/yyyy
char *formatConversionDate(Date d){
    // Cap phap vung nho
    char *formattedDate = (char *)malloc(11 * sizeof(char));
    sprintf(formattedDate, "%02d/%02d/%04d",d.day, d.month, d.year);
    return formattedDate;
}

// Ham kiem tra ngay thang nam co hop le hay khong
int checkDateValid(int day,int month,int year){
    if(year>0){
        // Truong hop nam nhuan
        if(year%4==0&&year%100!=0||year%400==0){
            if(month==2){
                if(day<1||day>29){
                    return 0;
                }
            }
            else if(month==4||month==6||month==9||month==11){
                if(day<1||day>30){
                    return 0;
                }
            }
            else if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
                if(day<1||day>31){
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
        // Truong hop nam khong nhuan
        else{
            if(month==2){
                if(day<1||day>28){
                    return 0;
                }
            }
            else if(month==4||month==6||month==9||month==11){
                if(day<1||day>30){
                    return 0;
                }
            }
            else if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
                if(day<1||day>31){
                    return 0;
                }
            }
            else{
                return 0;
            }
        }
    }
    else{
        return 0;
    }
    return 1;
}

// Chuyen doi true/false thanh chu
char *convert(bool status){
    if(status==false){
        return "Lock";// Khoa
    }
    else if(status==true){
        return "Unlock";// Mo khoa
    }
    return "Undetermined";// Khong xac dinh
}

// Ham kiem tra so dien thoai co hop le hay khong
int checkPhoneNumber(char *phoneNumber){
    int length=(int)strlen(phoneNumber);
    // Kiem tra so dien thoai co dung 10 chu so hay khong
    if(length!=10){
        return 0;
    }
    // Kiem tra ki tu dau co phai la 0 hay khong
    if(*phoneNumber!='0'){
        return 0;
    }
    // Kiem tra sdt co chu cai hay khong
    for(int i=1;i<length;i++){
        if(*(phoneNumber+i)<48||*(phoneNumber+i)>57){
            return 0;
        }
    }
    return 1;
}

// Ham sap xep phan trang sach
void displayPageBook(Book books[], int size, int page){
    int start = page * 10;
    int end = start + 10;
	// Trang
    if (start >= size) {
        printf("\tInvalid page!!!\n");
        return;
    }
	// IN ra
    printf("\tPAGE %d:\n", page + 1);
    printf("$==========$==============================$==INFORMATION BOOK==$==========$==========$====================$\n");
	printf("|%-10s|%-30s|%-20s|%-10s|%-10s|%-20s|\n","ID","TITLE","AUTHOR","QUANLITY","PRICE(VND)","DATE PUBLICATION");
	printf("$==========$==============================$====================$==========$==========$====================$\n");
    for (int i = start; i < size && i < end; i++) {
        printf("|%-10s|%-30s|%-20s|%-10d|%-10d|%-20s|\n" ,
		                   books[i].bookId,
		                   books[i].title,
		                   books[i].author,
		                   books[i].quantity,
		                   books[i].price,
		                   formatConversionDate(books[i].publication));
		printf("$----------$------------------------------$--------------------$----------$----------$--------------------$\n");
    }
}

// Ham sap xep phan trang khach
void displayPageCustomer(Member members[], int size, int page){
    int start = page * 10;
    int end = start + 10;
	// Trang
    if (start >= size) {
        printf("\tInvalid page!!!\n");
        return;
    }
	// IN ra
    printf("\tPAGE %d:\n", page + 1);
    printf("$==========$================INFORMATION CUSTOMER=====$==========$===============$\n");
	printf("|%-10s|%-25s|%-15s|%-10s|%-15s|\n","ID","NAME","PHONE","STATUS","BORROWEDBOOKS");
	printf("$==========$=========================$===============$==========$===============$\n");
    for (int i = start; i < size && i < end; i++) {
        printf("|%-10s|%-25s|%-15s|%-10s|%-15d|\n" ,
		        members[i].memberId,
		        members[i].name,
		        members[i].phone,
		        convert(members[i].status),
		        members[i].bookCount);
		printf("$----------$-------------------------$---------------$----------$---------------$\n");
    }
}

//Clear het man hinh
int pressAnyKey(){
	char c;
	fflush(stdin);
	printf("\tPress any key to return to the program!!!\n");
	scanf("%c",&c);
}

// Ham kiem tra dinh danh email
int isValidEmail(const char *email){
    int atCount=0, dotCount=0;
    // Kiem tra chieu dai hop le
    int len = (int)strlen(email);
    if (len < 5 || len > 100) 
		return 0; 
    // Kiem tra tung ki tu trong email
    for (int i = 0; email[i] != '\0'; i++) {
        char ch = email[i];// lay tung ki tu
        if (ch == '@') {
            atCount++;
        } 
		else if (ch == '.') {
            dotCount++;
        } 
		else if (!isalnum(ch)&&ch!='_'&&ch!='-'&&ch!='.') {
            return 0; 
        }
    }
    // Kiem tra co dung 1 '@ va it nhat 1 dau '.'
    if (atCount!=1||dotCount<1) 
		return 0;
    char *check="@gmail.com";
    // Kiem tra co doi @gmail.com khong
    if(strstr(email,check)==NULL){
		return 0;
	}
    return 1; // Email hop le
}

// Mau galaxy
void galaxyEffect(){
	// Xanh duong, tim, hong, xanh bien, trang
    int colors[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14}; 
    int size = sizeof(colors) / sizeof(colors[0]);
	// Chen mau vong lap
	int i=0;
    while(1){
        setColor(colors[i++ % size]); 
        Sleep(200); // Dung 200ms de tao hieu ung
        system("cls"); // Xoa man hinh de tao hieu ung nhay
    }
	// Reset ve mau mac dinh
    setColor(7); 
}

// HAM PHU BO SUNG CHO HAM CHINH
// Ham kiem tra xem ma sach co trung hay khong
bool checkIdExistBook(Book *bookList, int totalBooks, char *bookId){
    for(int i=0;i<totalBooks;i++){
        if(strcmp(bookList[i].bookId,bookId) == 0){
            return true;
            // Ma sach ton tai
        }
    }
    return false;
    // Ma sach khong ton tai
}

// Ham kiem tra ten sach co trung hay khong
int checkTitleExistBook(const char *Title,int number,Book *book1){
    for(int i=0;i<number;i++){
        if(strcmp(Title,book1[i].title)==0){
            return 1;
            // Ten sach ton tai
        }
    }
    return 0;
    // Ten sach khong ton tai
}

// Kiem tra sach theo ma
int findIdByBook(const char *findIdBook){
    for(int i=0;i<numBooks;i++){
        if(strcmp(book1[i].bookId,findIdBook)==0){
            return i;
        }
    }
    return -1;
}

// Hien thi bang thong tin sach
void showTableListBook(){
    printf("$==========$===================INFORMATION BOOK================$========$==========$====================$\n");
    printf("|%-10s|%-30s|%-20s|%-8s|%-10s|%-20s|\n", "ID", "TITLE", "AUTHOR", "QUANLITY", "PRICE", "DATE PUBLICATION");
    printf("$==========$==============================$====================$========$==========$====================$\n");
    for (int i = 0; i < numBooks; i++) {
        printf("|%-10s|%-30s|%-20s|%-8d|%-10d|%-20s|\n",
               book1[i].bookId,
               book1[i].title,
               book1[i].author,
               book1[i].quantity,
               book1[i].price,
               formatConversionDate(book1[i].publication));
        printf("$----------$------------------------------$--------------------$--------$----------$--------------------$\n");
    }
}

// Ham kiem tra xem ma so khach co ton tai hay chua
int checkIdExistCustomer(Member *memberList, int totalMember, char *memberId){
    for(int i=0;i<totalMember;i++){
        if(strcmp(memberId,memberList[i].memberId)==0){
            return 1;
            // Ma so khach hang ton tai
        }
    }
    return 0;
    // Ma so khach khong ton tai
}

// Ham kiem tra xem so dien thoai co ton tai hay chua
int checkPhoneNumberExistCustomer(Member *memberList, int totalMember, char *memberId){
    for(int i=0;i<totalMember;i++){
        if(strcmp(memberId,memberList[i].phone)==0){
            return 1;
            // Sdt cua khach da co
        }
    }
    return 0;
    // Sdt cua khach chua co
}

// Kiem tra khach hang theo ma
int findIdByCustomer(const char *findIdCustomer){
    for(int i=0;i<numMember;i++){
        if(strcmp(member1[i].memberId,findIdCustomer)==0){
            return i;
        }
    }
    return -1;
}

// Ham dinh huong chuong trinh sach
void programOrientationBook(){
	int page;
	// Tinh so trang
	int totalPage=(numBooks+10-1)/10;
	while(1){
		printf("\tInput page 1 form %d (input 0 to return) : ",totalPage);
		scanf("%d",&page);
		pressAnyKey();
		system("cls");
		if (page == 0) break;
			if (page < 1 || page > totalPage) {
		        printf("\tInvalid Page! Input to 1 form %d.\n", totalPage);
		} 
		else {
		    displayPageBook(book1, numBooks, page - 1);
		}
	}
}

// Ham dinh huong chuong trinh khach
void programOrientationCustomer(){
	int page;
	// Tinh so trang
	int totalPage=(numMember+10-1)/10;
	while(1){
		printf("\tInput page to 1 form %d (input 0 to return) : ",totalPage);
		scanf("%d",&page);
		pressAnyKey();
		system("cls");
		if (page == 0){
			break;
		}
		if (page < 1 || page > totalPage) {
		    printf("\tInvalid Page! Input to 1 form %d.\n", totalPage);
		}
		else {
		    displayPageCustomer(member1, numMember, page - 1);
		}
	}
}

// DANH SACH THU VIEN
// Hien thi menu chinh
void showMenuMain(){
    printf("\t\tMENU MAIN\n");
    printf("\t|===============================|\n");
    printf("%-33s|\n","\t| [1] Management Book");
    printf("%-33s|\n","\t| [2] Management Customer");
    printf("%-33s|\n","\t| [0] Exit the Program");
    printf("\t|===============================|\n");
}

// Hien thi menu sach
void showMenuBook(){
    printf("\t\tMENU BOOK\n");
    printf("\t|==============================|\n");
    printf("%-32s|\n","\t| [1] Show All Books");
    printf("%-32s|\n","\t| [2] Add New the Books");
    printf("%-32s|\n","\t| [3] Edit the Books");
    printf("%-32s|\n","\t| [4] Delete the Books");
    printf("%-32s|\n","\t| [5] Find the Books by name");
    printf("%-32s|\n","\t| [6] Sort the Books by price");
    printf("%-32s|\n","\t| [0] Exit the Program");
    printf("\t|==============================|\n");
}

// Luu danh sach vao file nhi phan
void saveBookToBinaryFile(Book *book2){
    // Tao va mo file viet
    FILE *f=fopen(FILE_NAME, "ab");
    if(f==NULL){
        printf("\tCannot open file %s write!!!\n",FILE_NAME);
        return;
    }
    // Ghi so luong vao file
    fwrite(book2,sizeof(Book),1,f);
    printf("\tSave file success!!!!\n");
    // Dong file
    fclose(f);
}

// Doc thong tin cua sach tu file
void readBookFromBinaryFile(int mode){
    FILE *f=fopen(FILE_NAME,"rb");
    if(f==NULL){
        printf("\tFile %s no exist or no datas!!!\n",FILE_NAME);
        return;
    }
    numBooks=0;
    Book book2;
    if(mode==1){
        printf("$==========$===================INFORMATION BOOK================$==========$==========$====================$\n");
        printf("|%-10s|%-30s|%-20s|%-10s|%-10s|%-20s|\n","ID","TITLE","AUTHOR","QUANLITY","PRICE(VND)","DATE PUBLICATION");
        printf("$==========$==============================$====================$==========$==========$====================$\n");
    }
    while(fread(&book2,sizeof(Book),1,f)){
        book1[numBooks++] = book2; // Luu sach vao mang va tang so luong sach
        if(mode==1){
            printf("|%-10s|%-30s|%-20s|%-10d|%-10d|%-20s|\n" ,
                   book2.bookId,
                   book2.title,
                   book2.author,
                   book2.quantity,
                   book2.price,
                   formatConversionDate(book2.publication));
            printf("$----------$------------------------------$--------------------$----------$----------$--------------------$\n");
        }
    }
    //Dong file
    fclose(f);
}

// Nhap vao thong cua sach
void inputInfoBook(Book *book1,const int *i,int index,int mode){
    if(mode==0){
        printf("\tPlease enter the number of Books want to add : ");
        scanf("%d",i);
        getchar();
    }
    // Nhap tung thong tin cua sach
    for(int j=0;j<*i;j++){
        if(mode==1){
            j=index;
        }
        // NHAP ID SACH
        if(mode==0){
            while(1){
                fflush(stdin);
                char input[50];
                printf("\tPlease enter the book ID (Vd: B001) : ");
                fgets(input,sizeof(input),stdin);
                // Xoa ki tu xuong dong
                input[strcspn(input,"\n")]='\0';
                // Kiem tra ki tu dau co phai ki tu 'B' hay khong
                if(input[0]!='B'){
					printf("\tThe first character must be 'B'!!!\n");
					continue;
				}
				// Kiem tra cac ki tu sau co phai chu so hay khong
				for(int i=1;i<strlen(input);i++){
				    if(*(input+i)<48||*(input+i)>57){
				        continue;
				    }
				}
                // Kiem tra do dai va ki rong
                if (strlen(input) == 0 || strlen(input) > 10) {
                    printf("\tError: Book ID must be between 1 and 10 characters!!!\n");
                    continue;
                }
                // Kiem tra Id co ton tai hay chua
                if(checkIdExistBook(book1,numBooks,input)){
                    printf("\tError: Book ID already exists, Please enter a different one!!!\n");
                    continue;
                }
                // Hop le luu vao danh sach
                strcpy(book1[j].bookId, input);
                printf("\tBook ID has been added successfully!\n");
                break;
            }
        }
        // NHAP TIEU DE CHO SACH
        while (1){
            fflush(stdin);
            char input[50];
            printf("\tPlease enter the book Title : ");
            fgets(input,sizeof(input),stdin);
            input[strcspn(input,"\n")]='\0';
            // Kiem tra ten sach co ton tai hay chua
            if(checkTitleExistBook(input,numBooks,book1)){
                printf("\tError: Book Title already exists, Please enter a different one!!!\n");
                continue;
            }
            strcpy(book1[j].title, input);
            printf("\tBook Title has been added successfully!\n");
            break;
        }
        // NHAP TEN TAC GIA
        while (1){
            fflush(stdin);
            char input[50];
            printf("\tPlease enter the author's name : ");
            fgets(input,sizeof(input),stdin);
            input[strcspn(input,"\n")]='\0';
            // Kiem tra ki tu rong
            if (strlen(input) == 0) {
                printf("\tError: Book ID must be between 1 and 10 characters!!!\n");
                continue;
            }
            strcpy(book1[j].author, input);
            printf("\tBook Author has been added successfully!\n");
            break;
        }
        // MOI NHAP SO LUONG SACH CUNG LOAI
        while (1){
            fflush(stdin);
            printf("\tPlease enter the quantity of this book : ");
            scanf("%d",&book1[j].quantity);
            // Kiem tra so luong
            if (book1[j].quantity<=0) {
                printf("\tError: The number of books must be greater than Zero!!!\n");
                continue;
            }
            printf("\tBook Quanlity has been added successfully!\n");
            break;
        }
        // NHAP GIA BAN CHO SACH
        while(1){
            fflush(stdin);
            printf("\tPlease enter the price : ");
            scanf("%d",&book1[j].price);
            // Kiem tra gia
            if (book1[j].price<1000) {
                printf("\tError: The price of a book must be greater than 1000!!!\n");
                continue;
            }
            printf("\tBook Price has been added successfully!\n");
            break;
        }
        // NHAP NGAY XUAT BAN
        do{
            fflush(stdin);
            printf("\tPlease enter the day : ");
            scanf("%d",&book1[j].publication.day);
            printf("\tPlease enter the month : ");
            scanf("%d",&book1[j].publication.month);
            printf("\tPlease enter the year : ");
            scanf("%d",&book1[j].publication.year);
            if(!checkDateValid(book1[j].publication.day,
                               book1[j].publication.month,
                               book1[j].publication.year)){
                // Nhap khong thanh cong
                printf("\tInvalid, please again enter!!!\n");
            }
            else{
                printf("\tEnter successfully!!!\n");
                break;
            }
        }while(1);
        if(mode==0){
            saveBookToBinaryFile(&book1[j]);// Luu thong tin vao file nhi phan
        }
    }
}

// Chinh sua thong tin lop hoc
void editInforBook(){
    readBookFromBinaryFile(1);
    int n=1;
    fflush(stdin);
    char ma[10];
    printf("\tPlease enter Book Id want to edit : ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = '\0';
    // Lay chi so Id trong mang danh sach lop
    int index = findIdByBook(ma);
    if (index == -1) {
        printf("\tNo find Book ID!!!!\n");
        return;
    }
    // Hien thi thong tin cu truoc khi sua
    printf("\tShow old Information Book: \n");
    printf("\tID : %s\n", book1[index].bookId);
    printf("\tTitle : %s\n", book1[index].title);
    printf("\tAuthor : %s\n", book1[index].author);
    printf("\tQuanlity : %d\n", book1[index].quantity);
    printf("\tPrice : %d\n",book1[index].price);
    printf("\tDate Publication : %s\n", formatConversionDate(book1[index].publication));
    // Cap nhat lai thong tin
    inputInfoBook(book1, &n, index, 1);
    // Ghi lai thong tin vao file
    FILE *f=fopen(FILE_NAME, "wb");
    if(f==NULL){
        printf("\nFile %s no exsit or no datas!!!\n",FILE_NAME);
        return;
    }
    // Dong file
    fwrite(book1, sizeof(Book), numBooks, f);
    fclose(f);
    printf("\tUpdated information Book successfully!!!\n");
}

// Xoa sach
void deleteBook(){
    // Doc va luu file vao book1
    readBookFromBinaryFile(1);
    // Nhap id
    char ma[10];
    fflush(stdin);
    printf("\tPlease enter Book Id to Delete : ");
    fgets(ma,sizeof(ma),stdin);
    ma[strcspn(ma,"\n")]='\0';
    // Tim sach bang ma
    int index = findIdByBook(ma);
    if(index==-1){
        printf("\tNo find Book ID!!!!\n");
        return;
    }
    else{
        int choice;
        printf("\tAre you sure you want to delete?\n");
        printf("\t1.YES\n");
        printf("\t0.NO\n");
        printf("\tEnter The Choice : ");
        scanf("%d",&choice);
        if(choice){
            for(int i=index;i<numBooks-1;i++){
                *(book1 + i) = *(book1 + i + 1);
            }
            --(numBooks);
            // Ghi thong tin vao file
            FILE *f=fopen(FILE_NAME, "wb");
            if(f==NULL){
                printf("\nFile %s no exsit or no datas!!!\n",FILE_NAME);
                return;
            }
            // Dong file
            fwrite(book1, sizeof(Book), numBooks, f);
            fclose(f);
            printf("\tDelete Book successfully!!!\n");
            return;
        }
        else{
            return;
        }
    }
}

// Tim kiem sach theo ten
void searchTitleBook(){
    int numResults=0;
    char keyWords[30];
    fflush(stdin);
    Book results[numBooks]; // Cau truc luu thong tin
    printf("\tPlease enter keywords to find books : ");
    fgets(keyWords, sizeof(keyWords), stdin);
    keyWords[strcspn(keyWords, "\n")] = 0;
    for(int i=0;i<numBooks;i++){
        if (strstr(book1[i].title, keyWords) != NULL) {
            results[numResults++] = book1[i];
        }
    }
    if(numResults>0){
        printf("\tSearch results:\n");
        printf("#***********#*******************************#*********************#*********#***********#*********************#\n");
        printf("$%-11s$%-31s$%-21s$%-9s$%-11s$%-21s$\n","ID","TITLE","AUTHOR","QUANLITY","PRICE(VND)","DATE PUBLICATION");
        printf("#***********#*******************************#*********************#*********#***********#*********************#\n");
        for(int i=0;i<numResults;i++){
            printf("$ %-10s$ %-30s$ %-20s$ %-8d$ %-10d$ %-20s$\n" ,
                   results[i].bookId,
                   results[i].title,
                   results[i].author,
                   results[i].quantity,
                   results[i].price,
                   formatConversionDate(results[i].publication));
        	printf("#***********#*******************************#*********************#*********#***********#*********************#\n");
        }
    }
    else{
        printf("\tNo books found!!!\n");
    }
}

// Sap xep sach theo gia tien
void sortBooksByPrice(){
    int choice;
    printf("\t1.Sort Increase\n");
    printf("\t2.Sort Decrease\n");
    while(1){
        printf("\tEnter The Choice : ");
        scanf("%d",&choice);
        if(choice==1){
            //insertion sort
            for(int i=1;i<numBooks;i++){
                Book key=book1[i];
                int j=i-1;
                while(j>=0&&key.price<book1[j].price){
                    book1[j+1]=book1[j];
                    j--;
                }
                book1[j+1]=key;
            }
            programOrientationBook();
            break;
        }
        else if(choice==2){
            //selection sort
            for(int i=0;i<numBooks;i++){
                Book max=book1[i];
                for(int j=i+1;j<numBooks;j++){
                    if(book1[j].price>max.price){
                        max=book1[j];
                        book1[j]=book1[i];
                        book1[i]=max;
                    }
                }
            }
            programOrientationBook();
            break;
        }
        else{
            printf("\tYour selection is not!!!!\n");
        }
    }
}

// Lua chon tinh nang trong menu quan ly sach
void choiceMenuBook(){
    while (1) {
    	system("color 6");
        readCustomerFromBinaryFile(0);
        readBookFromBinaryFile(0);
        showMenuBook();
        int choice,newCount;
        printf("\tEnter The Choice : ");
        scanf("%d", &choice);
        switch (choice) {
            // Hien thi tat ca thong tin cua sach
            case 1: {
                if(numBooks==0){
                    printf("\tNo books added yet!!!\n");
                    break;
                }
                programOrientationBook();
                break;
            }
                // Them sach vao thu vien
            case 2: {
                if(numBooks==100) {
                    printf("\tThe total number of books is full, cannot be added!!!\n");
                    break;
                }
                inputInfoBook(book1,&newCount,1,0);
                printf("\tAdd success!!!!\n");
                break;
            }
                // Chinh sua thong tin cua sach
            case 3: {
                if(numBooks==0){
                    printf("\tThere are no books to edit!!!\n");
                    break;
                }
                editInforBook();
                break;
            }
                // Xoa 1 quyen sach
            case 4:{
                if(numBooks==0){
                    printf("\tThere are no books to delete!!!\n");
                    break;
                }
                deleteBook();
                break;
            }
                // Tim sach bang ten sach
            case 5:{
                if(numBooks==0){
                    printf("\tThere are no books to search!!!\n");
                    break;
                }
                searchTitleBook();
                break;
            }
            	// Sap xep sach them gia tien sach
            case 6:{
                if(numBooks==0){
                    printf("\tThere are no books to sort!!!\n");
                    break;
                }
                sortBooksByPrice();
                break;
            }
            case 0: {
            	system("cls");
            	printf("\tReturn menu!!!\n");
                return;
            }
            default:
                printf("\tYour selection is not on the menu!!!!\n");
                break;
        }
        pressAnyKey();
		system("cls");
    }
}

//DANH SACH KHACH HANG
//Hien thi menu khach hang
void showMenuCustomer(){
    printf("\t\tMENU CUSTOMER\n");
    printf("\t|============================|\n");
    printf("%-30s|\n","\t| [1] Show All Customers");
    printf("%-30s|\n","\t| [2] Add New Customers");
    printf("%-30s|\n","\t| [3] Edit Customers");
    printf("%-30s|\n","\t| [4] Account lock (unlock)");
    printf("%-30s|\n","\t| [5] Find client by name");
    printf("%-30s|\n","\t| [6] Lend Books");
    printf("%-30s|\n","\t| [7] Return Books");
    printf("%-30s|\n","\t| [0] Exit the Program");
    printf("\t|============================|\n");
}

// Luu thong tin khach vao file nhi phan
void saveCustomerToBinaryFile(Member *member2){
    // Tao mo file viet
    FILE *f=fopen(FILE_NAME1, "ab");
    if(f==NULL){
        printf("\tCannot open file %s write!!!\n",FILE_NAME1);
        return;
    }
    // Ghi so lan luot khach vao file
    fwrite(member2,sizeof(Member),1,f);
    printf("\tSave file success!!!!\n");
    // Dong file
    fclose(f);
}

// Doc thong tin cua khach tu file
void readCustomerFromBinaryFile(int mode){
    FILE *f=fopen(FILE_NAME1,"rb");
    if(f==NULL){
        printf("\tFile %s no exist or no datas!!!\n",FILE_NAME1);
        return;
    }
    numMember=0;
    Member member2;
    if(mode==1){
        printf("$==========$=========================$===INFORMATION BOOK=======$===============$\n");
        printf("|%-10s|%-25s|%-15s|%-10s|%-15s|\n","ID","NAME","PHONE","STATUS","BORROWEDBOOKS");
        printf("$==========$=========================$===============$==========$===============$\n");
    }
    while(fread(&member2,sizeof(Member),1,f)){
        member1[numMember++] = member2; // Luu khach vao file vao tang so luong
        if(mode==1){
            printf("|%-10s|%-25s|%-15s|%-10s|%-15d|\n",
                   member2.memberId,
                   member2.name,
                   member2.phone,
                   convert(member2.status),
                   member2.bookCount);
            printf("$----------$-------------------------$---------------$----------$---------------$\n");
        }
    }
    // Dong file
    fclose(f);
}

// Them va nhap thong tin cho khach 
void inputInfoCustomer(Member *member1,const int *i,int index,int mode){
    if(mode==0){
        printf("\tPlease enter the number of Customers want to add : ");
        scanf("%d",i);
        getchar();
    }
    // Nhap tuong thong tin cua khach
    for(int j=0;j<*i;j++){
        if(mode==1){
            j=index;
        }
        if(mode==0){
            // Nhap Id cho khach
            while(1){
                fflush(stdin);
                char input[50];
                printf("\tPlease enter the Costumer ID (Vd: KH001) : ");
                fgets(input,sizeof(input),stdin);
                // Xoa ki tu xuong dong
                input[strcspn(input,"\n")]='\0';
                // Kiem tra ki tu dau co phai ki tu 'K' va 'H' hay khong
				if(input[0]!='K'||input[1]!='H'){
					printf("\tThe first character must be 'K' and 'H'!!!\n");
					continue;
				}
				// Kiem tra cac ki tu sau co phai chu so hay khong
				for(int i=2;i<strlen(input);i++){
				if(*(input+i)<48||*(input+i)>57){
					continue;
					}
				}
                // Kiem tra do dai va ki tu rong
                if (strlen(input) == 0 || (int)strlen(input) > 10) {
                    printf("\tError: Customers ID must be between 1 and 10 characters!!!\n");
                    continue;
                }
                if(checkIdExistCustomer(member1,numMember,input)){
                    printf("\tError: Customers ID already exists, Please enter a different one!!!\n");
                    continue;
                }
                // Hop le va luu vao danh sach
                strcpy(member1[j].memberId, input);
                printf("\tCustomers ID %s has been added successfully!\n", member1[j].memberId);
                break;
            }
        }
        // Nhap ten
        fflush(stdin);
        printf("\tPlease enter the Customer's name : ");
        fgets(member1[j].name,sizeof(member1[j].name),stdin);
        member1[j].name[strcspn(member1[j].name,"\n")]='\0';
        // Nhap so dien thoai cho khach hang
        while(1){
			fflush(stdin);
			char input[15];
			printf("\tPlease enter the phone Number : ");
			fgets(input,sizeof(input),stdin);
			input[strcspn(input,"\n")]='\0';
			// Kiem tra so dien thoai co hop ly hay khong
			if(!checkPhoneNumber(input)){
				printf("\tInvalid phone number!!!\n");
				continue;
			}
			// Kiem tra su sdt co trung hay khong
			if(checkPhoneNumberExistCustomer(member1,numMember,input)){
				printf("\tThis phone number is valid!!!\n");
				continue;
			}
			printf("\tEnter successful phone number!!!\n");
			strcpy(member1[j].phone,input);
			break;
		}
        // Nhap trang thai khach hang
        if(mode==0){
            while(1){
                fflush(stdin);
                char input[50];
                printf("\tPlease enter the status Customer (true : Unlock/false : Lock) : ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input,"\n")]='\0';
                if (strcmp(input, "true") == 0) {
                    member1[j].status = true;
                    break;
                } else if (strcmp(input, "false") == 0) {
                    member1[j].status = false;
                    break;
                } else {
                    printf("\tError, can enter 'true' or 'false'!!!\n");
                }
            }
        }
        // So luong sach ( ban dau mac dinh la 0 )
        if(member1[j].status==false){
            printf("\tThe customer is status of not borrowing books!!!\n");
        }
        else{
            member1[j].bookCount=0;
        }
        // Luu thong tin 
        if(mode==0){
            saveCustomerToBinaryFile(&member1[j]);
        }
    }
}

// Chinh sua thong tin khach hang
void  editInforCustomer(){
    readCustomerFromBinaryFile(1);
    int n=1;
    fflush(stdin);
    char ma[10];
    printf("\tPlease enter Customer Id want to edit : ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = '\0';
    // Lay chi so ID trong mang danh sach khach hang
    int index = findIdByCustomer(ma);
    if (index == -1) {
        printf("\tNo find Customer ID!!!!\n");
        return;
    }
    // Hien thi thong tin cu truoc khi sua
    printf("\tShow old Information Customer: \n");
    printf("\tID : %s\n", member1[index].memberId);
    printf("\tName : %s\n", member1[index].name);
    printf("\tPhoneNumber : %s\n", member1[index].phone);
    printf("\tStatus : %s\n", convert(member1[index].status));
    printf("\tBorrowedBooks : %d\n",member1[index].bookCount);
    // Cap nhat thong tin
    inputInfoCustomer(member1, &n, index, 1);
    // Ghi lai thong tin file
    FILE *f=fopen(FILE_NAME1, "wb");
    if(f==NULL){
        printf("\nFile %s no exist or no datas!!!\n",FILE_NAME1);
        return;
    }
    // Dong file
    fwrite(member1, sizeof(Member), numMember, f);
    fclose(f);
    printf("\tUpdated information Customer successfully!!!\n");
}

// Khoa (Mo) thong tin khach hang
void toggleMemberStatus(){
    char Id[10];
    fflush(stdin);
    printf("\tInput Customer Id need Lock/Unlock : ");
    fgets(Id, sizeof(Id), stdin);
    Id[strcspn(Id, "\n")] = '\0';
    // Lay chi so Id trong danh sach khach hang
    int index = findIdByCustomer(Id);
    if (index == -1) {
        printf("\tNo find Customer ID!!!!\n");
        return;
    }
    // Neu khach hang ton tai kiem tra trang thai hien tai
    if (member1[index].status) {
        printf("Client %s is open. Do you want to block this customer? (yes/no): ", member1[index].name);
    } else {
        printf("Client %s is close. Do you want to unblock this customer? (yes/no): ", member1[index].name);
    }
    // Nhap lua chon
    char choice[5];
    fflush(stdin);
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';
    if (strcpy(choice,"yes")==0 || strcpy(choice,"Yes")==0) {
        //Dao trang thai(khoa-mo/mo-khoa)
        member1[index].status = !member1[index].status;
        printf("\tClient %s has been %s successfully!!!\n",member1[index].name,member1[index].status ? "unlocked" : "locked");
    }
    else {
        printf("\tCanceled\n");
    }
}

// Tim kiem khach hang theo ten
void searchNameCustomer(){
    int numResults=0;
    char name[30];
    fflush(stdin);
    Member results[numMember]; // Cau truc luu thong tin khach
    printf("\tPlease enter keywords name to find Client : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    for(int i=0;i<numMember;i++){
        if (strstr(member1[i].name, name) != NULL) {
            results[numResults++] = member1[i];
        }
    }
    if(numResults>0){
        printf("\tSearch results:\n");
        printf("#***********#**************************#****************#***********#****************#\n");
        printf("$%-10s$%-25s$%-15s$%-10s$%-15s$\n","ID","NAME","PHONE","STATUS","BORROWED BOOKS");
        printf("#***********#**************************#****************#***********#****************#\n");
        for(int i=0;i<numResults;i++){
            printf("$ %-10s$ %-25s$ %-15s$ %-10s$ %-15d$\n" ,
                   results[i].memberId,
                   results[i].name,
                   results[i].phone,
                   convert(results[i].status),
                   results[i].bookCount);
            printf("#***********#**************************#****************#***********#****************#\n");
        }
    }
    else{
        printf("\tNo customers found!!!\n");
    }
}

// Cho muon sach ( toi da 5 quyen )
void addBookByCustomer(){
    // Nhap Id khach hang
    char customerId[10];
    fflush(stdin);
    printf("\tPlease enter Id to find Client : ");
    fgets(customerId, sizeof(customerId), stdin);
    customerId[strcspn(customerId,"\n")]='\0';
    int n, index= findIdByCustomer(customerId);
    // Id khach hang khong ton tai
    if(index == -1) {
        printf("\tNo find Customer ID!!!!\n");
        return;
    }
    // Khach hang dang bi khoa
    if(!member1[index].status){
        printf("\tCustomer is locked!!!\n");
        return;
    }
    // Kiem tra khach hang da muon du 5 quyen sach
    if (member1[index].bookCount >= 5) {
        printf("\tCustomer has already borrowed the maximum number of books (5)!\n");
        return;
    }
    // Hien thi sach da co trong thu vien
    printf("\tBooks are available in the library :\n");
    printf("\t| %-10s| %-30s| %-10s|\n","ID","TITLE","QUANLITY");
    for(int i=0;i<numBooks;i++){
        printf("\t| %-10s| %-30s|    %-7d|\n",book1[i].bookId,book1[i].title,book1[i].quantity);
    }
    // Nhap so luong sach muon muon va so sach c
    do{
        printf("\tEnter number of books to borrow (max 5, remain %d): ",(5-member1[index].bookCount));
        scanf("%d",&n);
    }while(n<=0||n>(5- member1[index].bookCount));
    getchar();
    // Nhap id sach cho khach
	for (int i = 0; i < n; i++) {
	    char bookId[10];
	    while (1) {
	        printf("\tInput Book Id %d: ", i + 1);
	        fgets(bookId, sizeof(bookId), stdin);
	        bookId[strcspn(bookId, "\n")] = '\0'; // Xoa dau xuong dong
	        // Kiem tra Id sach co hop le hay khong
	        if(checkIdExistBook(book1, numBooks, bookId)) {
	        	// Sao chep dia chi sach cho Member
	            strcpy(member1[index].BorrowedBooks[member1[index].bookCount].bookId, bookId);
	            // Cong so luong sach cho khach
				member1[index].bookCount++;
				// Lay vi tri cua sach
				int index1=findIdByBook(bookId);
				// Tru so luong sach
				book1[index1].quantity--;
	        	break; // Thoat khoi vong lap
	        }
	        // Kiem tra so luong sach da het hay chua
			if(book1[index].quantity <= 0) {
			    printf("\tThis book is out of the library, choose another one!!!\n");
			    continue;
			}
			else {
	            printf("\tBook id does not exist, please enter again\n");
	        }
	    }
	}
	// Mo file
	FILE *f = fopen(FILE_NAME1, "wb");
	// Kiem tra loi
	if (f == NULL) {
	    printf("\tError opening file%s!\n", FILE_NAME1);
	    return;
	}
	// Viet vao file
	fwrite(member1, sizeof(Member), numMember, f);
	// Dong file
	fclose(f);
	printf("\tUpdated information Customer successfully!!!\n");
	FILE *f1 = fopen(FILE_NAME, "wb");
	// Kiem tra loi
	if (f1 == NULL) {
		printf("\tError opening file%s!\n", FILE_NAME);
		return;
	}
	// Viet vao file
	fwrite(book1, sizeof(Book), numBooks, f1);
	// Dong file
	fclose(f1);
}

// Tra lai sach da muon
void returnBookByLibrary(){
    // Nhap id khach hang
    char customerId[10];
    fflush(stdin);
    printf("\tPlease enter Id to find Client : ");
    fgets(customerId, sizeof(customerId), stdin);
    customerId[strcspn(customerId,"\n")]='\0';
    int index= findIdByCustomer(customerId);
    // Id khach hang khong ton tai
    if(index == -1) {
        printf("\tNo find Customer ID!!!!\n");
        return;
    }
    // Khach hang khong co sach
    if(!member1[index].bookCount){
        printf("\tCustomer has no book to return!!!\n");
        return;
    }

    // Hien thi nhung sach khach da muon
    printf("\tDisplays borrowed books\n");
    for(int i=0;i<member1[index].bookCount;i++){
    	int index1=findIdByBook(member1[index].BorrowedBooks[i].bookId);
        printf("\t| %-10s| %-30s|\n",book1[index1].bookId,book1[index1].title);
    }
    // Nhap Id sach muon xoa
    char Id[10];
    fflush(stdin);
    printf("\tInput Book Id need return : ");
    fgets(Id, sizeof(Id), stdin);
    Id[strcspn(Id, "\n")] = '\0';
    // Tra lai sach (xoa sach)
    for(int i=0;i<member1[index].bookCount;i++){
        if(strcmp(Id,member1[index].BorrowedBooks[i].bookId)==0){
            for(int j=i;j<member1[index].bookCount-1;j++){
                *(member1[index].BorrowedBooks[i].bookId + j) = *(member1[index].BorrowedBooks[i].bookId + j + 1);
            }
            --(member1[index].bookCount);
        }
    }
    // Cong lai sach cho thu vien
    int index2=findIdByBook(Id);
    book1[index2].quantity++;
    // Ghi thong tin vao file
	FILE *f=fopen(FILE_NAME1, "wb");
	if(f==NULL){
		printf("\nFile %s no exsit or no datas!!!\n",FILE_NAME1);
		return;
	}
	// Dong file
	fwrite(member1, sizeof(Member), numMember, f);
	fclose(f);
    FILE *f1 = fopen(FILE_NAME, "wb");
	// Kiem tra loi
	if (f1 == NULL) {
		printf("\tError opening file%s!\n", FILE_NAME);
		return;
	}
	// Viet vao file
	fwrite(book1, sizeof(Book), numBooks, f1);
	// Dong file
	fclose(f1);
	printf("\tDelete Book successfully!!!\n");
}

// Lua chon tinh nang trong menu quan ly khach hang
void choiceMenuCustomer(){
    while (1) {
    	system("color 6");
        readBookFromBinaryFile(0);
        readCustomerFromBinaryFile(0);
        showMenuCustomer();
        int choice,newCount;
        printf("\tEnter The Choice : ");
        scanf("%d", &choice);
        switch (choice) {
            // Hien thi tat ca thong tin cua khach
            case 1: {
                if(numMember==0){
                    printf("\tNo Customer added yet!!!\n");
                    break;
                }
                programOrientationCustomer();
                break;
            }
                // Them thong tin khach vao file
            case 2: {
                if(numMember==100){
                    printf("\tThe total number of Customer is full, cannot be added!!!\n");
                    break;
                }
                inputInfoCustomer(member1,&newCount,1,0);
                printf("\tAdd successfully!!!!\n");
                break;
            }
                // Chinh sua thong tin khach
            case 3: {
                if(numMember==0){
                    printf("\tThere are no Customers to edit!!!\n");
                    break;
                }
                editInforCustomer();
                break;
            }
                // Khoa tai khoan khach
            case 4:{
                if(numMember==0){
                    printf("\tThere are no Customers to lock/unlock!!!\n");
                    break;
                }
                toggleMemberStatus();
                break;
            }
                // Tim khach hang bang ten
            case 5:{
                if(numMember==0){
                    printf("\tThere are no Customer to search!!!\n");
                    break;
                }
                searchNameCustomer();
                break;
            }
                // Cho muon sach
            case 6:{
                if(numMember==0){
                    printf("\tThere are no customer to borrow!!!\n");
                    break;
                }
                if(numBooks==0){
                    printf("\tThere are no book to borrow!!!\n");
                    break;
            	}
                addBookByCustomer();
                break;
            }
                // Tra sach da muon
            case 7:{
				if(numMember==0){
				    printf("\tThere are no customer to return!!!\n");
				    break;
				}
				if(numBooks==0){
				    printf("\tThere are no book to return!!!\n");
				    break;
				}
				returnBookByLibrary();
                break;
            }
            case 0: {
            	system("cls");
            	printf("\tReturn menu!!!\n");
                return;
            }
            default:
                printf("\tYour selection is not on the menu!!!!\n");
                break;
        }
        pressAnyKey();
		system("cls");
    }
}

// Menu chinh sau khi nhap TK
void choiceMenuMain(){
	int choice;
	while (1) {
		system("color 4E");
		showMenuMain();
		printf("\tEnter The Choice : ");
		scanf("%d", &choice);
		switch(choice){
			case 1: {
			   	system("cls");
			    choiceMenuBook();
			    break;
			}
			case 2: {
			    system("cls");
				choiceMenuCustomer();
				break;
			}
			case 0: {
				system("cls");
				printf("\tExit the program!!!\n");
				return;
			}
			default:
				setColor(3);
				printf("\tYour selection is not on the menu!!!!\n");
				setColor(7);
				break;
		}
	}
}

// Menu Tai khoan
void showMenuAccount(){
	printf("\t\t\t\t\t%-42s\n","***STUDENT MANAGEMENT SYSTEM USING C***");
	printf("\t\t\t\t\t\t\tCHOOSE YOUR ROLE\n");
	printf("\t\t\t\t\t\t|==========================|\n");
	printf("\t\t\t\t\t\t| %-25s|\n","[1] Register Account");
	printf("\t\t\t\t\t\t| %-25s|\n","[2] Login Account");
	printf("\t\t\t\t\t\t| %-25s|\n","[3] Forget Password");
	printf("\t\t\t\t\t\t| %-25s|\n","[0] Exit the Program");
	printf("\t\t\t\t\t\t|==========================|\n");
}

// Luu danh sach vao file text
void saveAccountToTextFile(Account *nick2){
    FILE *f = fopen(FILE_NAME2, "a"); 
    if (f == NULL) {
        printf("\tCannot open %s file!!!\n", FILE_NAME2);
        return;
    }
    // Ghi thong tin vao file ( moi dong la mot gia tri)
    fprintf(f, "%s\n%s\n%s\n%s\n", nick2->name, nick2->email, nick2->phone, nick2->password);
    fclose(f);
    setColor(2);
    printf("\tSave Account Successfully!!!\n");
    setColor(7);
}


// Doc thong tin cua TK tu file
void readAccountsFromTextFile(){
    FILE *f = fopen(FILE_NAME2, "r");
    if (f == NULL) {
        printf("\tCannot open %s file!!!\n", FILE_NAME2);
        return;
    }
    numAccount=0;
	while (fscanf(f, "%49s\n%49s\n%14s\n%49s\n", nick1.name, nick1.email, nick1.phone, nick1.password) != EOF) {
    	numAccount++;
	}
	// Dong file
    fclose(f);
}

// Ham an mat khau khi dang nhap
void getPassword(char *password){
    int i = 0;
    char ch;
    while (1) {
    	// Nhap ki tu nhung khong hien len man hinh
        ch = getch();
        // Neu nhan enter
        if (ch == 13) { 
            password[i] = '\0';
            break;
        } else if (ch == 8 && i > 0){ 
        // Neu nhan Backspace, Xoa ky tu truoc do
            printf("\b \b");
            i--;
        } else if (i < 49){
        // Hien thi dau * thay cho so
            password[i++] = ch;
            printf("*"); 
        }
    }
}

// Ham kiem tra xem tai khoan da ton tai hay chua
int findAccountExistFromFile(const char *username){
    FILE *file = fopen(FILE_NAME2, "r");
    if (file == NULL) return 0; 
    Account acc;
    while (fscanf(file, "%49s\n%49s\n%14s\n%49s\n", acc.name, acc.email, acc.phone, acc.password) != EOF) {
        if (strcmp(acc.name, username) == 0) {
            fclose(file);
            return 1; // Tk da ton tai
        }
    }
    fclose(file);
    return 0; // TK chua ton tai
}

// Ham kiem tra tinh an toan cua password
int checkPasswordStrength(const char *password){
    int length = strlen(password);
    int upper = 0, lower = 0, digit = 0, special = 0;
    // Danh sach cac ki tu dac biet
    char specialChars[] = "!@#$%^&*+-/~<>.,?";

    // Kiem tra ki tu cua mk
    for(int i = 0; i < length; i++) {
        if(isupper(password[i])){
			upper = 1;
		}
        else if(islower(password[i])){
			lower = 1;
		}
        else if(isdigit(password[i])){
			digit = 1;
		}
        else if(strchr(specialChars, password[i])){
			special = 1;
		}
    }
	// Danh dau do manh cua mat khau
	// Rat yeu < 8
    if(length < 8) 
		return 0;
    // Rat manh
    if(upper && lower && digit && special) 
		return 3;
	// Trung binh
    if((upper||lower)&&digit||upper&&lower) 
		return 2;
	// Yeu
    return 1; 
}

// Ham tao password ngau nhien
void generateRandomPassWord(char *pass){
    char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*+-/~<>.,?"; 
    // Lay do dai cua mang tren
	int charsetSize = sizeof(charset) - 1;
	// Chin ki tu ngau nhien tu mang
    for (int i = 0; i < 12; i++) {
        pass[i] = charset[rand() % charsetSize]; 
    }
    // Thong bao ket thuc chuoi
    pass[12] = '\0'; 
}

// Dang ki tai khoan
void registerAccount(){
	// Nhap tai khoan
	printf("\t\tREGISTER ACCOUNT\n");
	fflush(stdin);
	while(1){
		printf("\tEnter account name : ");
		fgets(nick1.name,sizeof(nick1.name),stdin);
		nick1.name[strcspn(nick1.name,"\n")]='\0';
		if(findAccountExistFromFile(nick1.name)){
			setColor(4);
			printf("\tAccount name already exists!!!\n");
			setColor(7);
			continue;
		}
		setColor(2);
		printf("\tEnter successfully!!!\n");
		setColor(7);
		break;
	}
	// Nhap email
	fflush(stdin);
	while(1){
		printf("\tEnter email : ");
		fgets(nick1.email,sizeof(nick1.email),stdin);
		nick1.email[strcspn(nick1.email,"\n")]='\0';
		if(!isValidEmail(nick1.email)){
			setColor(4);
			printf("\tInvalid email!!!\n");
			setColor(7);
			continue;
		}
		setColor(2);
		printf("\tEnter successfully!!!\n");
		setColor(7);
		break;
	}
	// Nhap so dien thoai
	fflush(stdin);
	while(1){
		printf("\tEnter phone number : ");
		fgets(nick1.phone,sizeof(nick1.phone),stdin);
		nick1.phone[strcspn(nick1.phone,"\n")]='\0';
		if(!checkPhoneNumber(nick1.phone)){
			printf("\tInvalid phone number!!!\n");
			continue;
		}
		setColor(2);
		printf("\tEnter successfully!!!\n");
		setColor(7);
		break;
	}
	// Nhap password
	while(1){
		char confirmPass[50], tempPass[50];
		printf("\tEnter Password : ");
		getPassword(tempPass);
		// copy sang nick1->password
		strcpy(nick1.password,tempPass);
		printf("\n");
		// Kiem tra do manh yeu cua pass
		if(checkPasswordStrength(nick1.password)<2){
			setColor(4);
			printf("\tPassword is very weak, please enter again!!!\n");
			setColor(7);
			continue;
		}
		// Xac nhan lai pass
		printf("\tEnter again the password : ");
		getPassword(confirmPass);
		printf("\n");
		// Kiem tra coi hai lan nhap co khop hay khong
		if (strcmp(nick1.password, confirmPass) != 0) {
			setColor(4);
			printf("\tPasswords do not match!!!\n");
			setColor(7);
		    continue;
		}
		break;
	}
	saveAccountToTextFile(&nick1);
	pressAnyKey();
	system("cls");
}

// Ham dang nhap tai khoan
int loginAccount(){
	printf("\t\tLOGIN ACCOUNT\n");
	char username[50], password[50];
	// Nhap ten tai khoan
	fflush(stdin);
    printf("\tEnter account name : ");
	fgets(username,sizeof(username),stdin);
	username[strcspn(username,"\n")]='\0';
    // Nhap mat khau
    printf("\tEnter Password : ");
	getPassword(password);
	printf("\n");
	FILE *file = fopen(FILE_NAME2, "r");
	if (file == NULL) {
	    printf("\tCannot open %s file!!!\n", FILE_NAME2);
	    return 0;
	}
	Account acc;
    while(fscanf(file, "%49s\n%49s\n%14s\n%49s\n", nick1.name, nick1.email, nick1.phone, nick1.password) != EOF){
		if (strcmp(nick1.name, username)==0 && strcmp(nick1.password, password)==0) {
			fclose(file);
		    return 1;
		}
    }
    setColor(4);
    printf("\tAccount or password is incorrect!!!\n");
    setColor(7);
    pressAnyKey();
    system("cls");
	return 0;
}

// Tao mk tu email và so dien thoai
void GeneratePassword(){
	printf("\t\tFORGET ACCOUNT\n");
	printf("");
}

















