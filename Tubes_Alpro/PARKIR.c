#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>



struct data { //struct untuk data parkir
	int jenis;
	char plat[20];
};


//untuk waktu agar dapat mengambil waktu lokal
time_t t;
struct tm *tm;
time_t now;
    
//variabel global
char kendaraan[25];
float roda2 = 4.000; 
float roda4 = 10.000;
float roda6 = 15.000;
float premium = 30.000;
time_t masuk;
time_t keluar;
FILE *Data;

//deklarasi fungsi
int menu(); //untuk menampilkan menu awal
void kedalam(); //untuk pilihan pertama inputan ketika kendaraan masuk parkir
void meninggalkan(); //untuk pilihan kedua ketika kendaraan akan meninggalkan parkir
int pembayaran(); //untuk pembayaran saat keluar parkir 
void cekparkir(); //untuk mengecek kendaraan yang ada di dalam parkir
int cekkeluar(); //untuk mengecek kendaraan yang keluar parkir




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
			printf("\nPilihan Tidak Tersedia !!!\n\n");
            system("pause");
            system("cls");
		}
	}
}



int menu () {
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
	printf("Masukan Pilihan : ");
	scanf("%d", &pilih);
	
	return pilih;
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
	printf("Masukan Jenis Kendaraan : "); scanf("%d", &parkir.jenis);
	
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
	
	system ("cls");
	
	printf("Plat Nomor Kendaraan : ");
	fflush(stdin);
	scanf("%[^\n]", &parkir.plat);
	
	system ("cls");
	
	Data = fopen("coba.txt", "a"); //memasukan data pada file external
	fprintf(Data, "%s, %s, %d-%d-%d, %d, %s \n", kendaraan, parkir.plat, tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900, time(&masuk), "masuk");

	masuk = time(&masuk); //untuk jam masuk
    printf("Kendaraan Dalam Parkiran \n"); //data yang di print pada terminal (interface)
    	printf("+-----------------------------------------------------+\n");
		printf("|                    PARKIR KENDARAAN                 |\n");
		printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
		printf("+-----------------------------------------------------+\n");
		printf("| Jenis Kendaraan    : %s \n", kendaraan);
		printf("| Plat Nomor         : %s \n", parkir.plat);
		printf("| Tanggal            : %d-%d-%d\n", tm->tm_hour, tm->tm_mon+1, tm->tm_year+1900);
		printf("| Jam Masuk          : %d:%d \n", localtime(&masuk)->tm_hour, localtime(&masuk)->tm_min);
		printf("+-----------------------------------------------------+\n");
    
    fclose(Data);
}

