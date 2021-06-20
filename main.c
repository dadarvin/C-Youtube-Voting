/*
    Pemrograman Lanjut 02 - Proyek Akhir
    Ide Program = Youtube Nomination
    -----------------------------------------------
    Darvin (1906300694) & Frederik D.J (1906300744)
    Dibuat pada 17/12/2020
*/
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include <string.h>
#define kandidat 4
#define SIZE 20
#define RED "\x1B[31m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define RESET "\x1b[0m"

//Deklarasi Variabel Global
int n; //Banyak Pemilih pada acara
int sudahVote =0, batas[2] = {0}; //Banyak pemilih yang sudah voting
int edu[kandidat] = {0}, tekno[kandidat]={0}, stream[kandidat]={0}, vlogger[kandidat]={0}; //Jumlah voting untuk setiap kandidat
char kandidatEdu[SIZE][SIZE] = {"Crash Course", "Neso Academy", "Khan Academy", "Zenius"}; //Kandidat untuk nominasi Edukasi
char kandidatTekno[SIZE][SIZE] = {"Marques Brownley", "GadgetIn        ", "Unbox Theraphy  ", "Linus Techtips  "}; //Kandidat untuk nominasi Teknologi
char kandidatStream[SIZE][SIZE] = {"Reza Arap", "Kimihime", "Jess No Limit", "Milyhya"}; //Kandidat untuk nominasi Streamer
char kandidatVlogger[SIZE][SIZE] = {"Raditya Dika      ", "Rans Entertainment", "Atta Halilintar   ", "Arief Muhammad    "}; //Kandidat untuk nominasi Vlogger

//Modular yang digunakan pada program
COORD coord={0,0};
void menu();
void gotoxy(int x, int y);
void pemilihan();
void pilihanKategori(int array[]);
void hasilNominasi();
void adminPassword();
void adminMenu();
void menuAdmin();
void swap(int pilihan);
void cekVote();
void menukar(int i);
void searching();
void selesaiv();
void dataSebelum();

struct Node //struct untuk linkedlist penyimpanan vote kategori
{
    int nominasi;
    struct Node *next;
};

struct dataPemilih //struct untuk menyimpan data pemilih
{
    char nama[SIZE][SIZE];
    int umur;
    int edukasi, teknologi, streamer, vlog;
};

struct dataPemilih *pemilih;

struct Node* newNode(int data, struct Node* nextNode)
{
	// membuat node baru pada linkedlist
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	//memasukkan input pilihan kategori ke node
	node->nominasi = data;

	// mengarahkan node baru pada node selanjutnya
	node->next = nextNode;

	return node;
}

// membentuk linked list dari input yang dimasukkan
struct Node* constructList(int keys[], int n)
{
	int i;
	struct Node* head = NULL, *node = NULL;

	// membuat node dari akhir input ke awal
	for ( i= n - 1; i >= 0; i--)
	{
		node = newNode(keys[i], node);
		head = node;
	}

	return head;
}

// menampilkan input pilihan nominasi yang dimasukkan
void printList(struct Node* head)
{
	struct Node* ptr = head;
	while (ptr!=NULL)
	{
		printf("%d -> ", ptr->nominasi);
		ptr = ptr->next;
	}
	printf("Selesai");
}

int main()
{
   menu();
}


