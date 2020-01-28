#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int  argtonum(char * arg, int len){
	int i, num = 0, currnum = 0,m;

	m = 1;

	
	for (i = len-1; i >= 0; i--){
		num = num + (arg[i]-48) * m;
		m *= 10;
	}
	return num; 
}


int * dectobin(int decimal){

	int currbin, currbinary[32], currbinlen, i, m, number = 0;
    int *binary = (int*) malloc(32 * sizeof(int));

 	i=0;
 for(decimal; decimal/2 > 0 ; decimal/=2){
 	if (decimal % 2 == 1){
   		currbinary[i] = 1;
  	}
 	 else currbinary[i] = 0;
  		i++;
	 }
 if (decimal % 2 == 1) {currbinary[i] = 1;}
 else currbinary[i] = 0;

i++;
currbinlen = i;
currbin = i-1;

for(i= 0; i<32;i++ )
	 {
  	if (i < 32-currbinlen) {
   	binary[i] = 0;
  }
  else { binary[i] = currbinary[currbin]; currbin--;}
 }

 	return  binary;
}

int * bintoip(int binary[]){
	int *ip = (int*) malloc(4 * sizeof(int));
	int num = 0, y[] = {128,64,32,16,8,4,2,1}, i, j;
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 8; j++){
			num = num + y[j] * binary[8*i+j];
		}
		ip[i] = num;
		num = 0;
	}

	return ip;

}

char * bintohex(int binary[]){
	char *hex = (char*) malloc(8 * sizeof(char));
	int i, j, num = 0, y[] = {8,4,2,1};

	for(i = 0; i < 8; i++){
		for(j = 0; j < 4; j++){
			num = num + y[j] * binary[4*i+j];
		}
		switch(num){
			case 10 :
				hex[i] = 'A';
				break;
			case 11 :
				hex[i] = 'B';
				break;
			case 12 :
				hex[i] = 'C';
				break;
			case 13 : 
				hex[i] = 'D';
				break;
			case 14 :
				hex[i] = 'E';
				break;
			case 15 : 
				hex[i] = 'F';
				break;
			default :
				hex[i] = num + '0';
		}
		num = 0;
	}

	return hex;
}




int main(int argc, char * argv[]) {
	int decimal,argvlen=0, i, j, IPbinary[32];
	int* binary;
	int* ip;
	char * hex;

/* CHECKING ARGUMENTS*/
if (argc > 2) {
	printf("Too many arguments\n");
	exit(5);
}
else if (argc < 2) {
	printf("One argument expected\n");
	exit(4);
	}

argvlen = strlen(argv[1]);

if (argvlen > 10) { printf("Wrong decimal number\n"); exit(6);}

/*PASSING ARGUMENT TO GET NUMBER VERSION OF IT*/
decimal = argtonum(argv[1],argvlen);
printf("DECIMAL : %d\n",decimal);

if (decimal > 4294967295) {printf("Too big number\n");exit(7); }

/*DECIMAL TO BINARY*/
binary = dectobin(decimal);

printf("BINARY  : ");

for(i = 0; i < 32; i++){
	if ((i % 8 == 0) && (i != 31) && (i != 0)){printf(".");}
	printf("%d",binary[i]);
}

printf("\n");

/*BINARY TO IP*/
ip = bintoip(binary);

printf("IP      : ");

for(i = 0; i < 4; i++)
	if (i != 3)
		printf("%d.",ip[i]);
	else printf("%d\n",ip[i]);

/*BINARY TO HEX*/
hex = bintohex(binary);

printf("HEX     : ");

for(i=0; i <= 7; i+=2 ) {
	if(i == 6) {printf("%c%c",hex[i],hex[i+1]);}
	else printf("%c%c.",hex[i],hex[i+1]);
}
printf("\n");


	return 0;
}
