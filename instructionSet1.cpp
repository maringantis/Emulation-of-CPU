#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>

int PC,MAR,MDR;
int reg[8];
int mmemory[10];


/*	Integer array as memory address
	Array as Register file 
*/


void boot_init()
{	printf("\n____   ______   _____  _______        _____  _____   _    _   \n|  _ \ |  ____| / ____||__   __|      / ____||  __ \ | |  | |  \n| |_) || |__   | (___     | | ______ | |     | |__) || |  | |  \n|  _ < |  __|   \___ \    | ||______|| |     |  ___/ | |  | |  \n| |_) || |____  ____) |   | |        | |____ | |     | |__| |  \n|____/ |______||_____/    |_|         \_____||_|      \____/   \n \nBOOTING ");
    //sleep(2);
    mmemory[1] = 8; 
    

}

//void loadImmediate(char *lw)
void Imload(char *ld)
{

/*	loading immediate value to register and load memory address to register */
	printf("\nLoad immediate instruction executing%s\n",ld);
	//sleep(2);
	int reg_num;
        char *load = strtok(ld, " ");
	char *data = strtok(NULL, " ");
  	if (!data)
    	    data = "";
	char *reg_str = strtok(data, ",");
	char *val_str = strtok(NULL, " ");
	if(!val_str)
	    val_str="";
	reg_num = reg_str[0] - 'A';
	//atoi converts string to interger
	reg[reg_num] = atoi(val_str);

}
void loadWord(char *lw)
{
/*	load value from memory address to register */
	printf("\nLoad word instruction executing%s\n", lw);
	//sleep(2);
        int reg_numsrc, reg_numdest,loc;
        char *lwload = strtok(lw, " ");
        char *lwdata = strtok(NULL, " ");
        if (!lwdata)
            lwdata = "";
        char *reg_strdest = strtok(lwdata, ",");
        char *reg_strsrc = strtok(NULL, " ");
        if(!reg_strsrc)
            reg_strsrc="";
        reg_numsrc = reg_strsrc[0] - 'A';
	reg_numdest = reg_strdest[0] - 'A';
        loc = reg[reg_numsrc];
	reg[reg_numdest] = mmemory[loc];
}

void store(char *sr)
{
/*	store value from register to memory address */
	printf("\nstore instruction executing%s\n",sr);
	//sleep(2);
	int reg_numsrc, reg_numdest,loc, val;
        char *srload = strtok(sr, " ");
        char *srdata = strtok(NULL, " ");
        if (!srdata)
            srdata = "";
        char *sr_regstrsrc = strtok(srdata, ",");
        char *sr_regstrdest = strtok(NULL, " ");
        if(!sr_regstrdest)
            sr_regstrdest="";
        reg_numsrc = sr_regstrsrc[0] - 'A';
        reg_numdest = sr_regstrdest[0] - 'A';
	val = reg[reg_numsrc];
	loc = reg[reg_numdest];
	mmemory[loc]=val;
}




 /* Addition logic*/
int add_logic(int a, int b)
{
         // Iterate till there is no carry  
                 while (b != 0)
                 {
        // carry now contains common set bits of x and y
                        int carry = a & b;

        // Sum of bits of x and y where at least one of the bits is not set
                        a = a ^ b;

        // Carry is shifted by one so that adding it to x gives the required sum
                         b = carry << 1;
                 } 

            return a;
}






void Add(char *add)
{
        int S, T, sum;

/*      values provided in the  register */
        printf("\nADD instruction executing%s\n", add);
        //sleep(2);
        /* Parsing instrcution */
        int reg_numsrc, reg_numdest,loc;
        char *add_key = strtok(add, " ");
        char *add_data = strtok(NULL, " ");
        if (!add_data)
            add_data = "";
        char *reg_strdest = strtok(add_data, ",");
        char *reg_strsrc = strtok(NULL, " ");
        if(!reg_strsrc)
            reg_strsrc="";
        reg_numsrc = reg_strsrc[0] - 'S';
        reg_numdest = reg_strdest[0] - 'S';
        S = reg[reg_numsrc];
        S = reg[reg_numdest];
	sum = add_logic(S, T);
	reg[reg_numdest] = sum;
	printf("result value %d\n",sum);

}





