#include <stdio.h> //library dasar untuk bahasa C
#include <time.h> //library untuk waktu dan tanggal
#include <stdlib.h> //library untuk exit
#include <string.h> //library untuk string ataupun substring (strcmp, strcpy, dll)

//UNTUK PEMBAYARAN NON TUNAI BELUM BISA
//TAMBAHKAN PENGECEKAN UNTUK PLAT NOMOR DARI DAERAH MANA SESUAI DENGAN YANG DIINPUTKAN

struct data { //struct untuk data parkir
	int jenis;
	char plat[20];
};


//untuk waktu agar dapat mengambil waktu lokal
time_t t;
struct tm *tm;
time_t now;
time_t masuk;
time_t keluar;
    
//variabel global
char kendaraan[25];
float roda2 = 4.000; 
float roda4 = 10.000;
float roda6 = 15.000;
float premium = 30.000;
FILE *Data;
FILE *Copy;


int menu(); //fungsi untuk menampilkan menu awal
void kedalam(); //prosedur untuk pilihan pertama inputan ketika kendaraan masuk parkir
int cekdatasama(); //fungsi untuk memvalidasi kendaraan yang akan masuk parkir
void meninggalkan(); //prosedur untuk pilihan kedua ketika kendaraan akan meninggalkan parkir
int pembayaran(); //fungsi untuk pembayaran saat keluar parkir 
void cekparkir(); //prosedur untuk mengecek kendaraan yang ada di dalam parkir
int cekkeluar(); //fungsi untuk mengecek kendaraan yang keluar parkir
int validasi(); //fungsi untuk memvalidasi inputan yang akan dimasukan pada pemilihan menu


int main () {
	
	while (1) {
	switch (menu()){
		case 1 : 
			system("cls");
			kedalam();
			system("pause");
			system("cls");
			break;
		case 2 : 
			system("cls");
			meninggalkan();
			system("pause");
			system("cls");
			break;
		case 3 :
			system("cls");
			cekparkir();
			system("pause");
			system("cls");
			break;
		case 4 :
			system("cls");
			cekkeluar();
			system("pause");
			system("cls");
			break;
		case 5 :
			system("cls");
			printf ("TERIMAKASIHHH");
			exit(0);
		default :
			system("cls");
			printf("MENU YANG ADA INPTUKAN TIDAK TERSEDIA \nSILAHKAN PILIH MENU YANG TERSEDIA \n\n");
            system("pause");
            system("cls");
		}
	}
}


int menu () { //fungsi untuk menampilkan menu awal
	int pilih;
	
	printf("+-----------------------------------------------------+\n");
	printf("|                   PARKIR KENDARAAN                  |\n");
	printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
	printf("+-----------------------------------------------------+\n");
	printf("| MENU :                                              |\n");
	printf("|     1. Masuk Parkir                                 |\n");
	printf("|     2. Keluar Parkir                                |\n");
	printf("|     3. Cek Dalam Parkir                             |\n");
	printf("|     4. Data Keluar Parkir                           |\n");
	printf("|     5. EXIT                                         |\n");
	printf("+-----------------------------------------------------+\n");
	printf("Masukan Menu : "); pilih = validasi();
	
	return pilih;
}

int validasi () { //fungsi validasi untuk pilihan menu
	 int angka;
	char karakter;
	if (scanf("%d%c", &angka, &karakter) !=2 || angka < 1 || angka > 5 || karakter != '\n'){
		fflush(stdin);
		printf("MENU YANG ADA INPTUKAN TIDAK TERSEDIA \n SILAHKAN PILIH MENU YANG TERSEDIA");
		return validasi;
	} else {
		return angka;
	}
}



