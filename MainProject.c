#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int day, month, year;
} Date;
typedef struct {
    char productId[10];
    char name[50];
    char unit[10];
    int qty;
    int status;
} Product;

typedef struct {
    char transId[20];
    char productId[10];
    char type[10];
    Date date;
	int amount;
} Transaction;

Product listProduct[50] = {
{"MS001", "My Cay", "Hop", 100, 1},
{"MS002", "Dua Hau", "Kg", 20, 1},
{"MS003", "Kem Dau", "Cai", 20, 1},
{"MS004", "Socola", "Hop", 50, 1},
{"MS005", "Com Hop", "Hop", 30, 1},
{"MS006", "Bim Bim", "Cai", 60, 1},
{"MS007", "Chocopie", "Hop", 30, 1},
{"MS008", "Xuc Xich", "Cai", 35, 1},
{"MS009", "Banh Bao", "Cai", 40, 1},
{"MS010", "Thuoc La", "Hop", 20, 1}};

int page = 1;
int itemsPerPage = 5;

Transaction listTransaction[50];

void addProduct(Product ds[], int *n);
void displayProduct(Product ds[], int n);
int duplicateProduct(Product ds[], int n, char duplicate[]);
void updateProduct(Product ds[], int n);
void searchProduct(Product ds[], int n);
void namesortProduct(Product ds[], int n);
void qtysortProduct(Product ds[], int n);
void paginationProduct(Product ds[], int n);
void deleteProduct(Product ds[], int *n);
void lockedProduct(Product ds[], int n);
void importProduct(Product ds[], int n, Transaction logs[], int *logCount);
void showHistory(Product ds[], Transaction logs[], int logCount);
int confirmDateOrder(int day, int month, int year);

