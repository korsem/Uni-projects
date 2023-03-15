#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/msg.h>
#include<signal.h>
#include<unistd.h>

#define MY_MSG_SIZE 64

key_t shmkey;
int shmid;
struct my_data{
    int  typ;
    char txt[MY_MSG_SIZE];
    int likes;
    char user[16];
    int nr; //numer aktualnego posta
    int max; //maksymalna ilosc postow
}*shared_data;

static void sgnhandle(int signo) {
    if(signo == SIGINT)
    {
    	 printf("Zamykam program \n");
         if(shmdt(shared_data) != 0)
		    perror("blad shmdt");
	    if(shmctl(shmid, IPC_RMID, 0) != 0)
		    perror("blad shmctl");
	    exit(0);
    }
    else if(signo == SIGTSTP)
    {
    	printf("\n aktualne posty(%d): \n", shared_data->nr);
	    if(shared_data->nr != 0)
	    {
		    for(int i = 0; i < shared_data->nr; i++)
		    {
			    printf("[%s] : %s \n Likes: %d \n", shared_data[i].user, shared_data[i].txt, shared_data[i].likes);
		    }
	    }
	    else
	    {
		    printf("Brak postow \n");
	    }
    }
}

int main(int argc, char *argv[]) //pierwszy parametr to nazwa pliku, a drugi to maksymalna ilosc wpisow
{
    if(argc != 3)
    {
        printf("bledna ilosc parametrow\n");
        exit(1);
    }
    else
    {
	    printf("Twitter 2.0 \n");
        int n; //zminnna przechowuje maksymalna liczbe wiadmosci
        sscanf(argv[2], "%d", &n);
        if(n <= 0)
	    {
		    printf("Bledna ilosc maksymalnej ilosci wpisow jako parametr\n");
		    exit(1);
	    }
	    struct shmid_ds buf;

        signal(SIGINT, sgnhandle);
	    signal(SIGTSTP, sgnhandle);

        //tworze klucz IPC
	    shmkey = ftok(argv[1], 1);

        //tworze segment pamieci na n wpisow
        if((shmid = shmget(shmkey, n*sizeof(struct my_data), 0600 | IPC_CREAT | IPC_EXCL)) == -1)
        {
            printf("shmget error\n");
            exit(1);
        }
        shmctl(shmid, IPC_STAT, &buf);

        //dolaczam pamiec wspolna
        shared_data = (struct my_data *) shmat(shmid, (void *)0, 0);
        if(shared_data == (struct my_data *)-1)
        {
            perror("shmat \n");
            exit(1);
        }

        shared_data->typ = 0; // typ == 0 oznacza, ze nic jeszcze nie ma
	    shared_data->nr = 0; //poczatkowo jest 0 postw
	    shared_data->max = n;//w pamieci wspolnej zapisuje ile maksymalnie moze byc postow
	    while(8)
        {
            if(shared_data->typ != 0)
            {
                fflush(stdout); // trik by nadpisywanie sie udalo 
            }
            sleep(1);
        }

     }
}
