#include"datatype.h"
// HAM BO TRO TINH CHAC CHE LOGIC CUA CHUONG TRINH
// Ham chuyen doi dinh dang thang dd/mm/yyyy
char *formatConversionDate(Date d);
// Ham kiem tra ngay thang nam co hop le hay khong
int checkDateValid(int day,int month,int year);
// Chuyen doi true/false thanh chu
char *convert(bool status);
// Ham kiem tra so dien thoai co hop le hay khong
int checkPhoneNumber(char *phoneNumber);
// Ham sap xep phan trang sach
void displayPageBook(Book books[], int size, int page);
// Ham sap xep phan trang khach
void displayPageCustomer(Member members[], int size, int page);
// Clear het man hinh
int pressAnyKey();
// Ham kiem tra dinh danh email
int isValidEmail(const char *email);
// Ham doi mau tung dong
void setColor(int color);
// Mau galaxy
void galaxyEffect();

// HAM PHU BO SUNG CHO HAM CHINH
// Ham kiem tra xem ma sach co trung hay khong
bool checkIdExistBook(Book *bookList, int totalBooks, char *bookId);
// Ham kiem tra ten sach co trung hay khong
int checkTitleExistBook(const char *Title,int number,Book *book1);
// Kiem tra sach theo ma
int findIdByBook(const char *findIdBook);
// Hien thi bang thong tin sach
void showTableListBook();
// Ham kiem tra xem ma so khach co ton tai hay chua
int checkIdExistCustomer(Member *memberList, int totalMember, char *memberId);
// Ham kiem tra xem so dien thoai co ton tai hay chua
int checkPhoneNumberExistCustomer(Member *memberList, int totalMember, char *memberId);
// Kiem tra khach hang theo ma
int findIdByCustomer(const char *findIdCustomer);
// Ham dinh huong chuong trinh
void programOrientationBook();
// Ham dinh huong chuong trinh khach
void programOrientationCustomer();

// DANH SACH THU VIEN
// Hien thi menu chinh
void showMenuMain();
// Hien thi menu sach
void showMenuBook();
// Luu danh sach vao file nhi phan
void saveBookToBinaryFile(Book *book1);
// Doc thong tin cua sach tu file
void readBookFromBinaryFile(int mode);
// Nhap vao thong cua sach
void inputInfoBook(Book *book1,const int *i,int index,int mode);
// Chinh sua thong tin lop hoc
void editInforBook();
// Xoa sach
void deleteBook();
// Tim kiem sach theo ten
void searchTitleBook();
// Sap xep sach theo gia tien
void sortBooksByPrice();
// Lua chon tinh nang trong menu quan ly sach
void choiceMenuBook();

// DANH SACH KHACH HANG
//Hien thi menu khach hang
void showMenuCustomer();
// Luu thong tin khach vao file nhi phan
void saveCustomerToBinaryFile(Member *member2);
// Doc thong tin cua khach tu file
void readCustomerFromBinaryFile(int mode);
// Them va nhap thong tin cho khach 
void inputInfoCustomer(Member *member1,const int *i,int index,int mode);
// Chinh sua thong tin khach hang
void editInforCustomer();
// Khoa (Mo) thong tin khach hang
void toggleMemberStatus();
// Tim kiem khach hang theo ten
void searchNameCustomer();
// Cho muon sach ( toi da 5 quyen )
void addBookByCustomer();
// Tra lai sach da muon
void returnBookByLibrary();
// Lua chon tinh nang trong menu quan ly khach hang
void choiceMenuCustomer();
// Menu chinh sau khi nhap TK
void choiceMenuMain();

// TAI KHOAN
// Menu Tai khoan
void showMenuAccount();
// Luu danh sach vao file text
void saveAccountToTextFile(Account *nick2);
// Doc thong tin cua TK tu file
void readAccountsFromTextFile();
// Ham an mat khau khi dang nhap
void getPassword(char *password);
// Ham kiem tra xem tai khoan da ton tai hay chua
int findAccountExistFromFile(const char *username);
// Ham kiem tra tinh an toan cua password
int checkPasswordStrength(const char *password);
// Ham tao password ngau nhien
void generateRandomPassWord(char *pass);
// Dang ki tai khoan
void registerAccount();
// Ham dang nhap tai khoan
int loginAccount();
// Tao mk tu email và so dien thoai
void GeneratePassword();
