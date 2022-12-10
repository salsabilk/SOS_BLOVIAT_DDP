#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct {
	char nama[100];
	int skor;
	int giliran;
}Pemain;

void menuAwal(); //Menu di awal permainan untuk memilih apakah ingin main atau cara bermain, atau keluar
void skuy_main();
void display_tutor(); //Modul untuk menampilkan cara dan aturan bermain SOS
void display_udahan(); //Modul untuk menampilkan keluar jika pemain memilih untuk keluar permainan
void pilih_papan(); //Modul untuk memilih papan
void gambar_papan(); //Modul untuk membuat dan menampilkan papan permainan
void board_space();
int cek_papan(); //Modul untuk mengecek apakah papan sudah terisi penuh atau belum
void point_sos(); 
void papan_skor(); //Modul untuk menampilkan score permainan
void gotoxy(int x, int y);
void tampilan_akhir();


// Modul Waktu Bermain
int waktu_awal();
int waktu_akhir();

//Modul Bermain Player VS Player
void display_nama(Pemain player1, Pemain player2); //Modul untuk menginputkan nama player 1 dan player 2
int input_sos(); //Modul untuk menginputkan huruf S atau O ke papan
int cari_sos(); //Modul untuk mencari hasil SOS dari sebuah papan permainan

int pemainMain = 0; 

typedef struct {
	char petak[7][7];
}Papan;

typedef struct {
	Pemain player1, player2;
	Pemain winner;
	Papan ppn;
}Game;

/*VARIABEL GLOBAL*/
int opsi;
int ukuran;
int pilihanPapan; 
char papan[15][15]; 
int pilMenu;
int opsi_tutor;
int opsi_udahan;
int baris, kolom; // untuk menyimpan baris dan kolom yang dipilih pemain
int poin[3] = {0,0};
//int pemainMain = 0; // untuk menampilkan nama pemain yang diinputkan
int counter;
Pemain player1, player2;

int main(){
	menuAwal();
	do{
		switch(opsi){
   			case 1:
   				skuy_main();
   				break;
        	case 2:
   				display_tutor();
   				switch(opsi_tutor){
				default:
	      		menuAwal();
	      			break;
				}
   				break;
			case 3:
   				display_udahan();	
   				switch(opsi_udahan){
   				case 1:	
   				menuAwal();
   					break;
   				default:
   				return 0;
   					break;
				}
   				break;	
	   		 default:
   			 	printf("\t\t\t\t PILIHANMU TIDAK TEPAT, Klik Enter Untuk Mengulang!");
      		 	getch();
      		 	menuAwal();
			}
	} while (opsi != 1 || opsi != 2 || opsi != 3);

	switch(ukuran){
		case 1:
			pilihanPapan = 3;
			break;
		case 2:
			pilihanPapan = 5;
			break;
		case 3:
			pilihanPapan = 7;
			break;
//		 default:
//		 	printf("\t\t\t\t PILIHANMU TIDAK TEPAT, COBA MASUKAN KEMBALI!!!");
//      	 	system("pause");
//      	 	pilih_papan();
	}
	
	
	
	return 0;
}

void menuAwal(){
	system("cls");
	system("color E0");
	printf("\n\n\n\n\n\n");
	printf("\t\t _____________________________________________________________________________________   \n");
	printf("\t\t\xb3\t\t\t\t\t WELCOME TO                                   \xb3\n");
	printf("\t\t\xb3\t\t\t                                                              \xb3\n");
	printf("\t\t\xb3\t\t\t  **********     *********     **********                     \xb3\n");
	printf("\t\t\xb3\t\t\t  **            **       **    **                             \xb3\n");
	printf("\t\t\xb3\t\t\t  **            **       **    **                             \xb3\n");
	printf("\t\t\xb3\t\t\t  **********    **       **    **********                     \xb3\n");
	printf("\t\t\xb3\t\t\t          **    **       **            **                     \xb3\n");
	printf("\t\t\xb3\t\t\t          **    **       **            **                     \xb3\n");
	printf("\t\t\xb3\t\t\t  **********     *********     **********                     \xb3\n");
    printf("\t\t\xb3                                                                                     \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n");
	printf("\t\t\xb3\t\t\t\t\t                                              \xb3\n");
    printf("\t\t\xb3    [1] MAIN                                                                         \xb3\n");
    printf("\t\t\xb3    [2] TUTOR?                                                                       \xb3\n");
    printf("\t\t\xb3    [3] UDAHAN                                                    CREATED BY BLOVIAT \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n\n");
	printf("\t\t MAU APA? "); scanf("%d",&opsi);
	
}

