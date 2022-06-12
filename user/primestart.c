#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

int
main(int argc, char *argv[])
{
	int *prime_arr = malloc(100000*sizeof(int));
	int cnt = -1;
	int cmd = 0;
	
	share_mem("prime_arr", prime_arr, 100000*sizeof(int));
	share_mem("cnt", &cnt, sizeof(cnt));
	share_mem("cmd", &cmd, sizeof(cmd));

	int pid = fork();

	if(pid == 0){
		char *argv2[] = {"/bin/primecalc", 0};
		exec("/bin/primecalc", argv2);
	}else{
		int pid2 = fork();
		if(pid2 == 0){
			char *argv3[] = {"/bin/primecom", 0};
			exec("/bin/primecom", argv3);
		}else{
			wait();	
			wait();
		}
	}
	exit();
}
