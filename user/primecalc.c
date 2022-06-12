#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

int isPrime(int num){
    int flag=1;
    for(int i = 2; i <= num / 2; i++) {
       if(num % i == 0) {
          flag = 0;
          break;
       }
    }
    return flag;
}

int
main(int argc, char *argv[])
{
	// printf("primecalc_pocetak\n");
	//////////////////////////////////
	// get_shared provera
	// void* addr;
	// int c = get_shared("prime_arr", &addr);

	// switch (c)
	// {
	// case -1:
	// 	printf("Illegal arguments!");
	// 	break;
	// case -2:
	// 	printf("Shared structure with given name doesnt exist!\n");
	// 	break;
	// case 0:
	// 	printf("Podatak - %d na kraju\n", *(int *)(addr));
	// 	break;
	// }
	///////////////////////////////////////
	// while(1){
	// 	sleep(300);
	// 	void *addr;
	// 	get_shared("cmd", &addr);

	// 	void *ha;
	// 	get_shared("x", &ha);

	// 	printf("%d <- kco %d\n", *(int *)addr, *(int *)ha);
	// 	if(*(int *)addr == 5){
	// 		break;
	// 	}
		
	// }

	////////////////////////////////////////
		int num = 2;
		void *addr_arr;
	    get_shared("prime_arr", &addr_arr);

		void *addr_cmd;
		get_shared("cmd", &addr_cmd);
		
		void *addr_cnt;
		get_shared("cnt", &addr_cnt);

		int should_continue = 1;
		while(1){
			
			if(should_continue){
				if(isPrime(num)){
					*(((int *)addr_arr + ++(*((int *)addr_cnt)))) = num;
				}
				num++;
			}
			if(*(int *) addr_cmd == 4)
				should_continue = 1;
			if(*(int *) addr_cmd == 3 || *(int *)addr_cnt == 99999)
				should_continue = 0;
			sleep(1);
			if(*(int *) addr_cmd == 5)
				break;
		}
    
	///////////////////////////////////////

	///////////////////////////////////////
	// if(strcmp(command, "kraj\n") == 0){
	// 	void *addr;
	// 	get_shared("cmd", &addr);
	// 	*(int *)(addr) = 7;
	// 	void *addr2;
	// 	get_shared("cmd", &addr2);
	// 	printf("Nova komanda: %d\n", *(int*)addr2);
	// 	printf("Kraj\n");
	// }


	exit();
}
