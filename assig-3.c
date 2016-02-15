#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 10


/* Function for booting the system*/
void bootup()
{
printf(" \n____   ______   _____  _______        _____  _____   _    _   \n|  _ \ |  ____| / ____||__   __|      / ____||  __ \ | |  | |  \n| |_) || |__   | (___     | | ______ | |     | |__) || |  | |  \n|  _ < |  __|   \___ \    | ||______|| |     |  ___/ | |  | |  \n| |_) || |____  ____) |   | |        | |____ | |     | |__| |  \n|____/ |______||_____/    |_|         \_____||_|      \____/   \n  ");
printf("\n \n \n  \t \t \t \t BOOTING....");
sleep(5);
system("cls"); 
printf(" \n____   ______   _____  _______        _____  _____   _    _   \n|  _ \ |  ____| / ____||__   __|      / ____||  __ \ | |  | |  \n| |_) || |__   | (___     | | ______ | |     | |__) || |  | |  \n|  _ < |  __|   \___ \    | ||______|| |     |  ___/ | |  | |  \n| |_) || |____  ____) |   | |        | |____ | |     | |__| |  \n|____/ |______||_____/    |_|         \_____||_|      \____/   \n  ");
printf("\n \n \n  \t \t \t \t Initializing....");
sleep(2);
system("cls");
sleep(1);
printf(" \n____   ______   _____  _______        _____  _____   _    _   \n|  _ \ |  ____| / ____||__   __|      / ____||  __ \ | |  | |  \n| |_) || |__   | (___     | | ______ | |     | |__) || |  | |  \n|  _ < |  __|   \___ \    | ||______|| |     |  ___/ | |  | |  \n| |_) || |____  ____) |   | |        | |____ | |     | |__| |  \n|____/ |______||_____/    |_|         \_____||_|      \____/   \n  \n \n");
sleep(1);
	
};

/*CPU registers*/
struct registers{
	int r[10];
//	int r1[10]=[10,20,30,40,50,60];
	int *MAR;
	int MDR;
	char **PC;
}reg;
void binary_search(int [], int, int, int);
void bubble_sort(int [], int);

int r1[10]={10,20,30,40,50,60};