void skuy_main(){
	Pemain player1, player2;
	display_nama(player1, player2);
	pilih_papan();
	board_space();
	while (!cek_papan()) {
		system("cls");
		baris = 0; kolom = 0;
		papan_skor();
		gambar_papan();
		
		int input = input_sos();
		if (input){
			int point = cari_sos();
			if(!point) {
				printf("Yahhh Kamu belum dapat point :(.");
				getch();
				pemainMain = (pemainMain + 1) %2;
			}
			else {
				poin[pemainMain] = poin[pemainMain] + 1;
				printf("Yeayy Kamu dapat 1 point. Yuk main lagi");
				getch();
			}
			counter++;
		}
	}
	tampilan_akhir();
}

void display_nama(Pemain player1, Pemain player2) {
	system("cls");
	system("color E0");
	printf("\n\n\n\n\n\n");
	printf("\t\t _____________________________________________________________________________________   \n");
	printf("\t\t\xb3\t\t\t                                                              \xb3\n");
	printf("\t\t\xb3\t\t\t                                                              \xb3\n");
	printf("\t\t\xb3\t      ****      **       ***       **            **       ***                 \xb3\n");
	printf("\t\t\xb3\t      ** **     **      ** **      ***          ***      ** **                \xb3\n");
	printf("\t\t\xb3\t      **  **    **     **   **     ** *        * **     **   **               \xb3\n");
	printf("\t\t\xb3\t      **   **   **    **     **    **  *      *  **    **     **              \xb3\n");
	printf("\t\t\xb3\t      **    **  **   ***********   **   *    *   **   ***********             \xb3\n");
	printf("\t\t\xb3\t      **     ** **  **         **  **    *  *    **  **         **            \xb3\n");
	printf("\t\t\xb3\t      **      **** **           ** **     **     ** **           **           \xb3\n");
    printf("\t\t\xb3                                                                                     \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n\n");
    printf("\t\t     Player 1 :"); scanf("%s", &player1); 
    printf("\t\t     Player 2 :"); scanf("%s", &player2); 
}

void display_tutor(){
	opsi=0;
	system("cls");
	system("color E0");
	printf("\n\n\n\n\n\n");
	printf("\t\t _____________________________________________________________________________________   \n");
	printf("\t\t\xb3\t\t\t                                                              \xb3\n");
	printf("\t\t\xb3 Tata Cara dan Aturan Main :                                                         \xb3\n");
	printf("\t\t\xb3 1.Setelah masuk ke menu bermain, permainan akan dimulai dengan langkah player 1     \xb3\n");
	printf("\t\t\xb3   sebagai giliran pertama.                                                          \xb3\n");
	printf("\t\t\xb3 2.Player 1 akan diminta untuk memasukkan baris dan kolom untuk mengisi huruf 'S'    \xb3\n");
	printf("\t\t\xb3   atau 'O' pada papan.                                                              \xb3\n");
	printf("\t\t\xb3 3.Waktu yang diberikan untuk mengisi huruf 'S'/'O' untuk setiap player yaitu 15     \xb3\n");
	printf("\t\t\xb3   detik.                                                                            \xb3\n");
	printf("\t\t\xb3 4.Jika player melewati batas waktu yang telah ditentukan, maka giliran akan hangus  \xb3\n");
    printf("\t\t\xb3   hangus dan giliran bermain akan beralih ke pemain lawan.                          \xb3\n");
    printf("\t\t\xb3 5.Pemain akan mendapatkan satu poin jika berhasil merangkai kata 'SOS' baik secara  \xb3\n");
    printf("\t\t\xb3   vertikal, horizontal, maupun diagonal.                                            \xb3\n");
    printf("\t\t\xb3 6.Setelah papan terisi penuh, maka pemenang dapat ditentukan berdasarkan peraih     \xb3\n");
    printf("\t\t\xb3   skor tertinggi.                                                                   \xb3\n");
    printf("\t\t\xb3 7.Jika skor kedua player sama, maka permainan akan dinyatakan seri.                 \xb3\n");
    printf("\t\t\xb3\t\t\t                                                              \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n\n");
    printf("\t\t Pilih angka berapa saja dan enter untuk kembali ke menu awal :");		scanf("%d", &opsi_tutor);
}

