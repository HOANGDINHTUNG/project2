#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include"datatype.h"
#define MAX 500
#include "effect.h"
Book book1[MAX];
Member member1[MAX];

const char *FILE_NAME = "C:\\Users\\HOANG DINH TUNG\\Documents\\Projects\\Project6\\listBook.bin";
const char *FILE_NAME1 = "C:\\Users\\HOANG DINH TUNG\\Documents\\Projects\\Project6\\listCustomer.bin";
const char *FILE_NAME2 = "C:\\Users\\HOANG DINH TUNG\\Documents\\Projects\\Project6\\listAccounts.txt";

int numBooks=0;// So luong khach
int numMember=0;// So luong khach hang

// HAM BO TRO TINH CHAC CHE LOGIC CUA CHUONG TRINH

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
        if((year%4==0 && year%100!=0)||year%400==0){
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
    	setColor(4);
        printf("\tInvalid page!!!\n");
        setColor(6);
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
void pressAnyKey(){
	char c;
	fflush(stdin);
	printf("\tPress any key to return to the program!!!\n");
	scanf("%c",&c);
}

// Ham kiem tra dinh danh email
int isValidEmail(const char *email){
    // Bien dem '@' và bien dem dau '.'
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

// Ham doi mau tung dong
void setColor(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
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
        printf("\t\t\t\t\t\t=========== Thank You ============\n");
        printf("\t\t\t\t\t\t========== See You Soon ==========\n");
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
		if (page == 0){
			break;
		}
		if (page < 1 || page > totalPage) {
		    printf("\tInvalid Page! Input to 1 form %d.\n", totalPage);
		} 
		else{
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
		
		// Don moi khi qua trang
		pressAnyKey();
		system("cls");
		
		// Thoat chuong trinh
		if (page == 0){
			break;
		}
		if (page < 1 || page > totalPage) {
			setColor(4);
		    printf("\tInvalid Page! Input to 1 form %d.\n", totalPage);
		    setColor(6);
		}
		else {
			// Hien thi bang phan trang
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
    // Tao va mo file viet them
    FILE *f=fopen(FILE_NAME, "ab");
    if(f==NULL){
        printf("\tCannot open file %s write!!!\n",FILE_NAME);
        return;
    }
    
    // Ghi so luong vao file
    fwrite(book2,sizeof(Book),1,f);
    
    setColor(2);
    printf("\tSave file success!!!!\n");
    setColor(6);
    // Dong file
    fclose(f);
}

// Doc thong tin cua sach tu file
void readBookFromBinaryFile(int mode){
	// Tao mo file doc
    FILE *f=fopen(FILE_NAME,"rb");
    if(f==NULL){
        printf("\tFile %s no exist or no datas!!!\n",FILE_NAME);
        return;
    }
    
    // Tao bang
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
void inputInfoBook(Book *book1,int *i,int index,int mode){
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
                	setColor(4);
					printf("\tThe first character must be 'B'!!!\n");
					setColor(6);
					continue;
				}
				// Kiem tra cac ki tu sau co phai chu so hay khong
				for(int i=1;i < (int)strlen(input);i++){
				    if(*(input+i)<48||*(input+i)>57){
				        continue;
				    }
				}
                // Kiem tra do dai va ki rong
                if (strlen(input) == 0 || strlen(input) > 10) {
                	setColor(4);
                    printf("\tError: Book ID must be between 1 and 10 characters!!!\n");
                    setColor(6);
                    continue;
                }
                // Kiem tra Id co ton tai hay chua
                if(checkIdExistBook(book1,numBooks,input)){
                	setColor(4);
                    printf("\tError: Book ID already exists, Please enter a different one!!!\n");
                    setColor(6);
                    continue;
                }
                // Hop le luu vao danh sach
                strcpy(book1[j].bookId, input);
                setColor(2);
                printf("\tBook ID has been added successfully!\n");
                setColor(6);
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
            	setColor(4);
                printf("\tError: Book Title already exists, Please enter a different one!!!\n");
                setColor(6);
                continue;
            }
            strcpy(book1[j].title, input);
            setColor(2);
            printf("\tBook Title has been added successfully!\n");
            setColor(6);
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
            	setColor(4);
                printf("\tError: Book ID must be between 1 and 10 characters!!!\n");
                setColor(6);
                continue;
            }
            strcpy(book1[j].author, input);
            setColor(2);
            printf("\tBook Author has been added successfully!\n");
            setColor(6);
            break;
        }
        // MOI NHAP SO LUONG SACH CUNG LOAI
        while (1){
            fflush(stdin);
            printf("\tPlease enter the quantity of this book : ");
            scanf("%d",&book1[j].quantity);
            
            // Kiem tra so luong
            if (book1[j].quantity<=0) {
            	setColor(4);
                printf("\tError: The number of books must be greater than Zero!!!\n");
                setColor(6);
                continue;
            }
            setColor(2);
            printf("\tBook Quanlity has been added successfully!\n");
            setColor(6);
            break;
        }
        // NHAP GIA BAN CHO SACH
        while(1){
            fflush(stdin);
            printf("\tPlease enter the price : ");
            scanf("%d",&book1[j].price);
            // Kiem tra gia
            if (book1[j].price<1000){
            	setColor(4);
                printf("\tError: The price of a book must be greater than 1000!!!\n");
                setColor(6);
                continue;
            }
            setColor(2);
            printf("\tBook Price has been added successfully!\n");
            setColor(6);
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
                setColor(4);
                printf("\tInvalid, please again enter!!!\n");
                setColor(6);
            }
            else{
            	setColor(2);
                printf("\tEnter successfully!!!\n");
                setColor(6);
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
	// Hien thi tat ca thong tin cua sach
    readBookFromBinaryFile(1);
    
    // Nhap ma Id sach
    int n=1;
    fflush(stdin);
    char ma[10];
    printf("\tPlease enter Book Id want to edit : ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = '\0';
    
    // Lay chi so Id trong mang danh sach lop
    int index = findIdByBook(ma);
    
    // Xet ID co ton tai hay khong
    if (index == -1) {
    	setColor(4);
        printf("\tNo find Book ID!!!!\n");
        setColor(6);
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

    fwrite(book1, sizeof(Book), numBooks, f);
    
    // Dong file
    fclose(f);
    setColor(2);
    printf("\tUpdated information Book successfully!!!\n");
    setColor(6);
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
    
    // Xet truong hop khong tim thay
    if(index==-1){
    	setColor(4);
        printf("\tNo find Book ID!!!!\n");
        setColor(6);
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
            
            fwrite(book1, sizeof(Book), numBooks, f);
            
            // Dong file
            fclose(f);
            setColor(2);
            printf("\tDelete Book successfully!!!\n");
            setColor(6);
            return;
        }
        else{
            return;
        }
    }
}

// Tim kiem sach theo ten
void searchTitleBook(){
	// Bien dem sep luong ket qua tim thay
    int numResults=0;
    
    // Nhap tu khoa tua sach de tim kiem
    char keyWords[30];
    fflush(stdin);
    Book results[numBooks]; // Cau truc luu thong tin
    printf("\tPlease enter keywords to find books : ");
    fgets(keyWords, sizeof(keyWords), stdin);
    keyWords[strcspn(keyWords, "\n")] = 0;
    
    // Duyet lan lua tua voi tu khoa
    for(int i=0;i<numBooks;i++){
        if (strstr(book1[i].title, keyWords) != NULL) {
            results[numResults++] = book1[i];
        }
    }
    
    // Neu tim thay thi in ra
    if(numResults>0){
    	setColor(2);
        printf("\tSearch results:\n");
        setColor(6);
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
    	setColor(4);
        printf("\tNo books found!!!\n");
        setColor(6);
    }
}

// Sap xep sach theo gia tien
void sortBooksByPrice(){
    // Nhap lua chon
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
            
            // Dieu huong xap xep phan trang
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
            
            // Dieu huong sap xep phan trang
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
    	
    	// Doc cac list sach tu file
		readBookFromBinaryFile(0);
		        
		// Doc danh sach khach hang tu file
		readCustomerFromBinaryFile(0);
		
		// Hien thi menu Sach
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
            // Thoat chuong trinh
            case 0: {
            	system("cls");
            	printf("\tReturn menu!!!\n");
                return;
            }
            // Nhap su lua chon khac
            default:
                printf("\tYour selection is not on the menu!!!!\n");
                break;
        }
        
        // Don dep
        pressAnyKey();
		system("cls");
    }
}

// DANH SACH KHACH HANG
// Hien thi menu khach hang
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
	// Tao mo file doc
    FILE *f=fopen(FILE_NAME1,"rb");
    if(f==NULL){
        printf("\tFile %s no exist or no datas!!!\n",FILE_NAME1);
        return;
    }
    // Reset so luong bang 0
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
void inputInfoCustomer(Member *member1,int *i,int index,int mode){
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
					setColor(4);
					printf("\tThe first character must be 'K' and 'H'!!!\n");
					setColor(6);
					continue;
				}
				
				// Kiem tra cac ki tu sau co phai chu so hay khong
				for(int i=2 ; i < (int)strlen(input) ; i++){
					if(*(input+i)<48||*(input+i)>57){
						setColor(4);
						printf("\tError: Phone number with letters!!!\n");
						setColor(6);
						continue;
						}
					}
				
                // Kiem tra do dai va ki tu rong
                if (strlen(input) == 0 || (int)strlen(input) > 10) {
                	setColor(4);
                    printf("\tError: Customers ID must be between 1 and 10 characters!!!\n");
                    setColor(6);
                    continue;
                }
            	
            	// Kiem tra Id co trung khong
                if(checkIdExistCustomer(member1,numMember,input)){
                	setColor(4);
                    printf("\tError: Customers ID already exists, Please enter a different one!!!\n");
                    setColor(6);
                    continue;
                }
                
                // Hop le va luu vao danh sach
                strcpy(member1[j].memberId, input);
                setColor(2);
                printf("\tCustomers ID %s has been added successfully!\n", member1[j].memberId);
                setColor(6);
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
        	// Nhap So dien thoai
			fflush(stdin);
			char input[15];
			printf("\tPlease enter the phone Number : ");
			fgets(input,sizeof(input),stdin);
			input[strcspn(input,"\n")]='\0';
			
			// Kiem tra so dien thoai co hop ly hay khong
			if(!checkPhoneNumber(input)){
				setColor(4);
				printf("\tInvalid phone number!!!\n");
				setColor(6);
				continue;
			}
			
			// Kiem tra su sdt co trung hay khong
			if(checkPhoneNumberExistCustomer(member1,numMember,input)){
				setColor(4);
				printf("\tThis phone number is valid!!!\n");
				setColor(6);
				continue;
			}
			setColor(2);
			printf("\tEnter successful phone number!!!\n");
			setColor(6);
			strcpy(member1[j].phone,input);
			break;
		}
		
        // Nhap trang thai khach hang
        if(mode==0){
            while(1){
            	// Nhap true hoac false
                fflush(stdin);
                char input[50];
                printf("\tPlease enter the status Customer (true : Unlock/false : Lock) : ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input,"\n")]='\0';
            	
            	// Kiem tra
                if (strcmp(input, "true") == 0) {
                    member1[j].status = true;
                    break;
                } else if (strcmp(input, "false") == 0) {
                    member1[j].status = false;
                    break;
                } else {
                	setColor(4);
                    printf("\tError, can enter 'true' or 'false'!!!\n");
                    setColor(6);
                }
            }
        }
        
        // So luong sach ( ban dau mac dinh la 0 )
        if(member1[j].status==false){
        	setColor(4);
            printf("\tThe customer is status lock of not borrowing books!!!\n");
            setColor(6);
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
	// Hien thi sanh sach tat ca khach hang
    readCustomerFromBinaryFile(1);
    
    // Nhap ma
    int n=1;
    fflush(stdin);
    char ma[10];
    printf("\tPlease enter Customer Id want to edit : ");
    fgets(ma, sizeof(ma), stdin);
    ma[strcspn(ma, "\n")] = '\0';
    
    // Lay chi so ID trong mang danh sach khach hang
    int index = findIdByCustomer(ma);
    
    // Xet xem ma co tin tai hay khong
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
    
    
    fwrite(member1, sizeof(Member), numMember, f);
    
    // Dong file
    fclose(f);
    printf("\tUpdated information Customer successfully!!!\n");
}

// Khoa (Mo) thong tin khach hang
void toggleMemberStatus(){
	// Nhap Id khach can khoa
    char Id[10];
    fflush(stdin);
    printf("\tInput Customer Id need Lock/Unlock : ");
    fgets(Id, sizeof(Id), stdin);
    Id[strcspn(Id, "\n")] = '\0';
    
    // Lay chi so Id trong danh sach khach hang
    int index = findIdByCustomer(Id);
    
    // Xet xem ID co ton tai hay khong
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
    
    // Nhap lua chon yes hoac no
    char choice[5];
    fflush(stdin);
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';
    
    // So sach ki tu nhap vao voi ki tu cho san
    if (strcmp(choice,"yes")==0 || strcmp(choice,"Yes")==0) {
        // Dao trang thai(khoa-mo/mo-khoa)
        member1[index].status = !member1[index].status;
        
        // Thong bao
        setColor(2);
        printf("\tClient %s has been %s successfully!!!\n",member1[index].name,member1[index].status ? "unlocked" : "locked");
        setColor(6);
        
        // Cap nhat vao file
        FILE *f = fopen(FILE_NAME1, "wb");
		if (f == NULL) {
		    printf("\tError opening file %s!\n", FILE_NAME1);
		    return;
		}
		    
		fwrite(member1, sizeof(Member), numMember, f);
		    
		// Dong file
		fclose(f);
    }
    else {
    	setColor(4);
        printf("\tCanceled\n");// Huy khi khong nhap dung tu khoa cho san
        setColor(6);
    }
}

// Tim kiem khach hang theo ten
void searchNameCustomer(){
	// Bien dem ket qua tim thay
    int numResults=0;
    
    // Nhap tu khoa
    char keyWord[30];
    fflush(stdin);
    Member results[numMember]; // Cau truc luu thong tin khach
    printf("\tPlease enter keywords name to find Client : ");
    fgets(keyWord, sizeof(keyWord), stdin);
    keyWord[strcspn(keyWord, "\n")] = 0;
    
    // Duyet xem ten khach co chua tu khoa hay khong
    for(int i=0;i<numMember;i++){
        if (strstr(member1[i].name, keyWord) != NULL) {
            results[numResults++] = member1[i];
        }
    }
    
    // Neu ket qua tim thay lon hon 0 thi in danh sach tim duoc
    if(numResults>0){
        printf("\tSearch results:\n");
        printf("#***********#**************************#****************#***********#****************#\n");
        printf("$%-11s$%-26s$%-16s$%-11s$%-16s$\n","ID","NAME","PHONE","STATUS","BORROWED BOOKS");
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
    else{// Khong tim thay
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
    customerId[strcspn(customerId, "\n")] = '\0';

    // Tim Id khach hang
    int index = findIdByCustomer(customerId);
    if (index == -1) {
        setColor(4);
        printf("\tNo find Customer ID!!!!\n");
        setColor(6);
        return;
    }

    // KiEm tra xem khach hang co bi khoa hay khong
    if (!member1[index].status) {
        setColor(4);
        printf("\tCustomer is locked!!!\n");
        setColor(6);
        return;
    }

    // Kiem tra so luong scah da muon
    if (member1[index].bookCount >= 5) {
        setColor(4);
        printf("\tCustomer has already borrowed the maximum number of books (5)!\n");
        setColor(6);
        return;
    }

    // Kiem tra xem thu vien co sach hay khong
    if (numBooks == 0) {
    	setColor(4);
        printf("\tNo books available in the library!!!\n");
        setColor(6);
        return;
    }

    // Hien thi sach co san
    printf("\tBooks available in the library:\n");
    printf("\t| %-10s | %-30s | %-10s |\n", "ID", "TITLE", "QUANTITY");
    for (int i = 0; i < numBooks; i++) {
        printf("\t| %-10s | %-30s |    %-7d |\n", book1[i].bookId, book1[i].title, book1[i].quantity);
    }

    // Nhap so luong sach muon muon
    int n;
    do {
        printf("\tEnter number of books to borrow (max 5, remain %d): ", (5 - member1[index].bookCount));
        scanf("%d", &n);
    } while (n <= 0 || n > (5 - member1[index].bookCount));
    getchar();

    // Nhap ID sach can muon
    for (int i = 0; i < n; i++) {
        char bookId[10];
        while (1) {
            printf("\tInput Book Id %d: ", i + 1);
            fgets(bookId, sizeof(bookId), stdin);
            bookId[strcspn(bookId, "\n")] = '\0';

            // Kiem tra xem sach co ton tai hay khong
            int index1 = findIdByBook(bookId);
            if (index1 == -1) {
            	setColor(4);
                printf("\tBook ID does not exist, please enter again\n");
                setColor(6);
                continue;
            }

            // Kiem tra xem sach co con hay khong
            if (book1[index1].quantity <= 0) {
                setColor(4);
                printf("\tThis book is out of stock, please choose another one!!\n");
                setColor(6);
                continue;
            }

            // Them vao danh sach muon cua khach
            strcpy(member1[index].BorrowedBooks[member1[index].bookCount].bookId, bookId);
            member1[index].bookCount++;

            // Giam so luong sach trong thu vien
            book1[index1].quantity--;

            break;
        }
    }

    // Ghi lai thong tin khach hang vao file
    FILE *f = fopen(FILE_NAME1, "wb");
    if (f == NULL) {
        printf("\tError opening file %s!\n", FILE_NAME1);
        return;
    }
    
    fwrite(member1, sizeof(Member), numMember, f);
    
    // Dong file
    fclose(f);

    // Ghi thong tin sach vao file
    FILE *f1 = fopen(FILE_NAME, "wb");
    if (f1 == NULL) {
        printf("\tError opening file %s!\n", FILE_NAME);
        return;
    }
    
    fwrite(book1, sizeof(Book), numBooks, f1);
    
    // Dong file
    fclose(f1);
	
    printf("\tUpdated information Customer successfully!!!\n");
}

// Tra lai sach da muon
void returnBookByLibrary(){
    // Nhap id khach hang
    char customerId[10];
    fflush(stdin);
    printf("\tPlease enter Id to find Client : ");
    fgets(customerId, sizeof(customerId), stdin);
    customerId[strcspn(customerId,"\n")]='\0';
    
    // Tim kiem vi tri
    int index= findIdByCustomer(customerId);
    
    // Id khach hang khong ton tai
    if(index == -1) {
    	setColor(4);
        printf("\tNo find Customer ID!!!!\n");
        setColor(6);
        return;
    }
    
    // Khach hang khong co sach
    if(!member1[index].bookCount){
    	setColor(4);
        printf("\tCustomer has no book to return!!!\n");
        setColor(6);
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
    
    // Kiem tra Id sach nhap vao 
    int index2 = findIdByBook(Id);
	if (index2 == -1) {
		setColor(4);
	    printf("\tBook ID does not exist in the library!!!\n");
	    setColor(6);
	    return;
	}
	
    // Tra lai sach (xoa sach)
    for(int i=0;i<member1[index].bookCount;i++){
        if(strcmp(Id,member1[index].BorrowedBooks[i].bookId)==0){
            for(int j=i;j<member1[index].bookCount-1;j++){
                member1[index].BorrowedBooks[j] = member1[index].BorrowedBooks[j + 1];
            }
            --(member1[index].bookCount);
        }
    }
    
    // Cong lai sach cho thu vien
    book1[index2].quantity++;
    
    // Tao va mo file viet cho khach
	FILE *f=fopen(FILE_NAME1, "wb");
	if(f==NULL){
		setColor(4);
		printf("\nFile %s no exsit or no datas!!!\n",FILE_NAME1);
		setColor(6);
		return;
	}
	
	fwrite(member1, sizeof(Member), numMember, f);
	
	// Dong file
	fclose(f);
	
	// Tao va mo file viet cho sach
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
	setColor(2);
	printf("\tDelete Book successfully!!!\n");
	setColor(6);
}

// Lua chon tinh nang trong menu quan ly khach hang
void choiceMenuCustomer(){
    while (1) {
    	system("color 6");
    	// Doc cac list sach tu file
        readBookFromBinaryFile(0);
        
        // Doc danh sach khach hang tu file
        readCustomerFromBinaryFile(0);
        
        // Hien thi menu lua chon tinh nang khach hang
        showMenuCustomer();
        
        // Bien lua chon va bien dem
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
            // Thoa chuong trinh
            case 0: {
            	system("cls");
            	printf("\tReturn menu!!!\n");
                return;
            }
            // Nhap su lua chon khac
            default:
                printf("\tYour selection is not on the menu!!!!\n");
                break;
        }
        
        // Don dep
        pressAnyKey();
		system("cls");
    }
}

// Menu chinh sau khi nhap TK
void choiceMenuMain(){
	int choice;
	while (1) {
		system("color 4E");
		
		// Hien thi menu chinh
		showMenuMain();
		
		// Nhap lua chon
		printf("\tEnter The Choice : ");
		scanf("%d", &choice);
		switch(choice){
			// Hien thi su lua chon Sach
			case 1: {
			   	system("cls");
			    choiceMenuBook();
			    break;
			}
			// Hien thi sua lua chon khach hang
			case 2: {
			    system("cls");
				choiceMenuCustomer();
				break;
			}
			// Thoat chuong trinh
			case 0: {
				system("cls");
				printf("\tExit the program!!!\n");
				return;
			}
			// Nhap su lua chon khac
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
	printf("\t\t\t\t\t%-42s\n","***WELCOME TO THE LIBRARY MANAGEMENT SYSTEM***");
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
	// Tao mo file viet them
    FILE *f = fopen(FILE_NAME2, "a"); 
    if (f == NULL) {
        printf("\tCannot open %s file!!!\n", FILE_NAME2);
        return;
    }
    
    // Ghi thong tin vao file ( moi dong la mot gia tri)
    fprintf(f, "%s\n%s\n%s\n%s\n", nick2->name, nick2->email, nick2->phone, nick2->password);
    
    // Dong file
    fclose(f);
    setColor(2);
    printf("\tSave Account Successfully!!!\n");
    setColor(7);
}

// Doc thong tin cua TK tu file
void readAccountsFromTextFile(){
	// Tao mo file viet
    FILE *f = fopen(FILE_NAME2, "r");
    if (f == NULL) {
        printf("\tCannot open %s file!!!\n", FILE_NAME2);
        return;
    }
    
    Account nick1;
	while (fscanf(f, "%49s\n%49s\n%14s\n%49s\n", nick1.name, nick1.email, nick1.phone, nick1.password) != EOF);
	
	// Dong file
    fclose(f);
}

// Ham an mat khau khi dang nhap
void getPassword(char *password){
    int i = 0;
    char ch;
    while(1){
    	// Nhap ki tu nhung khong hien len man hinh
        ch = getch();
        
        // Neu nhan enter
        if (ch == 13){ 
            password[i] = '\0';
            break;
        } 
		else if (ch == 8 && i > 0){ 
        // Neu nhan Backspace, Xoa ky tu truoc do
            printf("\b \b");
            i--;
        } 
		else if (i < 49){
        // Hien thi dau * thay cho so
            password[i++] = ch;
            printf("*"); 
        }
    }
}

// Ham kiem tra xem tai khoan da ton tai hay chua
int findAccountExistFromFile(const char *username){
	// Tao mo file viet
    FILE *file = fopen(FILE_NAME2, "r");
    if (file == NULL){
		printf("\tCannot open %s file!!!\n",FILE_NAME2);
		return 0;
	} 
	
    Account acc;
    while (fscanf(file, "%49s\n%49s\n%14s\n%49s\n", acc.name, acc.email, acc.phone, acc.password) != EOF) {
        if (strcmp(acc.name, username) == 0) {
            fclose(file);
            return 1; // Tk da ton tai
        }
    }
    
    // Dong file
    fclose(file);
    return 0; // TK chua ton tai
}

// Ham kiem tra tinh an toan cua password
int checkPasswordStrength(const char *password){
	// Lay do dai
    int length = strlen(password);
    
    // Bien dem ki tu in HOA, in THUONG, ki tu SO, ki tu DAC BIET
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
    if(((upper || lower) && digit ) || (upper && lower))
		return 2;
		
	// Yeu
    return 1; 
}

// Ham tao password ngau nhien
void generateRandomPassWord(char *pass){
	// Cho dang ki tu can lay 
    char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*+-/~<>.,?";
    
    // Lay do dai cua mang tren
	int charsetSize = sizeof(charset) - 1;
	
	// Moi lan chay se tao ra mot mk khac nhau 
	srand(time(NULL));
	
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
	Account acc;
	while(1){
		// Nhap ten
		printf("\tEnter account name : ");
		fgets(acc.name,sizeof(acc.name),stdin);
		acc.name[strcspn(acc.name,"\n")]='\0';
		
		// Tìm kiem xem ten co trong file hay chua, neu co thi nhap lai
		if(findAccountExistFromFile(acc.name)){
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
		fgets(acc.email,sizeof(acc.email),stdin);
		acc.email[strcspn(acc.email,"\n")]='\0';
		
		// Kiem tra Email co dung dinh dang hay chua, neu chua thi nhap lai
		if(!isValidEmail(acc.email)){
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
		fgets(acc.phone,sizeof(acc.phone),stdin);
		acc.phone[strcspn(acc.phone,"\n")]='\0';
		
		// Kiem tra so dien thoai co dung dinh dang hay chua
		if(!checkPhoneNumber(acc.phone)){
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
		// Bien pass nhap lai và bien luu tru pass tam thoi
		char confirmPass[50], tempPass[50];
		printf("\tEnter Password : ");
		getPassword(tempPass);
		
		// copy sang nick1->password
		strcpy(acc.password,tempPass);
		printf("\n");
		
		// Kiem tra do manh yeu cua pass
		if(checkPasswordStrength(acc.password)<2){
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
		if (strcmp(acc.password, confirmPass) != 0) {
			setColor(4);
			printf("\tPasswords do not match!!!\n");
			setColor(7);
		    continue;
		}
		break;
	}
	
	// Luu thong tin vao file
	saveAccountToTextFile(&acc);
	
	// Don dep
	pressAnyKey();
	system("cls");
}

// Ham dang nhap tai khoan
int loginAccount(){
	printf("\t\tLOGIN ACCOUNT\n");
	// Bien dung luu tru ten và pass 
	char username[50], password[50];
	
	// Nhap ten tai khoan
	fflush(stdin);
    printf("\tEnter account name : ");
	fgets(username,sizeof(username),stdin);
	username[strcspn(username,"\n")]='\0';
	
    // Nhap mat khau
    printf("\tEnter Password : ");
	
	// Nhap mk chuyen sang dau '*'
	getPassword(password);
	printf("\n");
	
	// Tao va mo file
	FILE *file = fopen(FILE_NAME2, "r");
	if (file == NULL) {
	    printf("\tCannot open %s file!!!\n", FILE_NAME2);
	    return 0;
	}
	
	// Bien cau truc
	Account acc;
    while(fscanf(file, "%49s\n%49s\n%14s\n%49s\n", acc.name, acc.email, acc.phone, acc.password) != EOF){
		if (strcmp(acc.name, username)==0 && strcmp(acc.password, password)==0) {
			// Dong file
			fclose(file);
		    return 1;
		}
    }
    setColor(4);
    printf("\tAccount or password is incorrect!!!\n");
    setColor(7);
    
    // Don dep
    pressAnyKey();
    system("cls");
	return 0;
}

// Tao mk tu email và so dien thoai
void GeneratePassword(){
	fflush(stdin);
	// Cau truc luu tai khoan
	Account account1[20];
	
	// Bien danh dau xuat hien và bien dem so tai khoan
	int found=0, numAccount=0;
	
	// Bien dung de so sach voi bien da luu
	char email[50],phone[15],tempPass[15];
	
	// Nhap email
	printf("\t\tFORGET ACCOUNT\n");
	printf("\tPlease enter email : ");
	fgets(email,sizeof(email),stdin);
	email[strcspn(email,"\n")]='\0';
	
	// Nhap so dien thoai
	printf("\tPlease enter phone number : ");
	fgets(phone,sizeof(phone),stdin);
	phone[strcspn(phone,"\n")]='\0';
	
	// Tao mà mo file de doc
	FILE *file = fopen(FILE_NAME2, "r");
	if (file == NULL) {
	    printf("\tCannot open %s file!!!\n", FILE_NAME2);
	}
	
	// Doc danh sach tu file
	while(!feof(file)){ // Lap lai co den khi EOF
		char *fields[] = {account1[numAccount].name, 
						  account1[numAccount].email, 
						  account1[numAccount].phone, 
						  account1[numAccount].password };
		for (int i = 0; i < 4; i++) {
			if (fgets(fields[i], 50, file)) {
			    fields[i][strcspn(fields[i], "\n")] = '\0';
			} else {
			    // Thoat neu khong doc duoc
			    break; 
			}
		}
		// Den so luong tai khoan
		numAccount++;
	}
	
	// Dong file
	fclose(file);
	
	// Kiem tra email va sdt co khop hay khong
	    for (int i = 0; i < numAccount; i++){
	        if (strcmp(account1[i].email, email) == 0 && strcmp(account1[i].phone, phone) == 0) {
	            // Danh dau tim thay
				found = 1;
				
				// Tao mk bat ki và luu vao cau truc
	            generateRandomPassWord(tempPass);
	            strcpy(account1[i].password, tempPass);
	            
	            printf("\tNew password: ");
	            setColor(2 );
	            printf("%s\n", tempPass);
	            setColor(7);
	            break;
	        }
	    }
	// Neu khong khong tim thay thi ket thuc
    if(!found){
		setColor(4);
		printf("\tEmail or phone number is incorrect!!!\n");
		setColor(7);
		
		// Don dep 
		pressAnyKey();
		system("cls");
		return;
	}
	
    // Ghi lai tai khoan vao file
	FILE *tempFile = fopen(FILE_NAME2, "w");
	if (tempFile == NULL) {
	    printf("\tCannot open %s file!\n", FILE_NAME2);
	    return;
	}
	
	// Duyet tung tai khoan
	for (int i = 0; i < numAccount; i++){
	    fprintf(tempFile, "%s\n%s\n%s\n%s\n", account1[i].name, account1[i].email, account1[i].phone, account1[i].password);
	}
	
	// Dong file
	fclose(tempFile);
	
	// Don dep
	pressAnyKey();
	system("cls");
}
