default:
	gcc -fopenmp  -g parallel_div.c -o par_div.out -O3 -lm
	gcc -fopenmp  -g seq_add.c -o seq_add.out -O3 -lm
	gcc -fopenmp  -g seq_div.c -o seq_div.out -O3 -lm
	gcc -fopenmp  -g function_add.c -o function_add.out -O3 -lm
	gcc -fopenmp  -g domain_add.c -o domain_add.out -O3 -lm

intel:
	icx -fopenmp  -g parallel_div.c -o par_div.out -O3 -lm
	icx -fopenmp  -g seq_add.c -o seq_add.out -O3 -lm
	icx -fopenmp  -g seq_div.c -o seq_div.out -O3 -lm
	icx -fopenmp  -g function_add.c -o function_add.out -O3 -lm
	icx -fopenmp  -g domain_add.c -o domain_add.out -O3 -lm