void display_udahan(){
	system("cls");
	system("color E0");
	printf("\n\n\n\n\n\n");
	printf("\t\t _____________________________________________________________________________________   \n");
	printf("\t\t\xb3\t\t\t\t\t                                              \xb3\n");
	printf("\t\t\xb3\t      *     *       ***       *    *  ***  ***      **   ********             \xb3\n");
	printf("\t\t\xb3\t       *   *       ** **      *   *    *   ** *     **          *             \xb3\n");
	printf("\t\t\xb3\t        * *       **   **     *  *     *   **  *    **          *             \xb3\n");
	printf("\t\t\xb3\t         *       **     **    ***      *   **   *   **     ******             \xb3\n");
	printf("\t\t\xb3\t         *      ***********   *  *     *   **    *  **     *                  \xb3\n");
	printf("\t\t\xb3\t         *     **         **  *   *    *   **     * **     *                  \xb3\n");
	printf("\t\t\xb3\t         *    **           ** *    *  ***  **      ***     @                  \xb3\n");
	printf("\t\t\xb3\t\t\t\t\t                                              \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n");
    printf("\t\t\xb3\t\t\t\t\t                                              \xb3\n");
    printf("\t\t\xb3    [1] GA JADI DEH                                                                  \xb3\n");
    printf("\t\t\xb3    [2] YAKIN                                                                        \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n\n");
  	printf("\t\t MAU APA? :"); scanf("%d", &opsi_udahan);
}

void tampilan_akhir(){
	system("cls");
	system("color E0");
	int opsi;
}

void pilih_papan(){
	system("cls");
	system("color E0");
	printf("\n\n\n\n\n\n");
	printf("\t\t _____________________________________________________________________________________   \n");
	printf("\t\t\xb3\t\t\t\t\t                                              \xb3\n");
	printf("\t\t\xb3\t          ***       ********  ********  ***      **       ***                 \xb3\n");
	printf("\t\t\xb3\t         ** **      *      *  *         ** *     **      ** **                \xb3\n");
	printf("\t\t\xb3\t        **   **     *      *  *         **  *    **     **   **               \xb3\n");
	printf("\t\t\xb3\t       **     **    ********  ********  **   *   **    **     **              \xb3\n");
	printf("\t\t\xb3\t      ***********   *    *    *         **    *  **   ***********             \xb3\n");
	printf("\t\t\xb3\t     **         **  *     *   *         **     * **  **         **            \xb3\n");
	printf("\t\t\xb3\t    **           ** *      *  ********  **      *** **           **           \xb3\n");
    printf("\t\t\xb3                                                                                     \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n");
	printf("\t\t\xb3\t\t\t\t\t                                              \xb3\n");
    printf("\t\t\xb3    [1] 3 x 3                                                                        \xb3\n");
    printf("\t\t\xb3    [2] 5 x 5                                                                        \xb3\n");
    printf("\t\t\xb3    [3] 7 x 7                                                                        \xb3\n");
    printf("\t\t\xb3_____________________________________________________________________________________\xb3\n\n");
    printf("\t\t Masukkan Pilihanmu: "); scanf("%d",&ukuran);
//    switch(ukuran){
//		case 1:
//			pilihanPapan = 3;
//			break;
//		case 2:
//			pilihanPapan = 5;
//			break;
//		case 3:
//			pilihanPapan = 7;
//			break;
////		 default:
////		 	printf("\t\t\t\t PILIHANMU TIDAK TEPAT, COBA MASUKAN KEMBALI!!!");
////      	 	system("pause");
////      	 	pilih_papan();
//		}
}

void board_space(){
	for (int i = 0; i < pilihanPapan; i++){
		for (int j = 0; j < pilihanPapan; j++){
			papan[i][j] = ' ';
		}
	}
}

int cek_papan(){
	for( baris = 0; baris < pilihanPapan; baris++){
		for( kolom = 0; kolom < pilihanPapan; kolom++ ){
			if (papan[baris][kolom == ' ']){
				return 0;
			}
		}
	}
	return 1;
}

void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int waktu_awal(){
	clock_t time;
	time = clock();
	return time;
}

int waktu_akhir(){
	clock_t time;
	time = clock();
	return time;
}

void papan_skor() {
	gotoxy(0,0);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,194,196,194,196,196,196,196,196,196,196,196,196,191);
	printf("\n\xb3        \xb3:\xb3         \xb3\n");
	printf("\xb3        \xb3:\xb3         \xb3");
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,193,196,193,196,196,196,196,196,196,196,196,196,217);
	gotoxy(2,1); printf("%s\n", player1.nama);
	gotoxy(13,1); printf("%s\n", player2.nama);
	gotoxy(2,2); printf("%s\n", poin[0]);
	gotoxy(13,2); printf("%s\n", poin[1]);
}