void bubble_sort(int list[], int size)
{
    int temp, i, j;
    for (i = 0; i < size; i++)
    {
        for (j = i; j < size; j++)
        {
            if (list[i] > list[j])
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}
 
void binary_search(int list[], int lo, int hi, int key)
{
    int mid;
 
    if (lo > hi)
    {
        printf("Key not found\n");
        return ;
    }
    mid = (lo + hi) / 2;
    if (list[mid] == key)
    {
        printf("Key found\n");
        sleep(2);
    }
    else if (list[mid] > key)
    {
        binary_search(list, lo, mid - 1, key);
        
    }
    else if (list[mid] < key)
    {
        binary_search(list, mid + 1, hi, key);
        
    }
}


/*Structure for storing opcode and operands*/
struct operations{
	char opcode[5];
	char op_1[8];
	char op_2[8];
	char op_3[8];
}op;

/*Stack for storing functons*/
struct stack{
	int stk[SIZE];
	int top;
};

typedef struct stack STACK;
STACK s;

int count=0; // total number of instructions in instruction memory
int i;
//int remainder;
int mem[100]={0}; // Memory block represented in array
char *instr_mem[30]; // Instruction memory to store instructions

/*Displaying the CPU registers*/
void val_disp()
{
	printf("\n********REGISTERS Values**********\n");
	printf("\n-------------------------\n|\tr[0] = %d\t|\n-------------------------\n|\tr[1] = %d\t|\n-------------------------\n|\tr[2] = %d\t|\n-------------------------\n|\tr[3] = %d\t|\n-------------------------\n|\tr[4] = %d\t|\n-------------------------\n|\tr[5] = %d\t|\n-------------------------\n|\tr[6]= %d\t\t|\n-------------------------\n|\tr[7] = %d\t|\n-------------------------\n|\tr[8]=%d\t\t|\n-------------------------\n|\tMAR = %p\t|\n-------------------------\n|\tMDR = %d\t\t|\n-------------------------\n|\tPC = %p\t|\n-------------------------\n", reg.r[0],reg.r[1],reg.r[2],reg.r[3],reg.r[4],reg.r[5],reg.r[6],reg.r[7],reg.r[8],reg.MAR,reg.MDR,reg.PC);
	printf("\n<************REGISTERS Values********>\n");
	
	
}

/*Loading from memory*/
void mem_load()
{
	int x,a;
	char ch[2];
	char str[1];	
	ch[0]=op.op_2[4];
	ch[1]=op.op_2[5];
	ch[2]='\0';
	x=atoi(ch);
	if(op.op_1[0]=='M' ||op.op_1[0]=='m' )
	{
		reg.MAR= &mem[x];
		reg.MDR= mem[x];
		printf("\nLoading from memory\n");
		printf("\nMAR-->%p\t MDR--->%d\t mem[%d] = %d\n\n",reg.MAR, reg.MDR, x, mem[x]);	
		return;
	}
	else if(op.op_1[0]=='r')
	{
		str[0]=op.op_1[2];
		str[1]='\0';
		a=atoi(str);		
		reg.MAR=&mem[x];
		reg.r[a]= mem[x];
		printf("\nLoading from memory\n");
		printf("\nMAR-->%p\t reg[%d]--->%d\t mem[%d] = %d\n\n",reg.MAR,a, reg.r[a], x, mem[x]);
		return;	
	}
			
}

/*storing into memory*/
void mem_store()
{
	int x,a;
	char ch[2],str[1];
	ch[0]=op.op_1[4];
	ch[1]=op.op_1[5];
	ch[2]='\0';
	x=atoi(ch);
	if(op.op_2[0]=='m' || op.op_2[0]=='M' )
	{
		reg.MAR= &mem[x];
		mem[x]=reg.MDR;
		printf("\nStoring to memory-------->\n");
		printf("\nMAR-->%p\t MDR--->%d\t mem[%d] = %d\n\n",reg.MAR, reg.MDR, x, mem[x]);
		return;
	}
	else if(op.op_2[0]=='r' )
	{
		str[0] = op.op_2[2];
		str[1]='\0';
		a= atoi(str);
		reg.MAR= &mem[x];
		mem[x] = reg.r[a];
		printf("\nMAR-->%p\t reg[%d]--->%d\t mem[%d] = %d\n\n",reg.MAR,a, reg.r[a], x, mem[x]);
		return;	
	}
	
}

/*pushing values into stack*/
void push_stack()
{
	int x;
	char ch[1];
	ch[0]=op.op_1[2];
	ch[1]='\0';
	
    	if (s.top == (SIZE -1)) {
        	printf("End of Stack\n");
    	} else{
		x= atoi(ch);
			
		s.top=s.top+1;    		
		s.stk[s.top] = reg.r[x];
		printf("\n\npush_stacking--->r[%d] = %d",x,s.stk[s.top]);	
	}
}

int pop_stack()
{
    if (s.top == -1){
    printf("End of Stack\n");
    } else
        return s.stk[s.top];
}

/*Load immediate (li) for initialising registers*/
void init()
{
	char ch[1];
	char ch1[4];
	int x,y;
	ch[0]=op.op_1[2];
	ch[1]='\0';
	x=atoi(ch);
	y=atoi(op.op_2);
	
	reg.r[x]=y;
	
	printf("Result :\t r[%d]=%d\n\n",x,reg.r[x]);
	return;
	
}

void load_effective_address()
{
	int *p,a,x,y;
	char ch[2],str[1];
	ch[0]=op.op_2[4];
	ch[1]=op.op_2[5];
	ch[2]='\0';
	x=atoi(ch);
	str[0]=op.op_1[2];
	str[1]='\0';
	y=atoi(str);
	if(op.op_2[0]=='M' ||op.op_2[0]=='m' )
	{
		p= &mem[x];
		reg.r[y]=(size_t)p;
		printf("\nLoading effective address\n");
		printf("\nr[%d] = %d \t addr_mem[%d] = %d\n\n",y,reg.r[y], x, reg.r[y]);	
		return;
	}
}
/*Load, Store, push_stack and pop_stack operations*/
void memory_operations()
{
	if (strcmp(op.opcode, "ld") == 0) 
	{
			mem_load();
			return;
 	}
	else if (strcmp(op.opcode, "sd") == 0)
	{
			mem_store();
			return;
	}
	else if (strcmp(op.opcode, "push") == 0)
	{
		push_stack();
		return;
	}
	else if (strcmp(op.opcode, "pop") == 0)
	{
		printf("\npop_stacked item----->%d",pop_stack());
		s.top--;
		return;
	}
	else if(strcmp(op.opcode, "LEA")==0)
	{
		
		load_effective_address();
		return;
	}
	else  
	{ 
		printf("Sorry Not all Instructions defined yet\n");
		return;
	}
}


void add_oper()
{
	char ch_1[1];
	char ch_2[1];
	char ch_3[1];
	unsigned int carry;
	unsigned int sum;
	int a_1, a_2, a_3;
	int temp;
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a_1=atoi(ch_1);
	
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	a_2=atoi(ch_2);	
	temp=reg.r[a_2];
	ch_3[0]=op.op_3[2];
	ch_3[1]='\0';
	a_3=atoi(ch_3);
	sum = reg.r[a_2] ^ reg.r[a_3];
	carry = reg.r[a_2] & reg.r[a_3];
	
	while(carry!=0)
	{
		carry=carry<<1;
		int x=sum;
		int y=carry;
		sum=x^y;
		carry=x&y;
	}
	reg.r[a_1]= sum;	
	
	printf("\nr[%d]=%d  + r[%d]=%d = r[%d]=%d \t carry = %d\n",a_2, temp, a_3, reg.r[a_3], a_1, reg.r[a_1],carry);
	
	if(reg.r[a_1] > 2147483647)
		printf("overflow occurs\n");
	else 
		printf("no overflow\n");	
	
	return;
}
int add_logic(int c,int d)
{
	int sum=c^d;
	int carry=c&d;
	while(carry!=0)
	{
		carry=carry<<1;
		int x=sum;
		int y=carry;
		sum=x^y;
		carry=x&y;
	}
	return sum;
}

void subtract()
{
	char ch_1[1];
	char ch_2[1];
	char ch_3[1];
	int result;
	int sum;
	int a_1, a_2, a_3, b,a;
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a_1=atoi(ch_1);
	
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	a_2=atoi(ch_2);	
	
	ch_3[0]=op.op_3[2];
	ch_3[1]='\0';
	a_3=atoi(ch_3);
	
        b=reg.r[a_3];
	a=reg.r[a_2];
	result=add_logic(~b,1);
	printf("%d\n",result);
	sum=add_logic(a,result);
	reg.r[a_1]=sum;
	printf("\nr[%d]=%d  - [%d]=%d = r[%d]=%d \n",a_2, reg.r[a_2], a_3, reg.r[a_3], a_1, reg.r[a_1]);
	return;
}

void multiplication()
{
	char ch_1[1];
	char ch_2[1];
	char ch_3[1];
	int array[10];
	int result;
	static int i=1;
	int sum;
	int j=1;
	int a_1, a_2, a_3, b,a;
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a_1=atoi(ch_1);
	
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	a_2=atoi(ch_2);	
	
	ch_3[0]=op.op_3[2];
	ch_3[1]='\0';
	a_3=atoi(ch_3);
	
	a= reg.r[a_2];
	b= reg.r[a_3];
	
	/* multiplication logic*/
	if((a&1)!=0)
 	{
   		array[0]=b;
  	}
	else
	{ 
		array[0]=0;
	}
	while(a>1)
  	{
   		a=a>>1;
		b=b<<1;
  	 	if((a&1)!=0)
  	   	{
  	    		array[i]=b;
  	    		i++;
  	   	}
  	}

	for(j=1;j<i;j++)
  	{	
   		result=add_logic(array[0],array[j]);
  	}
	
	reg.r[a_1]= result;
	printf("\nr[%d]=%d * [%d]=%d = r[%d]=%d \n",a_2, reg.r[a_2], a_3, reg.r[a_3], a_1, reg.r[a_1]);
	return;
	
}

/*int divi(int tempdividend, int tempdivisor) {

     int quotient = 1;

     if (tempdivisor == tempdividend) {
        remainder = 0;
        return 1;
     } else if (tempdividend < tempdivisor) {
        remainder = tempdividend;
        return 0;
     }   

    do{

        tempdivisor = tempdivisor << 1;
        quotient = quotient << 1;

     } while (tempdivisor <= tempdividend);

     quotient = quotient + divi(tempdividend - tempdivisor, reg.r[]);

     return quotient;
 }*/ 

/*void division()*/
/*{
	char ch_1[1];
	char ch_2[1];
	char ch_3[1];
	int array[10];
	int quotient;
	static int i=1;
	int s;
	int a_1, a_2, a_3, b,a;
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a_1=atoi(ch_1);
	
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	a_2=atoi(ch_2);	
	
	ch_3[0]=op.op_3[2];
	ch_3[1]='\0';
	a_3=atoi(ch_3);
	
	a= reg.r[a_2];
	b= reg.r[a_3];
	
	quotient = divi(a,b);

	reg.r[a_1]= quotient;
	printf("\nr[%d]=%d / [%d]=%d = r[%d]=%d \n",a_2, reg.r[a_2], a_3, reg.r[a_3], a_1, reg.r[a_1]);
	return;
		
}*/
void modulus()
{
	char ch_1[1];
	char ch_2[1];
	char ch_3[1];
	int array[10];
	int result;
	static int i=1;
	int s;
	int a_1, a_2, a_3, b,a;
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a_1=atoi(ch_1);
	
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	a_2=atoi(ch_2);	
	
	ch_3[0]=op.op_3[2];
	ch_3[1]='\0';
	a_3=atoi(ch_3);
	
	a= reg.r[a_2];
	b= reg.r[a_3];
	s=a&b-1;
	reg.r[a_1]= s;
	printf("\nr[%d]=%d mod [%d]=%d = r[%d]=%d \n",a_2, reg.r[a_2], a_3, reg.r[a_3], a_1, reg.r[a_1]);
	return;
	
}

/*Arithmetic operations*/
void ALU_operations()
{
	if (strcmp(op.opcode, "add") == 0) 
	{
			add_oper();
			return;
 	}
	else if (strcmp(op.opcode, "sub") == 0) 
	{
			subtract();
			return;
 	}
	else if (strcmp(op.opcode, "mul") == 0) 
	{
			multiplication();
			return;
 	}
	else if (strcmp(op.opcode, "mod") == 0) 
	{
			modulus();
			return;
 	}	
	else if (strcmp(op.opcode, "div") == 0) 
	{
			//division();
			return;
 	}
	
}

int beq()
{
	int a,b;
	int temp;	
	int val_1,val_2,x,y;
	char ch_1[1];
	char ch_2[1];
	
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a= atoi(ch_1);
	x=a;	
	val_1=reg.r[a];
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	b= atoi(ch_2);
	y=b;	
	val_2=reg.r[b];	

	reg.r[x]=val_1;
	reg.r[y]=val_2;
	printf("\nr[%d]= %d \t r[%d] = %d \n",x,reg.r[x],y,reg.r[y]);
	val_disp();	
	if(val_1 == val_2)
	{
		printf("\nbeq r[%d]= %d, r[%d] = %d, end;\n",x,reg.r[x],y,reg.r[y]);
		printf("\n****Branch equal (beq) is true ------>go out of the loop****\n\n");
		return 1;
	}	
	else 
		return 0;
	
}

int bne()
{
	int a,b;
	int temp;	
	int val_1,val_2,x,y;
	char ch_1[1];
	char ch_2[1];
	
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a= atoi(ch_1);
	x=a;	
	val_1=reg.r[a];
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	b= atoi(ch_2);
	y=b;	
	val_2=reg.r[b];	

	reg.r[x]=val_1;
	reg.r[y]=val_2;
	printf("\nr[%d]= %d \t r[%d] = %d \n",x,reg.r[x],y,reg.r[y]);
	val_disp();	
	if(val_1 != val_2)
	{
		printf("\nbeq r[%d]= %d, r[%d] = %d, end;\n",x,reg.r[x],y,reg.r[y]);
		printf("\n****Branch not equal (bne) is true ------>go out of the loop****\n\n");
		return 1;
	}	
	else 
		return 0;
	
}

int bgez()
{
	int a,b;
	int temp;	
	int val_1,val_2,x,y;
	char ch_1[1];
	char ch_2[1];
	
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a= atoi(ch_1);
	x=a;	
	val_1=reg.r[a];
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	b= atoi(ch_2);
	y=b;	
	val_2=reg.r[b];	

	reg.r[x]=val_1;
	reg.r[y]=val_2;
	printf("\nr[%d]= %d \t r[%d] = %d \n",x,reg.r[x],y,reg.r[y]);
	val_disp();	
	if(val_1 >= 0)
	{
		printf("\nbeq r[%d]= %d, r[%d] = %d, end;\n",x,reg.r[x],y,reg.r[y]);
		printf("\n****Branch not equal (bne) is true ------>go out of the loop****\n\n");
		return 1;
	}	
	else 
		return 0;
	
}

int bge()
{
	int a,b;
	int temp;	
	int val_1,val_2,x,y;
	char ch_1[1];
	char ch_2[1];
	
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a= atoi(ch_1);
	x=a;	
	val_1=reg.r[a];
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	b= atoi(ch_2);
	y=b;	
	val_2=reg.r[b];	

	reg.r[x]=val_1;
	reg.r[y]=val_2;
	printf("\nr[%d]= %d \t r[%d] = %d \n",x,reg.r[x],y,reg.r[y]);
	val_disp();	
	if(val_1 >= val_2)
	{
		printf("\nbeq r[%d]= %d, r[%d] = %d, end;\n",x,reg.r[x],y,reg.r[y]);
		printf("\n****Branch not equal (bne) is true ------>go out of the loop****\n\n");
		return 0;
	}	
	else 
		return 1;
	
}

int blez()
{
	int a,b;
	int temp;	
	int val_1,val_2,x,y;
	char ch_1[1];
	char ch_2[1];
	
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a= atoi(ch_1);
	x=a;	
	val_1=reg.r[a];
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	b= atoi(ch_2);
	y=b;	
	val_2=reg.r[b];	

	reg.r[x]=val_1;
	reg.r[y]=val_2;
	printf("\nr[%d]= %d \t r[%d] = %d \n",x,reg.r[x],y,reg.r[y]);
	val_disp();	
	if(val_1 <= 0)
	{
		printf("\nbeq r[%d]= %d, r[%d] = %d, end;\n",x,reg.r[x],y,reg.r[y]);
		printf("\n****Branch not equal (bne) is true ------>go out of the loop****\n\n");
		return 1;
	}	
	else 
		return 0;
	
}


int bgtz()
{
	int a,b;
	int temp;	
	static int zero=0;
	int val_1,val_2,x,y;
	char ch_1[1];
	char ch_2[1];
	
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a= atoi(ch_1);
	x=a;	
	val_1=reg.r[a];
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	b= atoi(ch_2);
	y=b;	
	val_2=reg.r[b];	

	reg.r[x]=val_1;
	reg.r[y]=val_2;
	printf("\nr[%d]= %d \t r[%d] = %d \n",x,reg.r[x],y,reg.r[y]);
	val_disp();	
	if(val_1 > zero)
	{
		printf("\nbeq r[%d]= %d, r[%d] = %d, end;\n",x,reg.r[x],y,reg.r[y]);
		printf("\n****Branch not equal (bne) is true ------>go out of the loop****\n\n");
		return 1;
	}	
	else 
		return 0;
	
}

int bltz()
{
	int a,b;
	int temp;	
	static int zero=0;
	int val_1,val_2,x,y;
	char ch_1[1];
	char ch_2[1];
	
	ch_1[0]=op.op_1[2];
	ch_1[1]='\0';
	a= atoi(ch_1);
	x=a;	
	val_1=reg.r[a];
	ch_2[0]=op.op_2[2];
	ch_2[1]='\0';
	b= atoi(ch_2);
	y=b;	
	val_2=reg.r[b];	

	reg.r[x]=val_1;
	reg.r[y]=val_2;
	printf("\nr[%d]= %d \t r[%d] = %d \n",x,reg.r[x],y,reg.r[y]);
	val_disp();	
	if(val_1 < zero)
	{
		printf("\nbeq r[%d]= %d, r[%d] = %d, end;\n",x,reg.r[x],y,reg.r[y]);
		printf("\n****Branch not equal (bne) is true ------>go out of the loop****\n\n");
		return 1;
	}	
	else 
		return 0;
	
}




void loop(int index)
{

	int i,j,equal,j_index;
	j_index=index;	
	
	
	
int jal()
{
loop(j_index);
return reg.r[i];	
}
	
int j_()	{
	loop(j_index);
	return;
}

int jr()	{
	r(j_index);
	return;
}
	
/*
int while_loop()
{
	int a,b;
	int temp;	
	int val_1,val_2,x,y;
	char ch_1[1];
	char ch_2[1];
	
	ch_1[0]=0;-
	
	
}	*/
	
	
	
	
	for(i=index; i< count; i++)
	{
		reg.PC = &instr_mem[i];
		
		sscanf(instr_mem[i], "%s\n",op.opcode);
		printf("\nPC = %p\tIstruction = %s",reg.PC,instr_mem[i]);		
		if(!(strcmp(op.opcode,"beq")))
		{
			printf("\nExecuting branch equal instruction\n");
			sscanf(instr_mem[i], "%s %s %s\n",op.opcode,op.op_1,op.op_2);
			op.op_1[strlen(op.op_1)-1]='\0';
			op.op_2[strlen(op.op_2)-1]='\0';
			printf("\nopcode = %s\top_1 = %s\top_2 = %s\tend\tPC = %p\n", op.opcode, op.op_1, op.op_2,reg.PC);
						
			equal = beq(); //if condition is trure return 1 else 0
			if(equal<=1)
				return;
			else 
				continue;
		}
		if(!(strcmp(op.opcode,"bge")))
		{
			printf("\nExecuting bge instruction\n");
			sscanf(instr_mem[i], "%s %s %s\n",op.opcode,op.op_1,op.op_2);
			op.op_1[strlen(op.op_1)-1]='\0';
			op.op_2[strlen(op.op_2)-1]='\0';
			printf("\nopcode = %s\top_1 = %s\top_2 = %s\tend\tPC = %p\n", op.opcode, op.op_1, op.op_2,reg.PC);
						
			equal = bge(); //if condition is trure return 1 else 0
			if(equal==1)
				return;
			else 
				continue;
		}	
			
		if(!(strcmp(op.opcode,"li")))
		{
			printf("\nExecuting load immediate instruction\n");
			sscanf(instr_mem[i], "%s %s %s", op.opcode, op.op_1, op.op_2);
			op.op_1[strlen(op.op_1)-1]='\0';
			op.op_2[strlen(op.op_2)-1]='\0';
			printf("\nopcode = %s\top_1 = %s\top_2 = %s\tPC = %p\n", op.opcode, op.op_1, op.op_2,reg.PC);
			init();				
		}
		if(!(strcmp(op.opcode,"add")))
		{
			printf("\nExecuting increment operation\n");
			sscanf(instr_mem[i], "%s %s %s %s", op.opcode, op.op_1, op.op_2, op.op_3);
			op.op_1[strlen(op.op_1)-1]='\0';
			op.op_2[strlen(op.op_2)-1]='\0';
			op.op_3[strlen(op.op_3)-1]='\0';			
			printf("\nopcode = %s\top_1 = %s\top_2 = %s\top_3 = %s\tPC = %p\n",op.opcode,op.op_1,op.op_2,op.op_3,reg.PC);
			ALU_operations();
		}
		if(!(strcmp(op.opcode,"sub")))
		{
			printf("\nExecuting subtraction operation\n");
			sscanf(instr_mem[i], "%s %s %s %s", op.opcode, op.op_1, op.op_2, op.op_3);
			op.op_1[strlen(op.op_1)-1]='\0';
			op.op_2[strlen(op.op_2)-1]='\0';
			op.op_3[strlen(op.op_3)-1]='\0';			
			printf("\nopcode = %s\top_1 = %s\top_2 = %s\top_3 = %s\tPC = %p\n",op.opcode,op.op_1,op.op_2,op.op_3,reg.PC);
			ALU_operations();
		}
		
		if(!(strcmp(op.opcode,"j")))
		{
			j_();		}
	}
}

void instr_exe(int count)
{
	int i,j,k=0;
	for(i=0; i<count; i++)
	{
		reg.PC = &instr_mem[i];
		j=0;
		printf("\nPC = %p\tIstruction = %s",reg.PC,instr_mem[i]);
		if(!(strcmp(instr_mem[i],"end;\n")))
		{
			val_disp();
			return;
		}
		if((instr_mem[i][0]=='L') && (instr_mem[i][1]=='E'))
		{
			sscanf(instr_mem[i], "%s %s %s", op.opcode, op.op_1, op.op_2);
			memory_operations();
			val_disp();
		}
		
		// parsing instructions from instruction memory (instr_mem[])
		/*for register init*/
		if(instr_mem[i][0] == 'l')
		{
			if(instr_mem[i][1]=='i')
			{
				sscanf(instr_mem[i], "%s %s %s", op.opcode, op.op_1, op.op_2);
				op.op_1[strlen(op.op_1)-1]='\0';
				op.op_2[strlen(op.op_2)-1]='\0';
				printf("\nopcode = %s\top_1 = %s\top_2 = %s\tPC = %p\n", op.opcode, op.op_1, op.op_2,reg.PC);
			init();
			val_disp();
			}
			else 
				continue;
		}
		/*for memory instructions*/
		if(instr_mem[i][0] == 'l' || instr_mem[i][0] == 's')
		{
			if(instr_mem[i][1]=='d')
			{
				sscanf(instr_mem[i], "%s %s %s", op.opcode, op.op_1, op.op_2);
				op.op_1[strlen(op.op_1)-1]='\0';
				op.op_2[strlen(op.op_2)-1]='\0';
				printf("\nopcode = %s\top_1 = %s\top_2 = %s\tPC = %p\n",op.opcode,op.op_1,op.op_2,reg.PC);
			memory_operations();
			val_disp();
			}
			else 
				continue;
		}
		/*for Arithmetic operation instructions*/
		if(instr_mem[i][0] == 'a' || instr_mem[i][0] == 'S' || instr_mem[i][0] == 'm' || instr_mem[i][0] == 'd' || instr_mem[i][0] == 'M')
		{
			sscanf(instr_mem[i], "%s %s %s %s", op.opcode, op.op_1, op.op_2, op.op_3);
			op.op_1[strlen(op.op_1)-1]='\0';
			op.op_2[strlen(op.op_2)-1]='\0';
			op.op_3[strlen(op.op_3)-1]='\0';			
			printf("\nopcode = %s\top_1 = %s\top_2 = %s\top_3--->%s\tPC = %p\n",op.opcode,op.op_1,op.op_2,op.op_3,reg.PC);
			ALU_operations();
			val_disp();
		}
		/*for loop instructions*/
		if((instr_mem[i][0]=='L') && (instr_mem[i][1]=='o'))
		{
			sscanf(instr_mem[i], "%s\n", op.opcode);
			if(!(strcmp(op.opcode,"Loop:")))
			{	
				i++;	
				loop(i);
				val_disp();
			}			
			while(instr_mem[i][0]!='j')
			{
				i++;
			}	
		}	
		
		if(instr_mem[i][0] == 'p')
		{
			if(instr_mem[i][1] == 'o')
			{
				sscanf(instr_mem[i], "%s", op.opcode);
				printf("\nopcode--->%s\n",op.opcode);
				op.opcode[strlen(op.opcode)-1]='\0';
				memory_operations();
				//val_disp();
			}
			else{
				sscanf(instr_mem[i], "%s %s", op.opcode, op.op_1);
				
				op.op_1[strlen(op.op_1)-1]='\0';
				printf("\nopcode-->%s\top_1--->%s\tPC---->%p\n",op.opcode,op.op_1,reg.PC);
				memory_operations();
				//val_disp();
			}
		}	
		
	}
	return;
	
}

int main()

{
	//bootup();
	
	{int key;
	typedef unsigned int si;
	si size=6;
    int list[25];
 
    printf("Enter size of a list: ");
    scanf("%d", &size);
    int s=size%2;
    if (s==0)
	
	    {
    	printf("\nThe number is even\n");
	}
	else
	{
    	printf("\nThe number is odd\n");
	}
    printf("Generating random numbers\n");
    for(i = 0; i < size; i++)
    {
        list[i] = rand() % 100;
        printf("%d  ", list[i]);
    }
    bubble_sort(list, size);
    printf("\n \n");
    
    printf("Enter key to search\n");
    scanf("%d", &key);
//    binary_search(list, 0, size, key);
 }
	
	
	
	
	
	
	
	int i,j,l;
	FILE * fp = fopen("instructionSet.txt", "r");
        for(j=0;j<100;j++)
        {
		mem[j]=j;
	}
	
	for(i=0; i<10; i++)
	{
		instr_mem[i]=(char *)malloc(30*sizeof(char));
	}
	i=0;
	while( fgets(instr_mem[i], sizeof(instr_mem), fp) != NULL ) {
		instr_mem[i][strlen(instr_mem[i])-1] = '\0';
		i++;
		count++;
		if(!(strcmp(instr_mem[i],"end;\n")))
			break;
	}
	
	printf("Instructions from file external text file *.txt:\n");	
	for(i=0; i<count; i++)
	{
		printf("instruction[%d]    >>    %s\n",i,instr_mem[i]);
		
	}
	printf("\n\nExecuting Instructions...\n");
	
	instr_exe(count);
	val_disp();
	return 0;
}