void Multiplication(char *mul)
{
	int S, T, product;

/*      values provided in the  register */
        printf("\nMultiply instruction executing%s\n", mul);
        //sleep(2);
	/* Parsing instrcution */
        int reg_numsrc, reg_numdest,loc;
        char *mul_key = strtok(mul, " ");
        char *mul_data = strtok(NULL, " ");
        if (!mul_data)
            mul_data = "";
        char *reg_strdest = strtok(mul_data, ",");
        char *reg_strsrc = strtok(NULL, " ");
        if(!reg_strsrc)
            reg_strsrc="";
        reg_numsrc = reg_strsrc[0] - 'S';
        reg_numdest = reg_strdest[0] - 'T';
	S = reg[reg_numsrc];
	T = reg[reg_numdest];
	/*Multiplication logic*/
	product=0;
   	while(T != 0)               // Iterate the loop till b==0
  	{
        	if (T&01)                // Bitwise &  of the value of b with 01
      		{
         		 product=add_logic(product,S);     // Add a to result if b is odd .
      		}
       		S<<=1;                   // Left shifting the value contained in 'a' by 1 
                                // multiplies a by 2 for each loop
       		T>>=1;                   // Right shifting the value contained in 'b' by 1.
  	}
   		printf("nResultmultiply:%d\n",product);
	
	reg[reg_numdest] = product;

} 

void data_print()
{
	int i =0,len,memlen;
	len = sizeof(reg)/sizeof(reg[0]);
	memlen = sizeof(mmemory)/sizeof(mmemory[0]);

/*	Print the register and memory layout after the load and store instruction*/	
	for(i = 0;i <len; i++)
	{
		printf("R[%d] = %d\n",i,reg[i]);
	}
	for(i=0; i<memlen; i++)
	{
		printf("mmemory[%d] = %d\n",i,mmemory[i]);
	}
}

int main()
{
/*	Booting the system*/
	
	boot_init();
	printf("\nThe register values before instruction execution\n");
	data_print();
	char *str;
        str =   (char *) malloc ( 34 + 1 );
	char line[34];
	FILE *fp;
	int n;
	printf("\n********The instructions are read from text file*******\n");
	//sleep(2);

/*	Open the file in read mode where instructions are stored*/
	fp = fopen("instructionSet.txt","r"); // read` mode
	if( fp == NULL )
  	{
/*	If the file is not present, error message is displayed*/
     		 perror("Error while opening the file.\n");
      		 exit(EXIT_FAILURE);
  	}
 
/*	read instructions from file and parse the instruction*/ 
  	 while( fgets(line, 34, fp) != NULL )
       	 {
		 if(!(strncmp("li",line,2)))
		 {
			strcpy(str,line);
			Imload(str);
		 }
		 else if(!(strncmp("ld",line,2)))
                 {
                        strcpy(str,line);
                        loadWord(str);
                 }
		 else if(!(strncmp("sd",line,2)))
		 {
			strcpy(str,line);
			store(str);
		 }
		 else if(!(strncmp("mul",line,2)))
          	 {
			strcpy(str,line);
			Multiplication(str);
		 }
		 else if(!(strncmp("add",line,2)))
		 {
			strcpy(str,line);
			Add(str);
		 }
		 else
		 {
/*	Error handling for wrong instruction format*/
			printf("Wrong instruction entered\n");
			exit(0);
	         }
	}

	fclose(fp);
	//sleep(2);
	printf("\nThe registers and memory values after instruction execution\n");
	data_print();
return 0;
}