void kedalam () { //prosedur untuk menu pertama saat kendaraan masuk parkir
	struct data parkir; //pemanggilan struct data
	t = time(NULL);
    tm = localtime(&t);
    now = time(NULL);
	
	printf("+-----------------------------------------------------+\n");
	printf("|                  JENIS KENDARAAN                    |\n");
	printf("+-----------------------------------------------------+\n");
	printf("|     1. Kendaraan R2                                 |\n");
	printf("|     2. Kendaraan R4                                 |\n");
	printf("|     3. Kendaraan R6                                 |\n");
	printf("|     4. Premium Kendaraan R4                         |\n");
	printf("+-----------------------------------------------------+\n");
	printf("Masukan Jenis Kendaraan : ");
	scanf("%d", &parkir.jenis);
	
	//untuk mengubah tipe data dari jenis kendaraan yang awalnya integer menjadi string
	if (parkir.jenis == 1) {  
		strcpy(kendaraan, "Kendaraan R2");
	}
	else if (parkir.jenis == 2) {
		strcpy(kendaraan, "Kendaraan R4");
	}
	else if (parkir.jenis == 3) {
		strcpy(kendaraan, "Kendaraan R6");
	}
	else if (parkir.jenis == 4) {
		strcpy(kendaraan, "Premium Kendaraan R4");
	}
	
//	system ("cls");
	
	printf("Plat Nomor Kendaraan : ");
	fflush(stdin);
	scanf("%[^\n]", &parkir.plat);
	
	system("cls");
	
	
	Data = fopen("masuk.txt", "a"); //perintah untuk memasukan data ke dalam file external txt
	fprintf(Data, "%s, %s, %d-%d-%d, %d:%d \n", kendaraan, parkir.plat, tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900, time(&masuk)); 
	//jika waktu digunakan seperti awal (time_t(&masuk) maka waktu akan di convert ketika masuk file, sedangkan jika begini waktu mau menyesuaikan tetapi tidak bisa dijumlahkan dengan cara difftime

	masuk = time(&masuk); //untuk jam masuk
    printf("Kendaraan Masuk Dalam Parkiran \n"); //data yang di print pada terminal (interface)
    	printf("+-----------------------------------------------------+\n");
		printf("|                    PARKIR KENDARAAN                 |\n");
		printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
		printf("+-----------------------------------------------------+\n");
		printf("| Jenis Kendaraan    : %s \n", kendaraan);
		printf("| Plat Nomor         : %s \n", parkir.plat);
		printf("| Tanggal            : %d-%d-%d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
		printf("| Jam Masuk          : %d:%d \n", localtime(&masuk)->tm_hour, localtime(&masuk)->tm_min);
		printf("+-----------------------------------------------------+\n");
    
    
    	//pembagian plat berdasarkan daerah
    	if (strncmp(parkir.plat, "DK", 2) == 0 ) {
		printf("Asal Kendaraan Ini dari Daerah Bali \n\n");
		}
		else if (strncmp(parkir.plat, "B", 1) == 0) {
		printf("Asal Kendaraan Ini dari Daerah DKI Jakarta \n\n");
		}
		else if (strncmp(parkir.plat, "AA, AD", 2) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Jawa Tengah \n\n");
		} 
		else if (strncmp(parkir.plat, "A", 1) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Banten \n\n");
		}
		else if (strncmp(parkir.plat, "D, E, F, Z", 1) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Jawa Barat \n\n");
		}
		else if (strncmp(parkir.plat, "L, M, N, P, S, W", 1) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Jawa Timur \n\n");
		}
		else if (strncmp(parkir.plat, "KB, DA, KH, KT, KU", 2) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Kalimantan \n\n");
		}
		else if (strncmp(parkir.plat, "DB, DL, DM, DN, DT, DD, DC", 2) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Sulawesi \n\n");
		}
		else if (strncmp(parkir.plat, "PA, PB", 2) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Papua \n\n");
		}
		else if (strncmp(parkir.plat, "DE, DG", 2) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Maluku \n\n");
		}
		else if (strncmp(parkir.plat, "BL, BB, BK, BA, BM, BH, BD, BP, BG, BN, BE", 2) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Sumatra \n\n");
		}
		else if (strncmp(parkir.plat, "DR, EA, DH, EB, ED", 2) == 0) {
		printf("Asal Kendaraan Ini dari Daerah Nusa Tenggara \n\n");
		}
		else {
		printf("Plat Kendaraan Belum Terdaftar \n\n");
		}
	
    fclose(Data);
}

void meninggalkan() { //prosedur untuk menu kedua saat kendaraan keluar parkir
	struct data parkir;
	int read;
	char plat[20];
	char kendaraanfile[20];
	char tanggal[20];
	char masuk[20];
    t = time(NULL);
    tm = localtime(&t);
	float biaya, progresif, jam;
	double lama;
	float bayar, kembalian;
//	keluar = time(&keluar);
	
	printf("+-----------------------------------------------------+\n");
	printf("|                  JENIS KENDARAAN                    |\n");
	printf("+-----------------------------------------------------+\n");
	printf("|     1. Kendaraan R2                                 |\n");
	printf("|     2. Kendaraan R4                                 |\n");
	printf("|     3. Kendaraan R6                                 |\n");
	printf("|     4. Premium Kendaraan R4                         |\n");
	printf("+-----------------------------------------------------+\n");
	printf("Masukan Jenis Kendaraan : "); //parkir.jenis = validasijenis();
	scanf("%d", &parkir.jenis);
	
	
	//untuk pencarian data kendaraan yang akan keluar parkir
	printf("Plat Nomor Kendaraan : ");
	fflush(stdin);
	scanf("%[^\n]", parkir.plat);
	getchar();
	system ("cls");
	

//pengambilan data diambil dari plat nomornya, untuk di struk data terakhir. 
	Data = fopen("masuk.txt", "r");
	if (Data == NULL) {
		printf ("DATA KENDARAAN SAAT MASUK ANDA TIDAK DITEMUKAN \n SILAHKAN MASUK TERLEBIH DAHULU");
		kedalam();
	}
	else {
		do{
			read = fscanf(Data,"%20[^,], %20[^,], %20[^,], %20[^\n]\n", kendaraanfile, plat, tanggal, masuk);
			if (read == 4){
				if(strcmp(parkir.plat, plat) == 0){
					printf("+-----------------------------------------------------+\n");
					printf("|                 NOTA PARKIR KENDARAAN               |\n");
					printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
					printf("+-----------------------------------------------------+\n");
					printf("| Jenis Kendaraan    : %s \n", kendaraanfile);                  
					printf("| Plat Nomor         : %s \n", plat);
					printf("| Tanggal            : %s \n", tanggal);
//					printf("| Jam Masuk          : %s \n", masuk);
//					printf("| Jam Keluar         : %d:%d \n", localtime(&keluar)->tm_hour, localtime(&keluar)->tm_min);
					//proses penghitungan biaya parkir
					if (parkir.jenis == 1) {
						lama = difftime(keluar, masuk) / 3600;
							if (lama <= 12 ) {
	       						biaya = roda2;
	   						} 
							else if (lama > 12 ) {
	       						jam = lama - 12; 
	       						progresif = 2.000 * jam;
	       						biaya = roda2 + progresif;
							} 
							else {
		   						printf ("Denda Karcis Hilang Rp. 50.000");
							}
					}
					else if (parkir.jenis == 2) {
						lama = difftime(keluar, masuk) / 3600;
							if (lama <= 1 ) {
						       biaya = roda4;
						   } 
							else if (lama > 1 ) {
							       jam = lama - 1; 
							       progresif = 5.000 * jam;
							       biaya = roda4 + progresif;
							} 
							else {
							   printf ("Denda Karcis Hilang Rp. 100.000");
							}
					}
					else if (parkir.jenis == 3) {
						lama = difftime(keluar, masuk) / 3600;
						if (lama <= 1) {
							biaya = roda6;
						}
						else if (lama > 1) {
							jam = lama - 1;
							progresif = 5.000 * jam;
							biaya = roda4 + progresif;
						}
						else {
							printf ("Denda Karcis Hilang Rp. 100.000");
						}
					}
					else if (parkir.jenis == 4) {
							lama = difftime(keluar, masuk) / 3600;
						if (lama <= 1) {
							biaya = roda4 + premium;
						}
						else if (lama > 1) {
							jam = lama - 1;
							progresif = 5.000 * jam;
							biaya = roda4 + progresif + premium;
						}
						else {
							printf ("Denda Karcis Hilang Rp. 100.000");
						}
					}						
//					printf("| Lama Parkir        : %.2f jam\n", lama);
					printf("| Biaya Parkir       : Rp. %0.3f \n", biaya);
				
					printf("+-----------------------------------------------------+\n");
					printf("|-------- HANYA MENERIMA PEMBAYARAN CASH SAJA --------|\n");
					printf("+-----------------------------------------------------+\n");
					printf("|Dibayar Sebesar \t\t Rp. ");
					scanf("%f", &bayar);
					kembalian = bayar - biaya;
					printf("|Kembalian \t\t\t Rp. %0.3f \n", kembalian);
					printf("+-----------------------------------------------------+\n");
					printf("|           TERIMA KASIH ATAS KUNJUNGAN ANDA          |\n");
					printf("+-----------------------------------------------------+\n");
				} 
			}
		}while(!feof(Data));
	} 
	fclose(Data);
	
	Data = fopen("masuk.txt", "r+");
	Copy = fopen("keluar.txt", "a+"); 
	
	//menambahkan do while dan scanf seperti saat menampilkan nota
	//mau manambahkan data ke file txt tapi ngga mau nambah file baru malah overwrite ke file sebelumnya dan ngebuat data lain malah ke hapus
	do {
		read = fscanf(Data,"%20[^,], %20[^,], %20[^,], %20[^\n]\n", kendaraanfile, plat, tanggal, masuk);
		if (read == 4){
			if(strcmp(parkir.plat, plat) == 0){
				fprintf(Copy, "%s, %s \n", kendaraanfile, plat);
			}
		}
	} while(!feof(Data)); //jika diganti (!feof(Copy)) maka tidak mau dijalankan
	

	fclose(Data);
	fclose(Copy);
	
	//masih bermasalah, masih overwrite ketumpuk nama filenya
	remove("masuk.txt");
	rename("masuk.txt", "keluar.txt");
	
}

void cekparkir() {
	int areaparkir;
	int repeat=1;
	char buff[255];
	char jenis_kendaraan[30];
	int jenis_sama;
	int total=0;
	char jenisR4[30] = "Kendaraan R4";
	char jenisR2[30] = "Kendaraan R2";
	char jenisR6[30] = "Kendaraan R6";
	char jenisR4PRE[30] = "Kendaraan R4 PRE";
	
	
	
	printf("+-----------------------------------------------------------------------------------------------+\n");
	printf("|                ||===================================================||                        |\n");
    printf("|                ||                PARKIR KENDARAAN                   ||                        |\n");
    printf("|                ||              BANDARA INTERNASIONAL                ||                        |\n");
    printf("|                ||               I GUSTI NGURAH RAI                  ||                        |\n");
    printf("|                ||===================================================||                        |\n");
    printf("|                                                                                               |\n");
    printf("+----+-----------------------------------+------------------------------------------------------|\n");
    printf("| No |     AREA PARKIR                   | Catatan :                                            |\n");
    printf("+----+-----------------------------------+                                                      |\n");
    printf("|  1 | Gedung Parkir Bertingkat          |==> PARKIR KENDARAAN RODA 4 (MOBIL,dsb)               |\n");
    printf("|  2 | Parkir Kendaraan Bermotor Roda 2  |==> PARKIR KENDARAAN KHUSUS SEPEDA MOTOR RODA 2       |\n");
    printf("|  3 | Area Parkir Bus                   |==> PARKIR KHUSUS BUS /TRUK                           |\n");
    printf("|  4 | Area Parkir Premium               |==> PARKIR KHUSUS RODA 4                              |\n");
    printf("+----+-----------------------------------+------------------------------------------------------+\n");
		    
do{
    	printf("\n\t\t Pilih Area Parkir : ");
	    scanf("%d", &areaparkir);
	    switch (areaparkir){
			case 1 : 
					Data = fopen("coba.txt", "r"); //memperlihatkan total kendaraan di areaparkir lewat data txt
				while(fgets(buff, sizeof(buff), Data)){
					strcpy(jenis_kendaraan, strtok(buff, ","));
 
				jenis_sama = strcmp(jenis_kendaraan, jenisR4);
				if (jenis_sama == 0 ){
					total++;
				} 
			}
				fclose(Data);
				printf ("Total %s = %d \n", jenisR4,total );
							break;
			case 2 : 
					Data = fopen("coba.txt", "r");
				while(fgets(buff, sizeof(buff), Data)){
					strcpy(jenis_kendaraan, strtok(buff, ","));
 
			jenis_sama = strcmp(jenis_kendaraan, jenisR2);
			if (jenis_sama == 0 ){
				total++;
			} 
		}
				fclose(Data);
				printf ("Total %s = %d \n", jenisR2,total );
				break;
			case 3 :
				Data = fopen("coba.txt", "r");
				while(fgets(buff, sizeof(buff), Data)){
					strcpy(jenis_kendaraan, strtok(buff, ","));
 
			jenis_sama = strcmp(jenis_kendaraan, jenisR6);
			if (jenis_sama == 0 ){
				total++;
			} 
		}
				fclose(Data);
				printf ("Total %s = %d \n", jenisR6,total );
				break;
			case 4 :	
				Data = fopen("coba.txt", "r");
				while(fgets(buff, sizeof(buff), Data)){
					strcpy(jenis_kendaraan, strtok(buff, ","));
 
			jenis_sama = strcmp(jenis_kendaraan, jenisR4PRE);
			if (jenis_sama == 0 ){
				total++;
			} 
		}
				fclose(Data);
				printf ("Total %s = %d \n", jenisR4PRE,total );
				break;
 
		}
		if(areaparkir <1 || areaparkir >4){
			printf("Maaf input anda salah!\nSilahkan Input kembali! (1 - 4)!\n ");
		}else{
			//system("cls || clear");
			//break;
			repeat=0;
		}
	}while(repeat==1);

}
 
int cekkeluar() {
	int areaparkir;
	int repeat=1;
	char buff[255];
	char jenis_kendaraan[30];
	int jenis_sama;
	int total=0;
	char jenisR4[30] = "Kendaraan R4";
	char jenisR2[30] = "Kendaraan R2";
	char jenisR6[30] = "Kendaraan R6";
	char jenisR4PRE[30] = "Kendaraan R4 PRE";
 
 
 
 
	printf("+-----------------------------------------------------------------------------------------------+\n");
	printf("|                ||===================================================||                        |\n");
    printf("|                ||                PARKIR KENDARAAN                   ||                        |\n");
    printf("|                ||              BANDARA INTERNASIONAL                ||                        |\n");
    printf("|                ||               I GUSTI NGURAH RAI                  ||                        |\n");
    printf("|                ||===================================================||                        |\n");
    printf("|                                                                                               |\n");
    printf("+----+-----------------------------------+------------------------------------------------------|\n");
    printf("| No |     AREA PARKIR                   | Catatan :                                            |\n");
    printf("+----+-----------------------------------+                                                      |\n");
    printf("|  1 | Gedung Parkir Bertingkat          |==> PARKIR KENDARAAN RODA 4 (MOBIL,dsb)               |\n");
    printf("|  2 | Parkir Kendaraan Bermotor Roda 2  |==> PARKIR KENDARAAN KHUSUS SEPEDA MOTOR RODA 2       |\n");
    printf("|  3 | Area Parkir Bus                   |==> PARKIR KHUSUS BUS /TRUK                           |\n");
    printf("|  4 | Area Parkir Premium               |==> PARKIR KHUSUS RODA 4                              |\n");
    printf("+----+-----------------------------------+------------------------------------------------------+\n");
 
	do{
    	printf("\n\t\t Pilih Area Parkir : ");
	    scanf("%d", &areaparkir);
	    switch (areaparkir){
			case 1 : 
					Data = fopen("coba.txt", "r"); //memperlihatkan total kendaraan di areaparkir lewat data txt
				while(fgets(buff, sizeof(buff), Data)){
					strcpy(jenis_kendaraan, strtok(buff, ","));
 
				jenis_sama = strcmp(jenis_kendaraan, jenisR4);
				if (jenis_sama == 0 ){
					total++;
				} 
			}
				fclose(Data);
				printf ("Total %s = %d \n", jenisR4,total );
							break;
			case 2 : 
					Data = fopen("coba.txt", "r");
				while(fgets(buff, sizeof(buff), Data)){
					strcpy(jenis_kendaraan, strtok(buff, ","));
 
				jenis_sama = strcmp(jenis_kendaraan, jenisR2);
				if (jenis_sama == 0 ){
					total++;
			} 
		}
				fclose(Data);
				printf ("Total %s = %d \n", jenisR2,total );
				break;
			case 3 :
				Data = fopen("coba.txt", "r");
				while(fgets(buff, sizeof(buff), Data)){
					strcpy(jenis_kendaraan, strtok(buff, ","));
 
			jenis_sama = strcmp(jenis_kendaraan, jenisR6);
			if (jenis_sama == 0 ){
				total++;
			} 
		}
			case 4 :
				fclose(Data);
				printf ("Total %s = %d \n", jenisR4PRE,total );
				break;
				Data = fopen("coba.txt", "r");
				while(fgets(buff, sizeof(buff), Data)){
					strcpy(jenis_kendaraan, strtok(buff, ","));
 
				jenis_sama = strcmp(jenis_kendaraan, jenisR4PRE);
				if (jenis_sama == 0 ){
					total++;
			} 
		}
				fclose(Data);
				printf ("Total %s = %d \n", jenisR2,total );
				break;
 
		}
		if(areaparkir <1 || areaparkir >4){
			printf("Maaf input anda salah!\nSilahkan Input kembali! (1 - 4)!\n ");
		}else{
			repeat=1;
		}
	}while(repeat==2);
}