void gambar_papan(){
	system ("color E0");
	int i, j;
	printf("\n   ");
	for (i = 0; i <= pilihanPapan; i++) {
		printf("\n   ");
		for (j = 0; j <= pilihanPapan; j++) {
			if (!i && !j) printf("      ");
			else if (!i && j == pilihanPapan) printf("   %2d  ", j);
			else if (!i) printf("  %2d  ", j);
			else if (!j) printf("  %2d  \xb3", i);
			else if (baris && kolom && baris == i && kolom == j) printf("     \xb3");
			else printf("  %c  \xb3", papan[i - 1][j - 1]);
		}
		printf("   \n   ");
		for (j = 0; j <= pilihanPapan; j++) {
			if (i == pilihanPapan && !j) printf("      ");
			else if (i == pilihanPapan) printf("\xc1\xcd\xcd\xcd\xcd\xcd");
			else if (!j) printf("      ");
			else printf("\xc5\xcd\xcd\xcd\xcd\xcd");
			if (i == pilihanPapan && j == pilihanPapan) printf("\xd9");
			else if (j == pilihanPapan) printf("\xb4");
		}
	}
	printf("\n");
}

int input_sos(){
	int waktu;
	double waktuIsi;
	waktu = waktu_awal();
	
	do{
		fflush(stdin);
		printf("\n\n\xdb Baris: ");
		scanf("%d", &baris);
		printf("\n\n\xdb Kolom: ");
		scanf("%d", &kolom);
		printf("\n INPUT POSISI TIDAK VALID! \n \xaf TEKAN ENTER UNTUK MELANJUTKAN!");
	}while(!(baris > 0 && baris <= pilihanPapan && kolom > 0 && kolom <= pilihanPapan));
	
	system("cls");
	switch (papan[baris - 1][kolom -1]) {
		case 'S':
		case 'O': printf("\xaf\xaf POSISI SUDAH DIISI !!!\n\xaf\xaf TEKAN ENTER UNTUK MELANJUTKAN!");
			getch();
			return 0;
			default:
			system("cls");
			papan_skor();
			gambar_papan();
			waktu = waktu_akhir()-waktu;
			waktuIsi = ((double)waktu)/CLOCKS_PER_SEC;
			if (waktuIsi<=15){
				printf("\n\n\xc Giliran : %s\n\xdb Baris: %d\n\xdb Kolom: %d\n\xaf\xaf S/O? ", player1, baris, kolom);
				char ch;
				scanf(" %c", &ch);
				switch (ch) {
					case 's':
					case 'S': papan[baris - 1][kolom - 1] = 'S'; return 1;
					case 'o':
					case 'O': papan[baris - 1][kolom - 1] = 'O'; return 1;
				}
				printf("\xaf\xaf Invalid letter!!\n\xaf\xaf Press any key to continue!!");
				getch();
				return 0;
			}
			else{
				papan_skor();
				gambar_papan();
				printf("\n Waktu Habis, Giliran Anda Hangus!");
				pemainMain = (pemainMain + 1) % 2;
				getch();
				return 0;
			}
	}
}

int cari_sos(){
	if (papan[baris - 1][kolom - 1] == 'S') {
		if (papan[baris - 3][kolom - 3] == 'S' && papan[baris - 2][kolom - 2] == 'O') return 1;
		if (papan[baris - 3][kolom - 1] == 'S' && papan[baris - 2][kolom - 1] == 'O') return 1;
		if (papan[baris - 3][kolom + 1] == 'S' && papan[baris - 2][kolom] == 'O') return 1;
		if (papan[baris - 1][kolom - 3] == 'S' && papan[baris - 1][kolom - 2] == 'O') return 1;
		if (papan[baris - 1][kolom + 1] == 'S' && papan[baris - 1][kolom] == 'O') return 1;
		if (papan[baris + 1][kolom - 3] == 'S' && papan[baris][kolom - 2] == 'O') return 1;
		if (papan[baris + 1][kolom - 1] == 'S' && papan[baris][kolom - 1] == 'O') return 1;
		if (papan[baris + 1][kolom + 1] == 'S' && papan[baris][kolom] == 'O') return 1;
	}
	else {
		if (papan[baris - 2][kolom - 2] == 'S' && papan[baris][kolom] == 'S') return 1;
		if (papan[baris - 2][kolom - 1] == 'S' && papan[baris][kolom - 1] == 'S') return 1;
		if (papan[baris - 2][kolom] == 'S' && papan[baris][kolom - 2] == 'S') return 1;
		if (papan[baris - 1][kolom - 2] == 'S' && papan[baris - 1][kolom] == 'S') return 1;
	}
	return 0;
}


