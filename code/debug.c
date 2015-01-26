void print_string (char *c) 

{
	printf("%s\n",c);

	return;
}

void print_reg (int n) 

{
	printf("%d\n",n);

	return;
}

void main_hex(int y) 
{
	int k = 0, t = 0;
	int mod_number = 1000;
	
	do {
	k = y/mod_number;
	y = y - (y/mod_number)*mod_number;
	mod_number = mod_number/10;
	printHex(&t,k);
	}while(y > 1);

	#define HEX ((volatile int*) 0x10000020)
	*HEX = t;
}

void printHex(int *x, int y)
{
	if(y == 0)
	{
		*x = (*x << 8) + 0x3f;
	}
	
	else if(y == 1)
	{
		*x = (*x << 8) + 0x6;
	}
	
	else if(y == 2)
	{
		*x = (*x << 8) + 0x5b;
	}
	else if(y == 3)
	{
		*x = (*x << 8) + 0x4f;
	}
	else if(y == 4)
	{
		*x = (*x << 8) + 0x66;
	}
	else if(y == 5)
	{
		*x = (*x << 8) + 0x6d;
	}
	else if(y == 6)
	{
		*x = (*x << 8) + 0x7d;
	}
	else if(y == 7)
	{
		*x = (*x << 8) + 0x07;
	}
	else if(y == 8)
	{
		*x = (*x << 8) + 0x7f;
	}
	else if(y == 9)
	{
		*x = (*x << 8) + 0x67;
	}
	return;
}