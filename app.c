#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int pil,i,j,n,x;
int posisi,nourut;
char nama[100],pass[100],currentuser[100],cari[100],uname[100],pass[100];
void admin();
void user();
void regis();
void login();
void reset();
void lihatdenda();
void sorting();
void inputbuku();
void editbuku();
void hapusbuku();
void hapususer();
void daftarbuku();
void konfirmasidenda();
void lihatdendauser();
void loginadmin();
void loginuser();
void pinjambuku();
void kembalikanbuku();
void konfirmasipeminjaman();
void konfirmasipengembalian();
void riwayatpeminjaman();
struct pinjam{
	char buku[100], peminjam[100];
	int pinjam, balik, balikuser;
}a;
struct user{
	char uname[100],pass[100];
	int denda;
}b,bantu[100],temp;
struct buku{
	char namabuku[100],namapeminjam[100];
}c;
FILE *fuser;
FILE *fuser2;
FILE *fpinjam;
FILE *fbuku;
FILE *fbuku2;
void regis(){
				system("cls");
				int sama=0;
				fuser=fopen("data user.dat","ab+");
				printf("\tUsername : ");gets(nama);
				while(fread(&b,sizeof(b),1,fuser)==1){
					if(strcmp(b.uname,nama)==0){
						sama=1;
					}
				}
				if(sama==1){
					printf("\tUsername Sudah Ada!!");
					getchar();
					regis();
				}
				b.denda=0;
				strcpy(b.uname,nama);
				printf("\tPass : ");gets(b.pass);
				fwrite(&b,sizeof(b),1,fuser);
				printf("\tPendaftaran Berhasil\n\tSILAHKAN KLIK UNTUK MELANJUTKAN\n");
				fclose(fuser);
				system("pause");
				system("cls");
				main();
}
void login(){
				system("cls");
				printf("\tPilihan Menu :\n\t1. Admin\n\t2. User\n\t3. Kembali Ke Menu Utama\n\tPilih : ");scanf("%d",&pil);
				getchar();
				switch(pil){
					case 1: admin();break;
					case 2: user();break;
					case 3: main();break;
					default: printf("\tMasukkan Pilihan Dengan Benar!!");break;
				}
}
void admin(){
				system("cls");
				int s=0; //variabel perhitungan berapa kali login salah
				printf("\tUsername Admin : ");gets(uname);
				printf("\tPassword Admin : ");gets(pass);
				if(strcmp(uname,"admin")==0 && strcmp(pass,"admin")==0){
					loginadmin();
				}
				else {
					printf("Username atau Password Salah!!\n");
					system("pause");
					if (s<=3){
						s++;
						admin();
					}
					else{
						main();
					}
				}
}
void user(){
				system("cls");
				int x;
				fuser=fopen("data user.dat","rb");
				printf("\tUsername : ");gets(nama);
				printf("\tPassword : ");gets(pass);
				while(fread(&b,sizeof(b),1,fuser)==1){
					if(strcmp(b.uname,nama)==0 && strcmp(b.pass,pass)==0){
						x=1;//ini artinya username sudah terdaftar
					}
				}
				if(x==1){
						loginuser();
				}
				else{
					printf("\tLOGIN GAGAL!!");
					getchar();
					user();
				}
				fclose(fuser);	
}
void lihatdenda(){
				system("cls");
				sorting();
				fuser=fopen("data user.dat","rb");
				printf("List User Beserta Denda :\n");
				while(fread(&b,sizeof(b),1,fuser)==1){
					printf("\tUsername : %s\n",b.uname);
					printf("\tDenda : %i\n",b.denda);
				}
				fclose(fuser);
				system("pause");
				loginadmin();
}
void sorting(){
				fuser=fopen("data user.dat","rb");
				i=0;
				while(fread(&b,sizeof(b),1,fuser)==1){
					bantu[i]=b;
					i++;
				}
				fclose(fuser);
				n=i;
				i=0;
				//sorting bubble
				for(i=n-1;i>=1;i--)
				for(j=1;j<=i;j++){
					if(strcmp(bantu[j-1].uname,bantu[j].uname)>0){
						temp=bantu[j-1];
						bantu[j-1]=bantu[j];
						bantu[j]=temp;
					}
				}
				fuser=fopen("data user.dat","wb");
				for(i=0;i<n;i++){
					b=bantu[i];
					fwrite(&b,sizeof(b),1,fuser);
				}
				fclose(fuser);
}
void inputbuku(){
				system("cls");
				fbuku=fopen("data buku.dat","ab");
				printf("\tInput banyaknya judul buku : ");scanf("%d",&n);getchar();
				printf("\tSilahkan Input Judul Buku : \n");
				for(i=1;i<=n;i++){
					printf("\t%d. ",i);gets(c.namabuku);
					fwrite(&c,sizeof(c),1,fbuku);
				}
				printf("\tInput Berhasil\n\tSILAHKAN KLIK UNTUK KEMBALI KE MENU UTAMA");
				fclose(fbuku);
				system("pause");loginadmin();
}
void editbuku(){
				system("cls");
				char edit[100],baru[100];
				fbuku=fopen("data buku.dat","rb");
				printf("\tList Buku : \n");
				i=1;
				while(fread(&c,sizeof(c),1,fbuku)==1){
					printf("\t%d. %s \n",i,c.namabuku);
					i++;
				}
				fclose(fbuku);
				fbuku = fopen("data buku.dat","rb+");
				fbuku2 = fopen("data buku2.dat","wb");
				printf("\tSilahkan masukkan nama buku yang akan diedit: "); gets(edit);
				while (fread(&c,sizeof (c),1, fbuku)==1){
				if (strcmp(c.namabuku, edit)!=0){
					fwrite(&c, sizeof(c), 1, fbuku2);
				}
				else {
					printf("\tNama Buku Baru : ");gets(baru);
					strcpy(c.namabuku,baru);
					fwrite(&c, sizeof(c), 1, fbuku2);	
				}
				}
				fclose(fbuku);
				fclose(fbuku2);
				remove("data buku.dat");
				rename("data buku2.dat","data buku.dat");
				printf("\tBuku Berhasil Diedit!!\n");
				system("pause");
				loginadmin();
}
void hapusbuku(){
				char dicari[100];
				system("cls");
				fbuku=fopen("data buku.dat","rb");
				printf("\tList Buku : \n");
				i=1;
				while(fread(&c,sizeof(c),1,fbuku)==1){
					printf("\t%d. %s \n",i,c.namabuku);
					i++;
				}
				fclose(fbuku); 
				fbuku=fopen("data buku.dat","rb");
				fbuku2=fopen("data buku2.dat","wb");
				printf("\tSilahkan Masukkan Nama Buku yang Akan dihapus : ");
				gets(dicari);
				while(fread(&c,sizeof(c),1,fbuku)==1){
					if(strcmp(c.namabuku,dicari)!=0){
						fwrite(&c,sizeof(c),1,fbuku2);
					}
				}
				printf("\tBuku Berhasil Dihapus\n");
				fclose(fbuku);
				fclose(fbuku2);
				remove("data buku.dat");
				rename("data buku2.dat","data buku.dat");
				system("pause");system("cls");
				fbuku=fopen("data buku.dat","rb");
				printf("\n\tList Buku Setelah Dihapus : \n");
				i=1;
				while(fread(&c,sizeof(c),1,fbuku)==1){
					printf("\t%d. %s \n",i,c.namabuku);
					i++;
				}
				fclose(fbuku);
				system("pause");
				loginadmin();
}
void hapususer(){	
				system("cls");
				fuser=fopen("data user.dat","rb");
				printf("\tList User : \n");
				i=1;
				while(fread(&b,sizeof(b),1,fuser)==1){
					printf("\t%d. %s \n",i,b.uname);
					i++;
				}
				fclose(fuser);
				fuser=fopen("data user.dat","rb");
				fuser2=fopen("data user2.dat","wb");
				printf("\tSilahkan Masukkan Username yang Akan dihapus : ");
				gets(cari);
				while(fread(&b,sizeof(b),1,fuser)==1){
					if(strcmp(b.uname,cari)!=0){
						fwrite(&b,sizeof(b),1,fuser2);
						}
				}
				fclose(fuser);
				fclose(fuser2);
				remove("data user.dat");
				rename("data user2.dat","data user.dat");
				printf("\tUser %s Berhasil Dihapus\n",cari);
				system("pause");system("cls");
				fuser=fopen("data user.dat","rb");
				printf("\tList User Setelah Dihapus : \n");
				i=1;
				while(fread(&b,sizeof(b),1,fuser)==1){
					printf("\t%d. %s \n",i,b.uname);
					i++;
				}
				fclose(fuser);
				system("pause");
				loginadmin();
}
void daftarbuku(){
				system("cls");
				fbuku=fopen("data buku.dat","rb");
				printf("\tList Buku D-Library : \n");
				i=0;
				while(fread(&c,sizeof(c),1,fbuku)==1){
					i++;
					printf("\t%d. %s \n",i,c.namabuku);
				}
				fclose(fbuku);
				system("pause");
				loginuser();
}
void konfirmasidenda(){
				system("cls");
				char dicari[100];
				int denda;
				fuser = fopen("data user.dat","rb+");
				fuser2 = fopen("data user2.dat","wb");
				printf("\tSilahkan masukkan nama user yang akan dikenai denda: "); gets(dicari);
				while (fread(&b,sizeof (b),1, fuser)==1){
				if (strcmp(b.uname, dicari)!=0){
					fwrite(&b, sizeof(b), 1, fuser2);
				}
				else {
					printf("\tDenda: "); scanf("%d", &denda);
					b.denda=b.denda+denda;
					fwrite(&b, sizeof(b), 1, fuser2);	
				}
				}
				fclose(fuser);
				fclose(fuser2);
				remove("data user.dat");
				rename("data user2.dat","data user.dat");
				getchar();
				printf("\tDenda Berhasil Diinput!!\n");
				system("pause");
				loginadmin();
}
void lihatdendauser(){
				system("cls");
				fuser=fopen("data user.dat","rb");
				printf("\tUser %s \n",currentuser);
				i=0;
				while(fread(&b,sizeof(b),1,fuser)==1){
					if(strcmp(currentuser,b.uname)==0){
						printf("\tTelah terkena denda sebesar Rp. %d",b.denda);
					}
				}
				fclose(fuser);
				system("pause");
				loginuser();
}
void konfirmasipeminjaman(){
				i=1;
				long int offset_byte, no;
				system("cls");
				fpinjam=fopen("data pinjam.dat","rb");
				while(fread(&a,sizeof(a),1,fpinjam)==1){
						printf("\tentry ke -%d \n",i);
						printf("\tUser Yang Meminjam : %s\n",a.peminjam);
						printf("\tBuku Yang Dipinjam : %s\n",a.buku);
						printf("\tStatus Peminjaman  oleh admin: %d\n\n",a.pinjam);
						i++;
				}
				fclose(fpinjam);
				fpinjam=fopen("data pinjam.dat","rb+");
				printf("\tNo daftar yang ingin diedit: "); scanf("%d", &no);
				offset_byte = (no-1)*sizeof(a);
				fseek(fpinjam,offset_byte,SEEK_SET);
				
				if (fread(&a, sizeof (a), 1, fpinjam) == 0){
						printf("\tMenu yang dicari tidak dapat ditemukan pada daftar.\n");
						system("pause");
						system("cls");
						konfirmasipeminjaman();
				}
				fseek(fpinjam, -sizeof(a), SEEK_CUR);
				printf("status peminjaman(0/1) : ");scanf("%d",&a.pinjam);
				fwrite(&a, sizeof(a), 1, fpinjam);	
				fclose(fpinjam);
				system("pause");
				loginadmin();
}
void konfirmasipengembalian(){
				i=1;
				long int offset_byte, no;
				system("cls");
				fpinjam=fopen("data pinjam.dat","rb");
				while(fread(&a,sizeof(a),1,fpinjam)==1){
						printf("\tentry ke -%d \n",i);
						printf("\tUser Yang Meminjam : %s\n",a.peminjam);
						printf("\tBuku Yang Dipinjam : %s\n",a.buku);
						printf("\tStatus pengembalian oleh admin  : %d\n\n",a.balik);
						printf("\tStatus pengembalian oleh user : %d\n\n",a.balikuser);
						i++;
				}
				fclose(fpinjam);
				fpinjam=fopen("data pinjam.dat","rb+");
				printf("\tNo daftar yang ingin diedit: "); scanf("%d", &no);
				offset_byte = (no-1)*sizeof(a);
				fseek(fpinjam,offset_byte,SEEK_SET);
				if (fread(&a, sizeof (a), 1, fpinjam) == 0){
						printf("\tMenu yang dicari tidak dapat ditemukan pada daftar.\n");
						system("cls");
						fclose(fpinjam);
						loginadmin();
				}
				printf("\tUser Yang Meminjam : %s\n",a.peminjam);
				printf("\tBuku Yang Dipinjam : %s\n",a.buku);
				printf("\tStatus pengembalian  : %d\n\n",a.balik);
				printf("\tstatus pengembalian(0/1) : ");scanf("%d",&a.balik);
				if (a.balikuser==0) {
					printf("\tMaaf Tidak Bisa");
					system("pause");
					fclose(fpinjam);
					loginadmin();
				}
				fseek(fpinjam, -sizeof(a), SEEK_CUR);
				fwrite(&a, sizeof(a), 1, fpinjam);	
				fclose(fpinjam);
				system("pause");
				loginadmin();
}
void riwayatpeminjaman(){
				i=1;
				fpinjam=fopen("data pinjam.dat","rb");
				while(fread(&a,sizeof(a),1,fpinjam)==1){
						printf("\tentry ke -%d \n",i);
						printf("\tUser Yang Meminjam : %s\n",a.peminjam);
						printf("\tBuku Yang Dipinjam : %s\n",a.buku);
						printf("\tStatus peminjaman  : %d\n\n",a.pinjam);
						printf("\tStatus pengembalian oleh admin  : %d\n\n",a.balik);
						printf("\tStatus pengembalian oleh user : %d\n\n",a.balikuser);
						i++;
				}
				system("pause");
				loginadmin();
}
void loginadmin(){
				system("cls");
				printf("\tPilihan Menu :\n\t1. Input Buku\n\t2. Edit Buku\n\t3. Hapus Buku\n\t4. Hapus User\n\t5. Konfimasi Peminjaman\n\t6. Konfirmasi Pengembalian\n\t7. Riwayat Peminjaman\n\t8. Konfirmasi Denda\n\t9. Lihat Denda\n\t10. Kembali Ke Menu Utama");
				printf("\n\tPilih : ");scanf("%d",&pil);
				getchar();
				switch (pil){
					case 1:inputbuku();break;
					case 2:editbuku();break;
					case 3:hapusbuku();break;
					case 4:hapususer();break;
					case 5:konfirmasipeminjaman();break;
					case 6:konfirmasipengembalian();break;
					case 7:riwayatpeminjaman();break;
					case 8:konfirmasidenda();break;
					case 9:lihatdenda();break;
					case 10:main();break;
					default:printf("\tMasukkan Pilihan Dengan Benar!!!");break;
				}
}
void loginuser(){
					system("cls");
					strcpy(currentuser,nama);
					printf("\tPilihan Menu :\n\t1. Daftar Buku\n\t2. Pinjam Buku\n\t3. Kembalikan Buku\n\t4. Lihat Denda\n\t5. Menu Utama");
					printf("\n\tPilih : ");scanf("%d",&pil);
					getchar();
					switch (pil){
						case 1:daftarbuku();break;
						case 2:pinjambuku();break;
						case 3:kembalikanbuku();break;
						case 4:lihatdendauser();break;
						case 5:main();break;
						default : printf("\tMasukkan Pilihan Dengan Benar!!!");break;
					}
}
void kembalikanbuku(){
				i=1;
				x=0;
				system("cls");
				fpinjam=fopen("data pinjam.dat","rb");
				while(fread(&a,sizeof(a),1,fpinjam)==1){
					if (strcmp(a.peminjam, currentuser)==0) {
						printf("\tentry ke -%d \n",i);
						printf("\tBuku Yang Dipinjam : %s\n",a.buku);
						printf("\tStatus peminjaman  : %d\n",a.pinjam);
						printf("\tStatus pengembalian oleh admin  : %d\n",a.balik);
						printf("\tStatus pengembalian oleh user : %d\n\n",a.balikuser);
						i++;
					}
				}
				fclose(fpinjam);
				fpinjam=fopen("data pinjam.dat","rb+");
				printf("\tBuku yang ingin dikembalikan : ");gets(cari);
				/**/
				while(fread(&a,sizeof(a),1,fpinjam)==1) {
					if (strcmp(a.peminjam, currentuser)==0 && strcmp(a.buku,cari)==0) {
						if (a.pinjam==0 || a.balik==1) {
							printf("\tTidak bisa mengembalikan. Cek status peminjaman buku Anda\n");
							getchar();
							system("cls");
							fclose(fpinjam);
							loginuser();
							x=1;
						}
						else {
							fseek(fpinjam, -sizeof(a), SEEK_CUR);
							printf("\tYakin mengajukan pengembalian? (1 : YA / 0: TIDAK): ");
							scanf("%d",&a.balikuser);
							fwrite(&a, sizeof(a), 1, fpinjam);
							fclose(fpinjam);
							if(a.balikuser==1){
								printf("\tBuku Berhasil Diajukan untuk Dikembalikan\n");
							}
							system("pause");
							loginuser();
							x=1;
						}
					}	
				}
				if(x==0) {
						printf("\tCek kembali buku yang Anda input\n");
					}
				fclose(fpinjam);
				system("pause");
				loginuser();
}
void pinjambuku(){
				int z=0;
				char namatemp[100];
				fbuku = fopen("data buku.dat", "rb");
				fpinjam=fopen("data pinjam.dat","ab+");
				printf("\tBuku yang ingin dipinjam : ");gets(cari);
				/**/
				while(fread(&a,sizeof(a),1,fpinjam)==1) {
					if (strcmp(a.peminjam, b.uname)==0) {
						if (a.balik==0) {
							printf("\tTidak bisa meminjam. cek status pengembalian buku anda/cek kembali buku yang anda input\n");
							getchar();
							system("cls");
							pinjambuku();
						}
					}
				}
				
				while(fread(&c,sizeof(c),1,fbuku)==1){
				if(strcmp(cari,c.namabuku)==0){
					strcpy(a.buku,c.namabuku);
					strcpy(a.peminjam,currentuser);
					a.pinjam=0;
					a.balik=0;
					a.balikuser=0;
					fwrite(&a, sizeof(a), 1, fpinjam);
					printf("\tBerhasil meminjam. Menunggu konfirmasi admin\n");
					z=1;
				}
				}
				
				if (z==0) {
					printf("\tBuku tidak ditemukan.\n");
				}
				fclose(fbuku);
				fclose(fpinjam);
				system("pause");
				loginuser();
}
main(){
	system("cls");
	printf("\tMENU D-LIBRARY\n");
	printf("\t1. Registrasi User\n\t2. Login (USER/ADMIN)\n\t3. Exit\n\tPilih Menu : ");scanf("%d",&pil);
	getchar();
	switch (pil){
		case 1 : regis();break;
		case 2 : login();break;
		case 3 : exit(0);break;
		default : printf("\tMasukkan Pilihan Dengan Benar");break;
	}
}