void meninggalkan() { //prosedur untuk menu kedua saat kendaraan keluar parkir
	struct data parkir;
	int read;
	char plat[20];
	char kendaraanfile[20];
	char tanggal[20];
	char waktumasuk[0];
	char status[6];
    t = time(NULL);
    tm = localtime(&t);
	float biaya, progresif, lama, jam;
	
	//untuk pencarian data kendaraan yang akan keluar parkir
	printf("Plat Nomor Kendaraan : ");
	fflush(stdin);
	scanf("%[^\n]", parkir.plat);
	getchar();
	system ("cls");

//pengambilan atau pengecak data diambil dari plat nomornya, untuk di struk data terakhir. 
	Data = fopen("coba.txt", "r+");
	if (Data == NULL) {
		printf ("DATA KENDARAAN SAAT MASUK ANDA TIDAK DITEMUKAN \n SILAHKAN MASUK TERLEBIH DAHULU");
		kedalam();
	}
	else {
		do{
			read = fscanf(Data,"%20[^,],%20[^,],%20[^,],%20[^,],%20[^\n]\n", kendaraanfile, plat, tanggal, waktumasuk,status);
			if (read == 5){
				//printf("%s\n", plat);
				//printf("%d \n",strcmp(parkir.plat, plat));
				if(strcmp(parkir.plat, plat) == 0){
					//printf("Jenis kendaraan %s %s %s %s %s", kendaraanfile, plat, tanggal, waktumasuk,status);
					//printf("%s", status);
					//system ("pause");
					char new_status[6] = "keluar";
					fprintf(Data, "%s, %s, %d-%d-%d, %d, %s \n", kendaraan, parkir.plat, tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900, time(&masuk), "keluar");
					printf("%s",status);
				}
				//printf("%s", status);
			}
		}while(!feof(Data));
	}
	fclose(Data);
system("pause");
system("cls");
	
	keluar = time(&keluar);	//untuk jam keluar
	if (parkir.jenis == 1) {	 //untuk struk pembayaran kendaraan R2
	printf("+-----------------------------------------------------+\n");
	printf("|                 NOTA PARKIR KENDARAAN               |\n");
	printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
	printf("+-----------------------------------------------------+\n");
	printf("| Jenis Kendaraan    : %s \n", kendaraanfile);                  
	printf("| Plat Nomor         : %s \n", parkir.plat);
	printf("| Tanggal            : %d-%d-%d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
	printf("| Jam Masuk          : %d:%d \n", localtime(&masuk)->tm_hour, localtime(&masuk)->tm_min);
	printf("| Jam Keluar         : %d:%d \n", localtime(&keluar)->tm_hour, localtime(&keluar)->tm_min);
	
	//proses penghitungan biaya parkir
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
	printf("| Lama Parkir        : %.2f jam\n", lama);
	printf("| Biaya Parkir       : Rp. %0.3f \n", biaya);
	printf("+-----------------------------------------------------+\n");
	printf("|           TERIMA KASIH ATAS KUNJUNGAN ANDA          |\n");
	printf("+-----------------------------------------------------+\n");
   }
   
   else if (parkir.jenis == 2) {	//untuk struk pembayaran kendaraan R4
   		printf("+-----------------------------------------------------+\n");
		printf("|                 NOTA PARKIR KENDARAAN               |\n");
		printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
		printf("+-----------------------------------------------------+\n");
		printf("| Jenis Kendaraan    : %s \n", kendaraanfile);
		printf("| Plat Nomor         : %s \n", parkir.plat);
		printf("| Tanggal            : %d-%d-%d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
		printf("| Jam Masuk          : %.2f \n", masuk);
		printf("| Jam Keluar         : %.2f \n", keluar);
		
	//proses penghitungan biaya parkir
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
		printf("| Lama Parkir        : %.2f jam\n", lama);
		printf("| Biaya Parkir       : Rp. %0.3f \n", biaya);
		printf("+-----------------------------------------------------+\n");
		printf("|           TERIMA KASIH ATAS KUNJUNGAN ANDA          |\n");
		printf("+-----------------------------------------------------+\n");
   }
   else if (parkir.jenis == 3) {	//untuk struk pembayaran kendaraan R6
   		printf("+-----------------------------------------------------+\n");
		printf("|                 NOTA PARKIR KENDARAAN               |\n");
		printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
		printf("+-----------------------------------------------------+\n");
		printf("| Jenis Kendaraan    : %s \n", kendaraanfile);
		printf("| Plat Nomor         : %s \n", parkir.plat);
		printf("| Tanggal            : %d-%d-%d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
		printf("| Jam Masuk          : %.2f \n", masuk);
		printf("| Jam Keluar         : %.2f \n", keluar);
		
	//proses penghitungan biaya parkir
	lama = difftime(keluar, masuk) / 3600;
	if (lama <= 1 ) {
	       biaya = roda6;
	   } 
	else if (lama > 1 ) {
	       jam = lama - 1; 
	       progresif = 5.000 * jam;
	       biaya = roda6 + progresif;
		} 
	else {
		   printf ("Denda Karcis Hilang Rp. 100.000");
		}
		printf("| Lama Parkir        : %.2f jam\n", lama);
		printf("| Biaya Parkir       : Rp. %0.3f \n", biaya);
		printf("+-----------------------------------------------------+\n");
		printf("|           TERIMA KASIH ATAS KUNJUNGAN ANDA          |\n");
		printf("+-----------------------------------------------------+\n");
   }
   else if (parkir.jenis == 4) { //untuk struk pembayaran kendaraan R4 Premium
   		printf("+-----------------------------------------------------+\n");
		printf("|                 NOTA PARKIR KENDARAAN               |\n");
		printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
		printf("+-----------------------------------------------------+\n");
		printf("| Jenis Kendaraan    : %s \n", kendaraanfile);
		printf("| Plat Nomor         : %s \n", parkir.plat);
		printf("| Tanggal            : %d-%d-%d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
		printf("| Jam Masuk          : %.2f \n", masuk);
		printf("| Jam Keluar         : %.2f \n", keluar);
		
	//proses penghitungan biaya parkir
	lama = difftime(keluar, masuk) / 3600;
	if (lama <= 1 ) {
	       biaya = roda4 + premium;
	   } 
	else if (lama > 1 ) {
	       jam = lama - 1; 
	       progresif = 5.000 * jam;
	       biaya = roda4 + progresif + premium;
		} 
	else {
		   printf ("Denda Karcis Hilang Rp. 100.000");
		}
		printf("| Lama Parkir        : %.2f jam\n", lama);
		printf("| Biaya Parkir       : Rp. %0.3f \n", biaya);
		printf("+-----------------------------------------------------+\n");
		printf("|           TERIMA KASIH ATAS KUNJUNGAN ANDA          |\n");
		printf("+-----------------------------------------------------+\n");
   } 
}


/*void pembayaran () {
	int bayar;
	
	printf("+-----------------------------------------------------+\n");
	printf("|                  JENIS KENDARAAN                    |\n");
	printf("+-----------------------------------------------------+\n");
	printf("|     1. Cash                                         |\n");
	printf("|     2. E-Money                                      |\n");
	printf("+-----------------------------------------------------+\n");
	printf ("Pembayaran dilakukan dengan apa?");
	scanf("%d", &bayar);
	
	if (bayar == 1) {
	
		
	}
	else if (bayar == 2) {
		//masukkan no e money setelahnya mengecek apakah e money berisi uang atau tidak 
		//jika tidak arahkan untuk melakukan top up
		//jika sudah berisi langsung dikurangi saldo dari e money
	}
} */
//untuk notanya nanti setelah selesai memilih metode pembayaran
//coba cari cara pembayaran di tol
//misal kalo e money tidak isi saldo bisa minjam ke pengendara di belakang atau beralih ke cash saja

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
 
