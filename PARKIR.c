#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>



struct data { 
	int jenis;
	char plat[10];
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
int kedalam(); //untuk pilihan pertama inputan ketika kendaraan masuk parkir
int meninggalkan(); //untuk pilihan kedua ketika kendaraan akan meninggalkan parkir
int cekparkir(); //untuk mengecek kendaraan yang ada di dalam parkir
//int cekkeluar(); //untuk mengecek kendaraan yang keluar parkir




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
		/*case 3 :
			cekparkir();
			system("pause");
			system("cls");
			break;
		case 4 :
			cekkeluar();
			system("pause");
			system("cls");
			break; */
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


int kedalam () { //fungsi untuk menu pertama saat kendaraan masuk parkir
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
	fprintf(Data, "+-----------------------------------------------------+\n");
	fprintf(Data, " Jenis Kendaraan    : %s \n", kendaraan);
	fprintf(Data, " Plat Nomor         : %s \n", parkir.plat);
	fprintf(Data, " Tanggal            : %d-%d-%d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
	fprintf(Data, " Jam Masuk          : %d \n", time(&masuk));


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
    return 0;
}

int meninggalkan () { //fungsi untuk menu kedua saat kendaraan keluar parkir
	struct data parkir;
    t = time(NULL);
    tm = localtime(&t);
	float biaya, progresif, lama, jam;
	
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
	fflush(stdin);
	
	system ("cls");

//pengambilan atau pengecak data diambil dari plat nomornya, untuk di struk data terakhir. 
/*Data = fopen ("coba.txt", "r");
fprintf(Data, " Jenis Kendaraan    : %s \n", kendaraan);
fprintf(Data, " Plat Nomor         : %s \n", parkir.plat);
fprintf(Data, " Tanggal            : %d-%d-%d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
fprintf(Data, " Jam Masuk          : %d \n", time(&masuk)); */

	keluar = time(&keluar);	//untuk jam keluar
	
	if (parkir.jenis == 1) {	
	printf("+-----------------------------------------------------+\n");
	printf("|                 NOTA PARKIR KENDARAAN               |\n");
	printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
	printf("+-----------------------------------------------------+\n");
	printf("| Jenis Kendaraan    : %s \n", kendaraan);                  
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
   
   else if (parkir.jenis == 2) {
   		printf("+-----------------------------------------------------+\n");
		printf("|                 NOTA PARKIR KENDARAAN               |\n");
		printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
		printf("+-----------------------------------------------------+\n");
		printf("| Jenis Kendaraan    : %s \n", kendaraan);
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
   else if (parkir.jenis == 3) {
   		printf("+-----------------------------------------------------+\n");
		printf("|                 NOTA PARKIR KENDARAAN               |\n");
		printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
		printf("+-----------------------------------------------------+\n");
		printf("| Jenis Kendaraan    : %s \n", kendaraan);
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
   else if (parkir.jenis == 4) {
   		printf("+-----------------------------------------------------+\n");
		printf("|                 NOTA PARKIR KENDARAAN               |\n");
		printf("|            BANDARA INTERNASIONAL NGURAH RAI         |\n");
		printf("+-----------------------------------------------------+\n");
		printf("| Jenis Kendaraan    : %s \n", kendaraan);
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
	return 0;
}
