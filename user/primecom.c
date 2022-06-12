#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"


int
main(int argc, char *argv[])
{
	// printf("primecom_pocetak\n");
	// 	//////////////////////////////////
	// // get_shared provera
	// int* addr;
	// int c = get_shared("cmd", &addr);

	// switch (c)
	// {
	// case -1:
	// 	printf("Illegal arguments!");
	// 	break;
	// case -2:
	// 	printf("Shared structure with given name doesnt exist!\n");
	// 	break;
	// case 0:
	// 	printf("Podatak - %d na kraju\n", *(addr));
	// 	break;
	// }
	// ///////////////////////////////////////	
	printf("Commands:\nprime <n>\nlatest\npause\nresume\nend\n");
	
	while(1){
		char command[100] = {};
		gets(command, 100);
		char prvi[10] = {};
		char drugi[100] = {};
		int broj = 0;
		int ii = 0;
		int jj = 0;
		for(int i = 0; i < 100; i++){
			if(broj)
				drugi[jj++] = command[i];
			else{
				if(command[i] != '\n' || command[i] != ' ')
					prvi[ii++] = command[i];
			}
			if(command[i] == ' ')
				broj = 1;
			if(command[i] == '\n')
				break;
		}


		void *addr;
		get_shared("cmd", &addr);

		void *addr_arr;
		get_shared("prime_arr", &addr_arr);
		
		void *addr_cnt;
		get_shared("cnt", &addr_cnt);

		if(strcmp(prvi, "prime\n") == 0 || strcmp(prvi, "prime ") == 0 || strcmp(prvi, "prime") == 0){

			void *ha;
			get_shared("x", &ha);
			if(atoi(drugi) > 0)
				*(int *)ha = atoi(drugi);
			
			*(int *) addr = 1;


			if(*(int *)addr_cnt < atoi(drugi))
				printf("Still havent calculated prime no. %d. We have primes up to %d\n", atoi(drugi), *(int *)addr_cnt);
			else
				printf("Prime no. %d is %d\n", atoi(drugi), *(((int *)addr_arr + atoi(drugi))));
		}
		if(strcmp(prvi, "latest\n") == 0){
			*(int *) addr = 2;
			printf("Latest prime is no. %d, value: %d\n", *(int *)addr_cnt, *(((int *)addr_arr+(*((int *)addr_cnt)))));		
		}
		if(strcmp(prvi, "pause\n") == 0){
			printf("Pausing...\n");
			*(int *) addr = 3;
		}
		if(strcmp(prvi, "resume\n") == 0){
			printf("Resuming...\n");
			*(int *) addr = 4;
		}
		if(strcmp(prvi, "end\n") == 0){
			*(int *) addr = 5;
			break;
		}
		
	}
	exit();
}
