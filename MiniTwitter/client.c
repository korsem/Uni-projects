#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define MY_MSG_SIZE 64

key_t shmkey;
int  shmid;
struct my_data{
    int  typ;
    char txt[MY_MSG_SIZE];
    int  likes;
    char user[16];
    int nr; 
    int max;
} *shared_data;

char   *buf = NULL;
size_t bufsize = MY_MSG_SIZE;

void newPost(char nick[16])
{
    //funkcja wpisuje komunikat w pierwsze wolne mijsce i sychronizuje z serwerem
    if(shared_data->nr == shared_data->max)
    {
        printf("\nNie ma miejsca na twoj post \n");
        exit(0);
    }
    printf("\nCo chcesz napisac?\n");
   
    char pm[10]; //zmienna pomocnicza do czyszczenia bufora
    fgets(pm, sizeof(pm), stdin);

    //dodanie tekstu do pamieci
    getline(&buf, &bufsize, stdin);
    shared_data->typ = 1;
    buf[strlen(buf)-1] = '\0';
    strcpy(shared_data[shared_data->nr].txt, buf);

    //wpisanie do pamieci nazwy uzytkownika
    strcpy(shared_data[shared_data->nr].user,nick);

    //dodanie do pamieci numeru wpisu
    shared_data->nr++;
    shmdt(shared_data);
}
void newLike()
{
    //funkcja dodaje jeden like do podanego wpisu i synchronizuje z serwerem
    printf("\nWpisowi o ktorym numerze chcesz dodac like? ");
    int n;
    scanf("%d", &n);
    if(n <= shared_data->nr)
    {
        shared_data[n-1].likes++;
        shmdt(shared_data);
    }
    else
    {
        printf("post o takim numerze nie istnieje \n");
    }
}

int main(int argc, char *argv[]) //pierwszy parametr to nazwa pliku, a drugi to nazwa uzytkownika
{
    if(argc != 3)
    {
        printf("bledna ilosc parametrow\n");
        exit(1);
    }
    else
    {
        printf("Witam w twitter 2.0!\n\n");
   
        //tworze klucz
        shmkey = ftok(argv[1], 1);

        //otwieram segmant sieci wspolnej
        if((shmid = shmget(shmkey, 0, 0)) == -1)
        {
            perror("shmget");
            exit(1);
        }

        //dolaczenie pamieci wspolnej
        shared_data = (struct my_data *) shmat(shmid, (void *)0, 0);
        if(shared_data == (struct my_data *)-1)
        {
            perror("shmat!");
            exit(1);
        }
	
        //wyswietla informacje ile mam jeszcze wolnych postow
        printf("Wolnych %d wpisow na %d \n", shared_data->max - shared_data->nr, shared_data->max);

        //wyswietlenie aktualnych postow
        if(shared_data->typ == 0)
            printf("Brak aktualnych wpisow\n");
        else
        {
	        printf("Aktualne wpisy:\n");
	        for(int i = 0; i < shared_data->nr; i++)
		    {
			    printf("%d. [%s] : %s \nLikes: %d \n \n", i+1, shared_data[i].user, shared_data[i].txt, shared_data[i].likes);
		    }
        }
    
        //akcja uzytkownika
        printf("Wybierz akcje: (N)owy post, (L)ike \n");
        char action;
        scanf("%c",&action);
        if(action == 'N' || action == 'n')
    	{
            newPost(argv[2]);
    	}
        else if(action == 'L' || action == 'l')
        {
        	newLike();
        }
        else
        perror("Zly typ akcji\n");
    }
return 0;
}