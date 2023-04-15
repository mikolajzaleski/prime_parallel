default:
	gcc -fopenmp  -g parallel_div.c -o eratostenes_par_div.a -O0 -lm
	gcc -fopenmp  -g parallel_add.c -o eratostenes_par_add.a -O0 -lm
	gcc -fopenmp  -g seq_add.c -o eratostenes_seq_add.a -O0 -lm
	gcc -fopenmp  -g seq_div.c -o eratostenes_seq_div.a -O0 -lm
intel:
	icx -fopenmp -g parallel_div.c -o eratostenes_par_div.a -O0
	icx -fopenmp -g parallel_add.c -o eratostenes_par_add.a -O0
	icx -fopenmp -g seq_add.c -o eratostenes_seq_add.a -O0
	icx -fopenmp -g seq_div.c -o eratostenes_seq_div.a -O0