int main(){
    int n = 10;
	int logCount = 0;
    int choice;
	char choose, choose1, choose2;
	int backMenu = 1;
    char comfirm = 'Y';

    do {
		system("cls");
		displayProduct(listProduct, n);
		printf("+---------------------------------------------+\n");
		printf("|          QUAN LY CUA HANG TIEN LOI          |\n");
    	printf("+---------------------------------------------+\n");
    	printf("|1. Them Ma Hang Moi                          |\n");
    	printf("|2. Cap Nhat Thong Tin Theo ID (E.g: MS001)   |\n");
    	printf("|3. Quan Ly Trang Thai (Khoa/Xoa)             |\n");
    	printf("|4. Tra Cuu Thong Tin                         |\n");
    	printf("|5. Danh Sach Phan Trang                      |\n");
    	printf("|6. Sap Xep Danh Sach (Ten/SoLuong)           |\n");
    	printf("|7. Giao Dich (Xuat/Nhap) Hang Hoa            |\n");
    	printf("|8. Lich Su (Xuat/Nhap)                       |\n");
		printf("|9. Thoat Khoi Quan Ly                        |\n");
    	printf("+---------------------------------------------+\n\n");
    	printf("Nhap Lua Chon: ");
    	scanf("%d", &choice);

		getchar();
    	
    	switch (choice){
    		case 1:
    			addProduct(listProduct, &n);
    			break;
    		case 2:
			    updateProduct(listProduct, n);
    			break;
    		case 3:
			    do{
					system("cls");
					displayProduct(listProduct, n);
					printf("\n+----------------------------------------+\n");
					printf("|     QUAN LY TRANG THAI (LOCK/DELETE)   |\n");
					printf("+----------------------------------------+\n");
					printf("|a. Khoa San Pham                        |\n");
					printf("|b. Xoa San Pham                         |\n");
					printf("|c. Quay Lai Trang Chu                   |\n");
					printf("+----------------------------------------+\n\n");
					printf("Nhap lua chon cua ban: ");
					scanf(" %c", &choose);
					switch (choose) {
					case 'a':
					    lockedProduct(listProduct, n);
					    fflush(stdin);
					    printf("\nNhan Enter de tiep tuc...");
						getchar();
						break;
					case 'b':
					    deleteProduct(listProduct, &n);
					    printf("\nNhan Enter de tiep tuc...");
						getchar();
						break;
					case 'c':
						printf("\nTro lai trang chu.\n");
						backMenu = 0;
						break;
					default:
					    getchar();
					    printf("\nNhap lai lua chon. Nhan Enter de tiep tuc...");
						getchar();
						break;
					}
				} while (choose != 'c');
				break;
    		case 4:
			    searchProduct(listProduct, n);
    			break;
    		case 5:
			    paginationProduct(listProduct, n);
    			break;
    		case 6:
			    do{
					system("cls");
					displayProduct(listProduct, n);
					printf("\n+----------------------------------------+\n");
					printf("|     QUAN LY TRANG THAI SAP XEP         |\n");
					printf("+----------------------------------------+\n");
					printf("|a. Sap Xep Theo Ten                     |\n");
					printf("|b. Sap Xep Theo So Luong Tang Dan       |\n");
					printf("|c. Quay Lai Trang Chu                   |\n");
					printf("+----------------------------------------+\n\n");
					printf("Nhap lua chon cua ban: ");
					scanf(" %c", &choose1);
					switch (choose1) {
					case 'a':
					    namesortProduct(listProduct, n);
					    getchar();
					    printf("\nNhan Enter de tiep tuc...");
						getchar();
						break;
					case 'b':
					    qtysortProduct(listProduct, n);
					    getchar();
					    printf("\nNhan Enter de tiep tuc...");
						getchar();
						break;
					case 'c':
						printf("\nTro lai trang chu.\n");
						backMenu = 0;
						break;
					default:
					    getchar();
					    printf("\nNhap lai lua chon. Nhan Enter de tiep tuc...");
						getchar();
						break;
					}
				} while (choose1 != 'c');
				break;
    		case 7:
			    do{
					system("cls");
					displayProduct(listProduct, n);
					printf("\n+----------------------------------------+\n");
					printf("|        QUAN LY TRANG THAI (IN/OUT)     |\n");
					printf("+----------------------------------------+\n");
					printf("|a. Nhap Hoac Xuat Hang Hoa              |\n");
					printf("|b. Quay Lai Trang Chu                   |\n");
					printf("+----------------------------------------+\n\n");
					printf("Nhap lua chon cua ban: ");
					scanf(" %c", &choose2);
					switch (choose2) {
					case 'a':
					    importProduct(listProduct, n, listTransaction, &logCount);
						getchar();
					    printf("\nNhan Enter de tiep tuc...");
						getchar();
						break;
					case 'b':
						printf("\nTro lai trang chu.\n");
						backMenu = 0;
						break;
					default:
					    getchar();
					    printf("\nNhap lai lua chon. Nhan Enter de tiep tuc...");
						getchar();
						break;
					}
				} while (choose2 != 'b');
    			break;
    		case 8:
			    showHistory(listProduct, listTransaction, logCount);
    			break;
    		case 9:
    			printf("\nBan Da Thoat Khoi He Thong!\n");
    			exit(0);
    		default:
    			printf("\nVui Long Nhap Lai Lua Chon (0-9)!\n");
				break;
		}
		do {
		printf("\nBan Co Muon Tiep Tuc Khong (Y/N)? ");
		scanf("%s", &comfirm);
		if(comfirm != 'N' && comfirm != 'n' && comfirm != 'Y' && comfirm != 'y'){
			printf("\nChi duoc nhap Y hoac N!\n");
		}
	} while (comfirm != 'N' && comfirm != 'n' && comfirm != 'Y' && comfirm != 'y');
	} while (comfirm == 'Y' || comfirm == 'y');
}
void addProduct(Product ds[], int *n){ 
	int addCount;
	char strNumber[10];

	while (1){
		printf("Nhap so luong muon them: ");
		fgets(strNumber, 10, stdin);
		strNumber[strcspn(strNumber, "\n")] = '\0';
		if(strspn(strNumber, " \t") == strlen(strNumber)){
			printf("\nKhong duoc de trong!\n");
		} else {
			addCount = atoi(strNumber);
			if(addCount < 0){
				printf("\nPhai nhap so duong!\n");
			}			
			if(addCount == 0){
				printf("\nPhai nhap vao la so!\n");			
			}
			if(addCount > 0){
				break;
			}
		}
	}
    for (int i = 0; i < addCount; i++) {
        fflush(stdin);
		do {
            printf("Nhap ma san pham: ");
            fgets(ds[*n].productId, 50, stdin);
            ds[*n].productId[strcspn(ds[*n].productId, "\n")] = '\0';
            if(strspn(ds[*n].productId, " \t") == strlen(ds[*n].productId)){
            	printf("\nMang rong vui long nhap lai!\n");
            	continue;
            }
            if (duplicateProduct(ds, *n, ds[*n].productId)){
            	printf("\nMa da bi trung hay nhap lai!\n");
            	continue;
			}
		} while (strspn(ds[*n].productId, " \t") == strlen(ds[*n].productId) || duplicateProduct(ds, *n, ds[*n].productId));

        do {
            printf("Nhap ten san pham: ");
            fgets(ds[*n].name, 50, stdin);
            ds[*n].name[strcspn(ds[*n].name, "\n")] = '\0';
            if(strspn(ds[*n].name, " \t") == strlen(ds[*n].name)){
            	printf("\nMang rong vui long nhap lai!\n");
            	continue;
			}
            if (duplicateProduct(ds, *n, ds[*n].name)){
            	printf("\nTen da bi trung hay nhap lai!\n");
            	continue;
			}
		} while (strspn(ds[*n].name, " \t") == strlen(ds[*n].name) || duplicateProduct(ds, *n, ds[*n].name));

		do {
			printf("Don vi hang hoa (Cai/KG/Hop): ");
			fgets(ds[*n].unit, 10, stdin);
			ds[*n].unit[strcspn(ds[*n].unit, "\n")] = '\0';
			if (strlen(ds[*n].unit) == 0) {
				printf("\nMang rong, vui long nhap lai!\n");
			}else if (strcmp(ds[*n].unit, "Cai") != 0 &&
				strcmp(ds[*n].unit, "KG")  != 0 &&
				strcmp(ds[*n].unit, "Hop") != 0) 
			{
				printf("\nVui long nhap dung (Cai/KG/Hop)!\n");
			}
		} while (
			strlen(ds[*n].unit) == 0 ||
			(strcmp(ds[*n].unit, "Cai") != 0 &&
			strcmp(ds[*n].unit, "KG")  != 0 &&
			strcmp(ds[*n].unit, "Hop") != 0));

		while (1){
			printf("So luong ton kho: ");
			fgets(strNumber, 10, stdin);
			strNumber[strcspn(strNumber, "\n")] = '\0';
			if(strspn(strNumber, " \t") == strlen(strNumber)){
				printf("\nKhong duoc de trong!\n");
			} else {
				ds[*n].qty = atoi(strNumber);
				if(ds[*n].qty < 0){
					printf("\nPhai nhap so duong!\n");
				}			
				if(ds[*n].qty == 0){
					printf("\nPhai nhap vao la so!\n");			
				}
				if(ds[*n].qty > 0){
					break;
				}
			}
		}
		fflush(stdin);
		do {
			printf("Nhap trang thai (1: Con su dung, 0: Da het han): ");
            scanf("%d", &ds[*n].status);
			if(ds[*n].status != 1 && ds[*n].status != 0){
				printf("\nChi nhap duoc status 1 hoac 0.\n");
			} 
		} while (ds[*n].status != 1 && ds[*n].status != 0);
		(*n)++;
    }
    printf("\nDa them thanh cong vao danh sach\n");
}
int duplicateProduct(Product ds[], int n, char duplicate[]){
	for(int i = 0; i < n; i++){
		if(strcmp(ds[i].productId, duplicate)== 0 || 
		   strcmp(ds[i].name, duplicate)== 0){
			return 1;
		}
	}
	return 0;
}
void displayProduct(Product ds[], int n){
    printf("\n+----------+-----------------------+----------------+-----------------+----------------+\n");
    printf("|%-9s |%-22s |%-15s |%-16s |%-15s |\n", "Ma Hang", "Ten Hang Hoa", "Don Vi Hang Hoa", "So Luong Ton Kho", "Trang Thai");
    printf("+----------+-----------------------+----------------+-----------------+----------------+\n");
    for (int i = 0; i < n; i++){
        printf("|%-9s |%-22s |%-15s |%-16d |%-15s |\n",
			ds[i].productId, 
			ds[i].name, ds[i].unit, 
			ds[i].qty, ds[i].status == 1 ? "Con su dung" : "Het han");
    }
    printf("+----------+-----------------------+----------------+-----------------+----------------+\n");
}
void updateProduct(Product ds[], int n){ 
	char findId[10];
	int found = 0;
	char strNumber[10];

	fflush(stdin);
	do{
		printf("Nhap ma hang can tim: ");
	    fgets(findId, 10, stdin);
	    findId[strcspn(findId, "\n")] = '\0';
		if(strspn(findId, " \t") == strlen(findId)){
            printf("\nMang rong vui long nhap lai!\n");
		}
	} while (strspn(findId, " \t") == strlen(findId));

	for (int i = 0; i < n; i++) {
		if(strcmp(ds[i].productId, findId)== 0){
			do {
                printf("Nhap ten san pham moi: ");
                fgets(ds[i].name, 50, stdin);
                ds[i].name[strcspn(ds[i].name, "\n")] = '\0';
                if(strspn(ds[i].name, " \t") == strlen(ds[i].name)){
            	    printf("\nMang rong vui long nhap lai!\n");
            	    continue;
				}
	            if (duplicateProduct(ds, n, ds[i].name)){
	            	printf("\nTen da bi trung hay nhap lai!\n");
	            	continue;
				}
			} while(strspn(ds[i].name, " \t") == strlen(ds[i].name) || duplicateProduct(ds, n, ds[i].name));

			do {
				printf("Don vi hang hoa moi (Cai/KG/Hop): ");
				fgets(ds[i].unit, 10, stdin);
				ds[i].unit[strcspn(ds[i].unit, "\n")] = '\0';
				if (strlen(ds[i].unit) == 0) {
					printf("\nMang rong, vui long nhap lai!\n");
				}else if (strcmp(ds[i].unit, "Cai") != 0 &&
					strcmp(ds[i].unit, "KG")  != 0 &&
					strcmp(ds[i].unit, "Hop") != 0) 
				{
					printf("\nVui long nhap dung (Cai/KG/Hop)!\n");
				}

			} while (
				strlen(ds[i].unit) == 0 ||
				(strcmp(ds[i].unit, "Cai") != 0 &&
				strcmp(ds[i].unit, "KG")  != 0 &&
				strcmp(ds[i].unit, "Hop") != 0));

			while (1){
				printf("So luong ton kho: ");
				fgets(strNumber, 10, stdin);
				strNumber[strcspn(strNumber, "\n")] = '\0';
				if(strspn(strNumber, " \t") == strlen(strNumber)){
					printf("\nKhong duoc de trong!\n");
				} else {
					ds[i].qty = atoi(strNumber);
					if(ds[i].qty < 0){
						printf("\nPhai nhap so duong!\n");
					}			
					if(ds[i].qty == 0){
						printf("\nPhai nhap vao la so!\n");			
					}
					if(ds[i].qty > 0){
						break;
					}
				}
			}	
			printf("\nDa cap nhat thanh cong vao danh sach\n");
			found = 1;
		}
	}
	if(!found){
		printf("\nKhong tim thay san pham!\n");
	}
}
void searchProduct(Product ds[], int n){ 
	int found = 0;
	char search[50];

	fflush(stdin);
	do{
		printf("Nhap ten hoac ma can tim: ");
	    fgets(search, 50, stdin);
	    search[strcspn(search, "\n")] = '\0';
		if(strspn(search, " \t") == strlen(search)){
            printf("\nMang rong vui long nhap lai!\n");
		}
	} while (strspn(search, " \t") == strlen(search));
	for (int i = 0; i < n; i++) {
		if(strcmp(ds[i].name, search)== 0 || 
		strcmp(ds[i].productId, search)== 0) {
			printf("\n+--------------------------------------------------------------------------------------+\n");
			printf("|                                  THONG TIN SAN PHAM                                  |\n");
			printf("+----------+-----------------------+----------------+-----------------+----------------+\n");
			printf("|%-9s |%-22s |%-15s |%-16s |%-15s |\n", "Ma Hang", "Ten Hang Hoa", "Don Vi Hang Hoa", "So Luong Ton Kho", "Trang Thai");
			printf("+----------+-----------------------+----------------+-----------------+----------------+\n");
			printf("|%-9s |%-22s |%-15s |%-16d |%-15s |\n", 
				ds[i].productId, 
				ds[i].name, 
				ds[i].unit, 
				ds[i].qty, 
				ds[i].status == 1 ? "Con su dung" : "Het han");
			printf("+----------+-----------------------+----------------+-----------------+----------------+\n");
			found = 1;
		}
	}
	if(!found) {
		printf("\nKhong tim thay ten hoac ma hang!\n");
	}
}
void namesortProduct(Product ds[], int n){ 
	Product temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if(strcmp(ds[j].name,  ds[j + 1].name) > 0){
				temp = ds[j];
				ds[j] = ds[j + 1];
				ds[j + 1] = temp;
			}
		}
	}
    printf("\nDa sap xep danh sach theo ten!\n");
}
void qtysortProduct(Product ds[], int n){ 
	Product temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if(ds[j].qty > ds[j + 1].qty){
				temp = ds[j];
				ds[j] = ds[j + 1];
				ds[j + 1] = temp;
			}
		}
	}
    printf("\nDa sap xep danh sach theo so luong!\n");
}
void paginationProduct(Product ds[], int n){ 
	int totalPages = n / itemsPerPage + ((n % itemsPerPage == 0) ? 0 : 1);
	char choose;
	while (1){
		system("cls");
        int start = (page - 1) * itemsPerPage;
        int end   = page * itemsPerPage;
		printf("\n+--------------------------------------------------------------------------------------+\n");
		printf("|                                 DANH SACH PHAN TRANG                                 |\n");
		printf("+----------+-----------------------+----------------+-----------------+----------------+\n");
		printf("|%-9s |%-22s |%-15s |%-16s |%-15s |\n", "Ma Hang", "Ten Hang Hoa", "Don Vi Hang Hoa", "So Luong Ton Kho", "Trang Thai");
		printf("+----------+-----------------------+----------------+-----------------+----------------+\n");
        for(int i = start; i < end && i < n; i++){
			printf("|%-9s |%-22s |%-15s |%-16d |%-15s |\n", 
				ds[i].productId, 
				ds[i].name, 
				ds[i].unit, 
				ds[i].qty, 
				ds[i].status == 1 ? "Con su dung" : "Het han");
		}
		printf("+----------+-----------------------+----------------+-----------------+----------------+\n");

        fflush(stdin);
        printf("\nBan co muon chuyen trang khong (C/K)? ");
        choose = getchar();
        if(choose == 'k' || choose == 'K') {
			return;
		}
        if(choose == 'c' || choose == 'C') {
            int newPage;
            do {
                printf("Nhap trang (1 - %d trang): ", totalPages);
                scanf("%d", &newPage);
                if(newPage < 1 || newPage > totalPages){
                    printf("Trang khong hop le!\n");
				}
            } while(newPage < 1 || newPage > totalPages);
            page = newPage;
            getchar();
        } else {
            printf("Lua chon khong hop le!\n");
        }
	}
}
void deleteProduct(Product ds[], int *n){ 
	char findId[10];
	int flag = 0;
	
	getchar();
	do{
		printf("Nhap ma san pham can xoa: ");
		fgets(findId, 10, stdin);
		findId[strcspn(findId, "\n")] = '\0';
		if (strspn(findId, " \t") == strlen(findId)) {
            printf("\nMang rong vui long nhap lai!\n");
		}
	} while(strspn(findId, " \t") == strlen(findId));

	for (int i = 0; i < *n; i++) {
		if(strcmp(ds[i].productId, findId)== 0) {
			for (int j = i; j < *n - 1; j++) {
				ds[j] = ds[j + 1];
			}
			(*n)--;
			printf("\nDa xoa thanh cong ma hang.\n");
			flag = 1;
		}
	}
	if(!flag){
		printf("\nKhong tim thay ma hang.\n");
	}
}
void lockedProduct(Product ds[], int n){ 
	char findId[10];
	int flag = 0;
	
	getchar();
	do{
		printf("Nhap ma san pham can khoa: ");
		fgets(findId, 10, stdin);
		findId[strcspn(findId, "\n")] = '\0';
		if (strspn(findId, " \t") == strlen(findId)) {
            printf("\nMang rong vui long nhap lai!\n");
		}
	} while(strspn(findId, " \t") == strlen(findId));

	for (int i = 0; i < n; i++) {
		if(strcmp(ds[i].productId, findId)== 0) {
			do{
				printf("Nhap Status (1: unlocked, 0: locked): ");
				scanf("%d", &ds[i].status);
				if(ds[i].status != 1 && ds[i].status != 0){
					printf("\nChi duoc nhap 1 hoac 0.\n");
				}
			} while(ds[i].status != 1 && ds[i].status != 0);
			flag = 1;
		}
	}
	if(!flag){
		printf("\nKhong tim thay ma hang.\n");
	}
}
void importProduct(Product ds[], int n, Transaction logs[], int *logCount) { 
    char findId[10];
    int amount;
    int flag = 0;
	char strNumber[10];

	fflush(stdin);
    do {
        printf("Nhap ma san pham: ");
        fgets(findId, 10, stdin);
        findId[strcspn(findId, "\n")] = '\0';
        if (strspn(findId, " \t") == strlen(findId)) {
            printf("\nMang rong vui long nhap lai!\n");
        }
    } while(strspn(findId, " \t") == strlen(findId));

    for (int i = 0; i < n; i++) {
        if(strcmp(ds[i].productId, findId)== 0) {
			flag = 1;
            do {
                printf("Nhap loai giao dich (IN/OUT): ");
                fgets(logs[*logCount].type, 10, stdin);
                logs[*logCount].type[strcspn(logs[*logCount].type, "\n")] = '\0';

                if (strspn(logs[*logCount].type, " \t") == strlen(logs[*logCount].type)){
                    printf("\nMang rong vui long nhap lai!\n");
					continue;
                }
                if(strcmp(logs[*logCount].type, "IN") != 0 && 
				        strcmp(logs[*logCount].type, "OUT") != 0){
                    printf("\nChi duoc nhap IN hoac OUT!\n");
					continue;
				}
				if(strcmp(logs[*logCount].type, "OUT") == 0 && ds[i].status == 0){
					printf("\nKhong the xuat khi hang da het han.\n");
					continue;
				}
				break;
            } while(1);

			while (1){
				printf("Nhap so luong: ");
				fgets(strNumber, 10, stdin);
				strNumber[strcspn(strNumber, "\n")] = '\0';
				if(strspn(strNumber, " \t") == strlen(strNumber)){
					printf("\nKhong duoc de trong!\n");
				} else {
					amount = atoi(strNumber);
					if(amount < 0){
						printf("\nPhai nhap so duong!\n");
					}			
					if(amount == 0){
						printf("\nPhai nhap vao la so!\n");			
					}
					if(amount > 0){
						break;
					}
				}
			}
			do {
				printf("Nhap (Ngay Thang Nam): ");
				scanf("%d %d %d",
					&logs[*logCount].date.day,
				    &logs[*logCount].date.month,
				    &logs[*logCount].date.year);
			} while(confirmDateOrder
				(logs[*logCount].date.day, 
				logs[*logCount].date.month, 
				logs[*logCount].date.year)==0 );

            if(strcmp(logs[*logCount].type, "IN")==0){
                ds[i].qty += amount;
                printf("Nhap hang thanh cong!\n");
            } else if(strcmp(logs[*logCount].type, "OUT")==0){
                if(amount > ds[i].qty){
                    printf("So luong xuat lon hon so luong ton kho!\n");
                    return;
                }
                ds[i].qty -= amount;
                printf("Xuat hang thanh cong!\n");
            }
            sprintf(logs[*logCount].transId, "GD%03d", *logCount + 1);
            strcpy(logs[*logCount].productId, ds[i].productId);
            logs[*logCount].amount = amount;
            
            (*logCount)++;
            return;
        }
    }
    if(!flag){
        printf("\nKhong tim thay ma hang.\n");
    }
}
int confirmDateOrder(int day, int month, int year){ 
    int success = 1;
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        if(day < 1 || day > 31){
			success = 0;
		}
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11){
        if(day < 1 || day > 30){
			success = 0;
		}
    }
    else if(month == 2){
        if((year %4 == 0 && year %100 != 0) || year % 400 == 0){
            if(day < 1 || day > 29) success=0;
        } else {
            if(day < 1 || day > 28) success=0;
        }
    } else{
		success = 0;
	}
    if(year < 1900 || year > 2025){
		success = 0;
	}
    if(!success){
		printf("\nNgay thang nam khong hop le! Nhap lai.\n");
    }
	return success;
}
void showHistory(Product ds[], Transaction logs[], int logCount){ 
    int found = 0;
    char search[50];

	fflush(stdin);
    do{
        printf("Nhap ma san pham can xem lich su: ");
        fgets(search, 50, stdin);
        search[strcspn(search, "\n")] = '\0';
        if(strspn(search, " \t") == strlen(search)){
            printf("\nMang rong vui long nhap lai!\n");
        }
    } while (strspn(search, " \t") == strlen(search));
	for (int i = 0; i < logCount; i++) {
		if(strcmp(logs[i].productId, search)== 0) {
				printf("\n+---------------------------------------------------------------------+\n");
				printf("|                      LICH SU GIAO DICH SAN PHAM                     |\n");
				printf("+----------------+-----------------------+-----------------+----------+\n");
				printf("|%-15s |%-22s |%-16s |%-9s |\n","Ma Giao Dich", "Trang Thai", "Ngay/Thang/Nam", "So Luong");
				printf("+----------------+-----------------------+-----------------+----------+\n");
				printf("|%-15s |%-22s |%02d/%02d/%04d       |%-9d |\n",
					logs[i].transId,
					strcmp(logs[i].type, "IN") == 0 ? "Nhap Vao" : "Xuat Ra",
					logs[i].date.day,
					logs[i].date.month,
					logs[i].date.year,
					logs[i].amount);
				printf("+----------------+-----------------------+-----------------+----------+\n");
			found = 1;
		}
	}
    if(!found) {
        printf("\nKhong co giao dich nao cho san pham nay!\n");
    }
}
