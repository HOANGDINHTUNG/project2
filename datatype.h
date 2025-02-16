#include <stdbool.h>
typedef struct{
    int day;// Ngay
    int month;// Thang
    int year;// Nam
}Date;
typedef struct{
    char bookId[10];// ID sach
    char title[35];// Tieu de sach
    char author[25];// Tac gia
    int quantity;// So luong sach co san
    int price;// Gia tien cua 1 cuon sach
    Date publication;// Ngay xuat ban
}Book;
typedef struct{
    char memberId[10];// ID khach
    char name[20];// Ten khach
    char phone[15];// So dien thoai
    bool status;// Trang thai Khoa mo
    Book BorrowedBooks[5];// liet ke nhung sach da muon
    int bookCount;// Dem so luong sach
}Member;
typedef struct{
	char name[50];
	char email[30];
	char phone[15];
	char password[50];
}Account;