void gotoxy (int x, int y) { //Fungsi Untuk memindahkan kursor
  coord.X=x;
  coord.Y=y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void menu()
{
    int kategori;

    system("CLS");
    printf("\t\t                           =========================\n");
    printf("\t\t                             ! Youtube Nomination !\n");
    printf("\t\t                           =========================\n\n");
    printf(RED"\t\t\t\t          ,,,,,,,,,,,,,,,,,,,,,,,,,,,      \n");
    printf("\t\t\t\t       `:+ooooossssssssssssssssooooo+:`    \n");
    printf("\t\t\t\t       `+ssssssssssssssssssssssssssssss+`   \n");
    printf("\t\t\t\t       .ssssssssssssssssssssssssssssssss.   \n");
    printf("\t\t\t\t       :ssssssssssss+-/ossssssssssssssss:   \n");
    printf("\t\t\t\t       /yyyyyyyyyyyy/  `.:+osyyyyyyyyyyyy   \n");
    printf("\t\t\t\t       /yyyyyyyyyyyy/     `-+syyyyyyyyyyy  \n");
    printf("\t\t\t\t       /yyyyyyyyyyyy/   .:+osyyyyyyyyyyyy   \n");
    printf("\t\t\t\t       :yyyyyyyyyyyyo syyyyyyyyyyyyyyyyy:   \n");
    printf("\t\t\t\t       .yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy.   \n");
    printf("\t\t\t\t       `+yyyyyyyyyyyyyyyyyyyyyyyyyyyyyy+`   \n");
    printf("\t\t\t\t        `:+osssssyyyyyyyyyyyyyyssssso+:`    \n");
    printf("\t\t\t\t          ````````````````````````````      \n"RESET);
    printf(YEL"\t\t        ___                           ___                             ___ \n");
    printf("\t\t       |_  |                         |_  |                           |_  |\n");
    printf("\t\t        _| |_                        |  _|                           |_  |\n");
    printf("\t\t       |_____|                       |___|                           |___|\n"RESET);
    printf("\t\t  -------------------       --------------------------          ----------------\n");
	printf(CYN"\t\t  Pilih Youtubermu !        Lihat Nominasi Sementara !    	 Khusus Admin !\n\n"RESET);


    switch(getch())//Menerima input user untuk pilihan menu
    {
    fflush(stdin);
    case '1':
       	pemilihan();
        break;
    case '2':
        hasilNominasi();
        break;
    case '3':
        adminPassword();
        break;
    default: //Jika Input salah maka panggil kembali Modular menu untuk menerima input kembali
        printf("\n\aMasukkan Input yang benar !");
        printf("\nTekan (Enter) untuk memasukkan input kembali....");
        getch();
        system("CLS");
        menu();
    }
}

void pemilihan()
{
    int j, k, voteKategori[4] = {0};
    char input;
    int pilihan[4] = {0}, tertentu[4] = {0}, banyakKategori = 0;
	int i, n=0;

    if(batas[0]==batas[1])//Error handling jika belum melakukan alokasi memori
    {
        MessageBox(0,"Anda belum memasukan batas voting !", "Masukkan Batas Pemilih", MB_OK );
        menu();
    }

    system("CLS");
    printf("    _    _         _   _ _             ___           _ _ _ _    \n");
    printf("   (_)__| |___ _ _| |_(_) |_ __ _ ___ | _ \\___ _ __ (_) (_) |_  \n");
    printf("   | / _` / -_) ' \\  _| |  _/ _` (_-< |  _/ -_) '  \\| | | | ' \\ \n");
    printf("   |_\\__,_\\___|_||_\\__|_|\\__\\__,_/__/ |_| \\___|_|_|_|_|_|_|_||_|\n");
    //Input data diri dari user untuk melakukan voting
    printf("\n");
	printf("\t\t\t\t\t\t    Masukkan Nama Anda : \n");
	printf("\t\t\t\t\t\t    ");
	scanf("%s", (pemilih+sudahVote)->nama);
	printf("\n  \t\t\t\t\t\t    Umur :\n");
	printf("\t\t\t\t\t\t    ");
	scanf("%d", &(pemilih+sudahVote)->umur);
	if ((pemilih+sudahVote)->umur<13 || (pemilih+sudahVote)->umur>70)
	{
		printf("\t\t\t\t\t\t    Batas Umur untuk voting adalah 13 sampai 70!\a");
		printf("\n\nTekan (Enter) untuk memasukkan data kembali...");
		getch();
		return pemilihan();
	}

	system("CLS");
	printf("\n     ___ _ _ _ _      _  __     _                    _ \n");
    printf(YEL"    | _ (_) (_) |_   | |/ /__ _| |_ ___ __ _ ___ _ _(_)\n");
    printf("    |  _/ | | | ' \\  | ' </ _` |  _/ -_) _` / _ \\ '_| |\n");
    printf("    |_| |_|_|_|_||_| |_|\\_\\__,_|\\__\\___\\__, \\___/_| |_|\n");
    printf("                                       |___/	    \n"RESET);

    printf("        -- Daftar Nominasi--\n\n");
    printf("      +/+        :o+       `-so`       EDUKASI                TEKNOLOGI\n");
    printf("       ://-    `-+:+/`   `./++      1. %s        1. %s \n", kandidatEdu[0], kandidatTekno[0]);
    printf("      ``+::/:` -+::/+/``-/+/o.      2. %s        2. %s\n",kandidatEdu[1], kandidatTekno[1] );
    printf("       `-/:::///:::///++///+/       3. %s        3. %s\n", kandidatEdu[2], kandidatTekno[2]);
    printf("         +:::::::::////////o        4. %s              4. %s\n", kandidatEdu[3], kandidatTekno[3]);
    printf("        ``o++++++++o+++/:+o:`        \n");
    printf("         `////:://////////o`            STREAMER              Vlog\n");
    printf("          :////////+//+++//         1. %s           1. %s\n", kandidatStream[0], kandidatVlogger[0]);
    printf("                                    2. %s            2. %s\n", kandidatStream[1], kandidatVlogger[1]);
    printf("                                    3. %s       3. %s\n", kandidatStream[2], kandidatVlogger[2]);
    printf("                                    4. %s             4. %s\n", kandidatStream[3], kandidatVlogger[3]);

	printf("\nApakah anda ingin vote semua kategori ? (Y/N)");
    scanf(" %c", &input);
    if(input =='y' || input == 'Y') //Jika Pemilih ingin vote semua kategori
    {
        printf("\nMasukkan Pilihan Nominasi untuk keempat kategori (Edukasi Teknologi Streamer Vlog): \n");
        memilih:
        for(i=0; i<4; i++)
        {
            printf("\Pilihan kategori %d : ", i+1);
            scanf("%d", &pilihan[i]);
            if(pilihan[i]<=0 || pilihan[i]>4)
            {
                printf("Input tidak valid !, tekan(enter) untuk input kembali..\n");
                getch();
                goto memilih;
            }
        }
        n=i;
        struct Node* head = constructList(pilihan, n);

        edu[pilihan[0]-1]++;
        tekno[pilihan[1]-1]++;
        stream[pilihan[2]-1]++;
        vlogger[pilihan[3]-1]++;

        //Memasukkan data voting ke struct masing-masing pemilih
        (pemilih+sudahVote)->edukasi = pilihan[0];
        (pemilih+sudahVote)->teknologi = pilihan[1];
        (pemilih+sudahVote)->streamer = pilihan[2];
        (pemilih+sudahVote)->vlog = pilihan[3];
        printf("\nVote yang anda masukkan : \n");
        printList(head);

    } else //Jika pemilih mau vote kategori tertentu saja
    {
        printf("\nPilihan Kategori : ");
        printf("\n1. Edukasi \n2. Teknologi \n3. Streamer \n4. Vlog\n\n");
        jmlhKategori:
        printf("Jumlah kategori yang akan anda vote  =  ");
        scanf("%d", &banyakKategori);
        if(banyakKategori<=0 || banyakKategori>4)
        {
            printf("Input tidak valid !, tekan(enter) untuk input kembali..\n");
            getch();
            goto jmlhKategori;
        }
        pilihKategori:
        printf("Masukkan Pilihan kategori mu : ");
        for(j=0; j<banyakKategori; j++)
        {
            scanf("%d", &voteKategori[j]); //Meminta input kategori yang ingin dipilih saja
            if(voteKategori[j]<=0 || voteKategori[j]>4)
            {
                printf("Input tidak valid !, tekan(enter) untuk input kembali..\n");
                getch();
                goto pilihKategori;
            }
        }
        printf("----------------------------------------------------\n");
        voteTertentu :
        for(i=0; i<banyakKategori; i++)
        {
            printf("\nPilihan Nominasi untuk kategori %d = ", voteKategori[i]);
            scanf("%d", &pilihan[i]);
            if(pilihan[i]<=0 || pilihan[i]>4)
            {
                printf("Input tidak valid !, tekan(enter) untuk input kembali..\n");
                getch();
                goto voteTertentu;
            }

            if(voteKategori[i]==1)
            {
                tertentu[0] = pilihan[i];
                edu[pilihan[1]-1]++;
            }
            if(voteKategori[i]==2)
            {
                tertentu[1] = pilihan[i];
                tekno[pilihan[i]-1]++;
            }
            if(voteKategori[i]==3)
            {
                tertentu[2] = pilihan[i];
                stream[pilihan[i]-1]++;
            }
            if(voteKategori[i]==4)
            {
                tertentu[3] = pilihan[i];
                vlogger[pilihan[i]-1]++;
            }
        }
        n=i;
        struct Node* head = constructList(pilihan, n);

        (pemilih+sudahVote)->edukasi = tertentu[0];
        (pemilih+sudahVote)->teknologi = tertentu[1];
        (pemilih+sudahVote)->streamer = tertentu[2];
        (pemilih+sudahVote)->vlog = tertentu[3];
        printf("\nVote yang anda masukkan : \n");
        printList(head);
    }

	printf("\n\nTekan (Enter) untuk melanjutkan....");
	getch();
    sudahVote++; //increment jumlah pemilih yang sudah vote
    batas[0] = sudahVote;
	thanks();
}

void hasilNominasi()
{
    int i;
    system("CLS");

    printf("\n\n");
    printf(YEL"\t                                         `.-..```````````````.--.         \n");
    printf("\t                                        ::```://////////:---:.``-:        \n");
    printf("\t                                       `:-   -//////////:----   .:`       \n");
    printf("\t                                        `:-.``://///////:--:` `-:`        \n");
    printf("\t    _____           _             _       `.--::////////:-::---`          \n");
    printf("\t   |   | |___ _____|_|___ ___ ___|_|          `.://////:---`              \n");
    printf("\t   | | | | . |     | |   | .'|_ -| |            `-:///::-`                \n");
    printf("\t   |_|___|___|_|_|_|_|_|_|__,|___|_|              -///::`                 \n");
    printf("\t                                             ````::::::::````             \n");
    printf("\t                                             oo////////////oo             \n");
    printf("\t                                             os:----------:ss             \n");
    printf("\t                                             ////////////////             \n\n"RESET);
    printf("\t     EDUKASI         Jumlah            TEKNOLOGI          Jumlah");
    for(i=0; i<4; i++)
    {
        printf("\n %11d %-18s%-14d%1d %-10s%6d", i+1, kandidatEdu[i], edu[i], i+1, kandidatTekno[i], tekno[i]);
    }
    printf("\n\n\t   STREAMER          Jumlah          Vlog                 Jumlah");
    for(i=0; i<4; i++)
    {
        printf("\n %11d %-18s%-14d%1d %-10s%5d", i+1, kandidatStream[i], stream[i], i+1, kandidatVlogger[i], vlogger[i]);
    }

    printf("\n\n\n\nTekan (Enter) untuk kembali ke menu utama....");
    getch();
    menu();
}

void adminPassword() //Modular untuk pengguna admin
{

    char password[5] = "admin";
	char pass[15];
	int x, j=0, k;
	int log = 0;
    Password:
	system("CLS");
	printf("\n\n\n\n\n");
	printf("\t\t\t   ____                 __           \n");
    printf("\t\t\t  /  _/__  ___ ___ ____/ /_          \n");
    printf("\t\t\t _/ // _ \\(_-</ -_) __/ __/               \n");
    printf("\t\t\t/___/_//_/___/\\__/_/  \\__/                          __\n");
    printf("\t\t\t               / _ \\___ ____ ____    _____  _______/ /\n");
    printf("\t\t\t              / ___/ _ `(_-<(_-< |/|/ / _ \\/ __/ _  / \n");
    printf("\t\t\t             /_/   \\_,_/___/___/__,__/\\___/_/  \\_,_/  \n");
    gotoxy(52,13);
	printf("Enter your password: ");
	//Menerima input password yang akan diganti dengan * agar tidak dapat terlihat
	for(x=0;x<5;x++)
    {
        pass[x]=getch();
        printf("%c",'*');
    }
    pass[x]='\0';
    if((strcmp(pass,password))!=0)
    {
        j++;
        printf("\nWrong Password (Press Enter to Try Again)\n");
        if(j==3)
        {
            printf("\nAnda salah memasukkan 3 kali !, mohon menunggu 5 detik");
            printf("\a");
            for(k=1; k<=5; k++) //Looping selama 5 detik jika sudah salah input 5 kali
                {
                    printf("\n%d", k);
                    Sleep(1000);
                }
                    adminPassword();
        }
            getch();
            goto Password;
    }
    else
    {

        printf("\n\nADMIN LOGIN SUCCESSFULL");
        for(k=0; k<6; k++)
        {
            printf(".");
            Sleep(200);
        }
            printf("(Press Enter)");
			getch();
			adminMenu();
    }

}

void adminMenu()
{
    int n;
    system("CLS");

    system("CLS");
    printf(GRN" _____   _       _     \n");
    printf("|  _  |_| |_____|_|___ \n");
    printf("|     | . |     | |   |\n");
    printf("|__|__|___|_|_|_|_|_|_|\n"RESET);
	printf("\n\n\t\t\t\t===================================================\n");
	printf("\t\t\t       |                                                  |\n");
	printf("\t\t\t       |                                                  |\n");
	printf("\t\t\t       |         PILIH FITUR YANG INGIN DIGUNAKAN:        |\n");
	printf("\t\t\t       |            __                                    |\n");
	printf("\t\t\t       |           |1.| Masukkan batas pemilih nominasi   |\n");
	printf("\t\t\t       |           |__|                                   |\n");
	printf("\t\t\t       |            __                                    |\n");
	printf("\t\t\t       |           |2.| Tampilkan Data Voting             |\n");
	printf("\t\t\t       |           |__|                                   |\n");
	printf("\t\t\t       |            __                                    |\n");
	printf("\t\t\t       |           |3.| Selesaikan Voting                 |\n");
	printf("\t\t\t       |           |__|                                   |\n");
	printf("\t\t\t       |                                                  |\n");
	printf("\t\t\t       |            __                                    |\n");
	printf("\t\t\t       |           |0.| Exit to menu                      |\n");
	printf("\t\t\t       |           |__|                                   |\n");
	printf("\t\t\t       |                                                  |\n");
    printf("\t\t\t       ====================================================\n");

    switch(getch())
    {
    fflush(stdin);
    case '1':
       	printf("\nMasukkan Batas Pemilih Nominasi : ");
        scanf("%d", &n);
        batas[1] = n;
        if (batas[1]<batas[0])
        {
        printf("\n\nJumlah pemilih telah melebihi batas yang telah dimasukkan...");
        printf("\nTekan (Enter) untuk memasukkan input kembali...");
        getch();
        adminMenu();
        }
        break;
    case '2':
        tabel();
        break;
    case '3':
    	selesaiv();
    	break;
    case '0' :
        menu();
        break;
    default:
        printf("\nMasukkan Input yang benar !");
        printf("Tekan (Enter) untuk memasukkan kembali...");
        getch();
        adminMenu();
    }

    pemilih =  (struct dataPemilih*) malloc (n* sizeof(struct dataPemilih));
    menu();
}

void tabel()
{
    int i, input, x ;

    system("CLS");
    printf("===========================================================================\n");
    printf("No.     Nama 		Umur      Edukasi   Teknologi   Streamer    Vlog \n");
    printf("===========================================================================\n");

	for(i=0; i<sudahVote; i++)
    {

    	printf("%-5d%-20s%-11d", i+1, (pemilih+i)->nama, (pemilih+i)->umur);
    	printf("%-11d%-13d%-11d%-9d \n", (pemilih+i)->edukasi, (pemilih+i)->teknologi, (pemilih+i)->streamer, (pemilih+i)->vlog);
    }

    printf("\n\nPilih Metode Pengurutan yang diinginkan : ");
    printf("\n1.Urutkan berdasarkan Nama ");
    printf("\n2.Urutkan berdasarkan Umur");
    printf("\n3.Cari nama Pemilih");
    printf("\n4.Baca Data voting sebelumnya");
    printf("\n9.Hapus voting");
    printf("\n0.Kembali ke menu admin");
    printf("\nInput : ");
    scanf("%d", &input);

    if(input>0 && input<3)
    {
        swap(input);
    } else if (input == 3)
    {
        searching();
    } else if (input == 4)
    {
        dataSebelum();
    } else if (input == 9)
    {
        cekVote();
    }
	else if (input == 0)
	{
        adminMenu();
    } else
    {
        printf("\n\nInput anda salah....");
        printf("\nTekan (Enter) untuk memilih kembali");
        getch();
        tabel();
    }

    printf("Tekan (Enter) untuk melanjutkan.....");
    getch();
    adminMenu();
}

void dataSebelum()
{
    char p[SIZE];	// variabel untuk menyimpan data
	int a,b,c,d,e,f; // variabel untuk menyimpan data
	FILE *fileptr;

    system("CLS");
    printf("\n===========================================================================\n");
    printf("No.     Nama 		Umur      Edukasi   Teknologi   Streamer    Vlog \n");
    printf("===========================================================================\n");


	if ((fileptr = fopen ("hasil_vote.txt", "r"))==NULL)
    {
    	printf("Error, data sebelumnya tidak ditemukan");
    	exit(1);
	}
	//Membuka file jika untuk voting yang telah dilakukan sebelumnya(jika sudah dilakukan)
	while(fscanf(fileptr,"%d%s%d%d%d%d%d\n",&f,p,&a,&b,&c,&d,&e)!=EOF)
	{
	printf("%-5d%-20s%-11d%-11d%-13d%-11d%-9d\n",f,p,a,b,c,d,e);
	}

	fclose(fileptr);

	printf("Tekan {Enter) untuk kembali ke tabel vote sekarang...");
	getch();
	tabel();
}

void swap(int pilihan)
{
    int swapped, i;

    while(1)
    {
        swapped = 0;

        for(i=0; i<sudahVote-1; i++ )
        {
            if (pilihan==1) //Berdasarkan Nama Pemilih
            {
                if(strcmp((pemilih+i)->nama, (pemilih+i+1)->nama)>0)
                {
                    menukar(i);
                    swapped=1;
                }
            }
            if (pilihan==2) //Berdasarkan Umur
            {
                if((pemilih+i)->umur > (pemilih+i+1)->umur)
                {
                    menukar(i);
                    swapped=1;
                }
            }
        }
        if(swapped==0) //Jika swapping telah selesai
        {
            break;
        }
    }
    tabel();
}

void menukar(int i)
{
    char namatemp[20][20];
    int noVotetemp, umurtemp, pilihantemp[4];

     //swap nama
    strcpy(namatemp[i], (pemilih+i)->nama);
    strcpy((pemilih+i)->nama, (pemilih+i+1)->nama);
    strcpy((pemilih+i+1)->nama, namatemp[i]);
    //swap umur
    umurtemp = (pemilih+i)->umur;
    (pemilih+i)->umur = (pemilih+i+1)->umur;
    (pemilih+i+1)->umur = umurtemp;
    //swap pilihan edukasi
    pilihantemp[0] = (pemilih+i)->edukasi;
    (pemilih+i)->edukasi = (pemilih+i+1)->edukasi;
    (pemilih+i+1)->edukasi = pilihantemp[0];
    //swap pilihan teknolgi
    pilihantemp[1] = (pemilih+i)->teknologi;
    (pemilih+i)->teknologi = (pemilih+i+1)->teknologi;
    (pemilih+i+1)->teknologi = pilihantemp[1];
    //swap pilihan streamer
    pilihantemp[2] = (pemilih+i)->streamer;
    (pemilih+i)->streamer = (pemilih+i+1)->streamer;
    (pemilih+i+1)->streamer = pilihantemp[2];
    //swap pilihan vlog
    pilihantemp[3] = (pemilih+i)->vlog;
    (pemilih+i)->vlog = (pemilih+i+1)->vlog;
    (pemilih+i+1)->vlog = pilihantemp[3];

}

void searching() //Mencari nama Pemilih
{
	char cari[SIZE];
	int i;
	system("CLS");
	printf("Nama yang ingin dicari :");
	scanf ("%s",&cari);
	for (i=0;i<sudahVote;i++)
	{
		if ((strcmp((pemilih+i)->nama,cari))==0)
		{
		printf("Data yang ditemukan :\n\n");
		printf("%-5d%-20s%-11d", i+1, (pemilih+i)->nama, (pemilih+i)->umur);
    	printf("%-11d%-13d%-11d%-9d \n", (pemilih+i)->edukasi, (pemilih+i)->teknologi, (pemilih+i)->streamer, (pemilih+i)->vlog);
		}
	}
	printf("Tekan enter untuk kembali");
	getch();
	tabel();
}

void selesaiv()
{
	int i,j,k, p[SIZE] = {0};
	char input;
	int tempEdu[SIZE] = {0}, tempTekno[SIZE] = {0}, tempStream[SIZE] = {0}, tempVlog[SIZE] = {0};

	system("CLS");
	printf("\n\n");
    printf(YEL"\t                                                   `.-..```````````````.--.         \n");
    printf("\t                                        	   ::```://////////:---:.``-:        \n");
    printf("\t       _                           _              `:-   -//////////:----   .:`       \n");
    printf("\t   ___| |__   __ _ _ __ ___  _ __ (_) ___  _ __    `:-.``://///////:--:` `-:`        \n");
    printf("\t  / __| '_ \\ / _` | '_ ` _ \\| '_ \\| |/ _ \\| '_ \\     `.--::////////:-::---`          \n");
    printf("\t | (__| | | | (_| | | | | | | |_) | | (_) | | | |	  .://////:---`              \n");
    printf("\t  \\___|_| |_|\\__,_|_| |_| |_| .__/|_|\\___/|_| |_|          `-:///::-`                \n");
    printf("\t                            |_|                              -///::`                 \n");
    printf("\t                                            	     	 ````::::::::````             \n");
    printf("\t                                                      	 oo////////////oo             \n");
    printf("\t                                                       	 os:----------:ss             \n");
    printf("\t                                                       	 ////////////////             \n\n"RESET);

    if(sudahVote==0)
    {
    	printf("Silahkan mengisi jumlah pemilih terlebih dahulu");
	}
	else
	{
        //Mencari pemenang edukasi
        for(i=0; i<4; i++)
        {
        	tempEdu[0]=0;
            for(k=0; k<4; k++)
            {
                if(edu[i]>edu[k])
                    tempEdu[0]++;
            }
            if(tempEdu[0]>tempEdu[1]){
            	tempEdu[2]=i;
            	tempEdu[1]=tempEdu[0];
			}
        }
        for(i=0;i<4;i++){
            if(i!=tempEdu[2]){
                if(edu[i]==edu[tempEdu[2]]){
                    p[0]= 1;
                }
            }
        }
        if(p[0]==0)
            printf(RED"\n\t\t\tPemenang Edukasi adalah %-15s\n"RESET, kandidatEdu[tempEdu[2]]);
        else
            printf("\n\t\t\tKategori Edukasi tidak ada pemenang karena nilai seri !\n");
	}

		//Mencari pemenang Tekno
		for(i=0; i<4; i++)
        {
        	tempTekno[0]=0;
            for(k=0; k<4; k++)
            {
                if(tekno[i]>tekno[k])
                    tempTekno[0]++;
            }
            if(tempTekno[0]>tempTekno[1]){
            	tempTekno[2]=i;
            	tempTekno[1]=tempTekno[0];
			}
        }
        for(i=0;i<4;i++){
            if(i!=tempTekno[2]){
                if(tekno[i]==tekno[tempTekno[2]]){
                    p[1]= 1;
                }
            }
        }
        if(p[1]==0)
            printf(BLU"\n\t\t\tPemenang teknologi adalah %-15s\n"RESET, kandidatTekno[tempTekno[2]]);
        else
            printf("\n\t\t\tKategori teknologi tidak ada pemenang karena nilai seri !\n");

		 //Mencari Pemenang Streamer
         for(i=0; i<4; i++)
        {
        	tempStream[0]=0;
            for(k=0; k<4; k++)
            {
                if(stream[i]>stream[k])
                    tempStream[0]++;
            }
            if(tempStream[0]>tempStream[1]){
            	tempStream[2]=i;
            	tempStream[1]=tempStream[0];
			}
        }
        for(i=0;i<4;i++){
            if(i!=tempStream[2]){
                if(stream[i]==stream[tempStream[2]]){
                    p[2]= 1;
                }
            }
        }
        if(p[2]==0)
            printf(GRN"\n\t\t\tPemenang Streamer adalah %-15s\n"RESET, kandidatStream[tempStream[2]]);
        else
            printf("\n\t\t\tKategori Streamer tidak ada pemenang karena nilai seri !\n");
		//Mencari Pemenang Vlogger

		 for(i=0; i<4; i++)
        {
        	tempVlog[0]=0;
            for(k=0; k<4; k++)
            {
                if(vlogger[i]>vlogger[k])
                    tempVlog[0]++;
            }
            if(tempVlog[0]>tempVlog[1]){
            	tempVlog[2]=i;
            	tempVlog[1]=tempVlog[0];
			}
        }
        for(i=0;i<4;i++){
            if(i!=tempVlog[2]){
                if(vlogger[i]==vlogger[tempVlog[2]]){
                    p[3] = 1;
                }
            }
        }
        if(p[3]==0)
            printf(CYN"\n\t\t\tPemenang Vlogger adalah %-15s\n"RESET, kandidatVlogger[tempVlog[2]]);
        else
            printf("\n\t\t\tKategori Vlogger tidak ada pemenang karena nilai seri !\n");

	printf("\n\nApakah Anda ingin menyelesaikan Program?\n ");
	printf("(Y/N)\n\n");
	scanf(" %c",&input);

	if(input=='y' || input =='Y')
	{
		printext();
		gratitude();
	}
	else
		adminMenu();
}

void gratitude() //Modular untuk exit dari program
{
    system("CLS");
    printf("\t\t  _____        _              _           _ _           \n");
    Sleep(100);
    printf("\t\t |_   _|__ _ _(_)_ __  __ _  | |____ _ __(_) |_                \n");
    Sleep(100);
    printf("\t\t   | |/ -_) '_| | '  \\/ _` | | / / _` (_-< | ' \\              \n");
    Sleep(100);
    printf("\t\t   |_|\\___|_| |_|_|_|_\\__,_| |_\\_\\__,_/__/_|_||_|                \n");
    Sleep(100);
    printf("\t\t         _____    _      _      __  __                                   _          \n");
    Sleep(100);
    printf("\t\t        |_   _|__| |__ _| |_   |  \\/  |___ _ _  __ _ __ _ _  _ _ _  __ _| |____ _ _ _   \n");
    Sleep(100);
    printf("\t\t          | |/ -_) / _` | ' \\  | |\\/| / -_) ' \\/ _` / _` | || | ' \\/ _` | / / _` | ' \\  \n");
    Sleep(100);
    printf("\t\t          |_|\\___|_\\__,_|_||_| |_|  |_\\___|_||_\\__, \\__, |\\_,_|_||_\\__,_|_\\_\\__,_|_||_| \n");
    Sleep(100);
    printf("\t\t                  ___                          |___/|___/   _                           \n");
    Sleep(100);
    printf("\t\t                 | _ \\_ _ ___  __ _ _ _ __ _ _ __   (_)_ _ (_)                         \n");
    Sleep(100);
    printf("\t\t                 |  _/ '_/ _ \\/ _` | '_/ _` | '  \\  | | ' \\| |                        \n");
    Sleep(100);
    printf("\t\t                 |_| |_| \\___/\\__, |_| \\__,_|_|_|_| |_|_||_|_|                        \n");
    Sleep(100);
    printf("\t\t                              |___/                         \n");
    exit(0);
}

void thanks()
{
    system("CLS");
    printf("\n\n\n\n");
    printf("\t\t\t ________             __          ___             \n");
    printf("\t\t\t/_  __/ /  ___ ____  / /__ ___   / _/__  ____     \n");
    printf("\t\t\t / / / _ \\/ _ `/ _ \\/  '_/(_-<  / _/ _ \\/ __/      \n");
    printf("\t\t\t/_/ /_//_/\\_,_/_//_/_/\\_\\/___/ /_/ \\___/_/  __     \n");
    printf("\t\t\t            __ _____  __ ______  _  _____  / /____ \n");
    printf("\t\t\t           / // / _ \\/ // / __/ | |/ / _ \\/ __/ -_)\n");
    printf("\t\t\t           \\_, /\\___/\\_,_/_/    |___/\\___/\\__/\\__/ \n");
    printf("\t\t\t          /___/  \n");
    printf("\n\n\nTekan (Enter) untuk voting selanjutnya.....");
    getch();
    menu();
}

void printext()
{
	int i;
	FILE *fileptr;
	fileptr = fopen("hasil_vote.txt","w+");
	if(fileptr==NULL)
	{
		printf("Error, Tidak dapat dijalankan..");
		adminMenu();
	}
	else
	{
		for(i=0; i<sudahVote; i++)
		{
		fprintf(fileptr,"%-5d%-20s%-11d", i+1, (pemilih+i)->nama, (pemilih+i)->umur);
    	fprintf(fileptr,"%-11d%-13d%-11d%-9d \n", (pemilih+i)->edukasi, (pemilih+i)->teknologi, (pemilih+i)->streamer, (pemilih+i)->vlog);
		}
	}
	fclose(fileptr);
}

void cekVote()
{
    int i, j, hapus, pilihan;

    printf("\n\nNomor Pemilih yang ingin dihapus : ");
    scanf("%d", &hapus);
    pilihan = hapus-1;

    if(hapus>=sudahVote+1)
    {
        printf("\nPenghapusan tidak dapat dilakukan !");
        printf("\nTekan (enter) untuk melanjutkan...");
        getch();
        tabel();
    } else
    {
        edu[((pemilih+pilihan)->edukasi)-1]--;
        tekno[((pemilih+pilihan)->teknologi)-1]--;
        stream[((pemilih+pilihan)->streamer)-1]--;
        vlogger[((pemilih+pilihan)->vlog)-1]--;

        for(i=hapus-1; i<sudahVote-1; i++ )
        {
            strcpy((pemilih+i)->nama, (pemilih+i+1)->nama);
            (pemilih+i)->umur = (pemilih+i+1)->umur;
            (pemilih+i)->edukasi = (pemilih+i+1)->edukasi;
            (pemilih+i)->teknologi = (pemilih+i+1)->teknologi;
            (pemilih+i)->streamer = (pemilih+i+1)->streamer;
            (pemilih+i)->vlog = (pemilih+i+1)->vlog;
        }
    }
    batas[0]--;
    sudahVote--;
    tabel();
}
