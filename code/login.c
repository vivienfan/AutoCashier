#define GLEDs ((volatile long *) 0x10000010)
#define RLEDs ((volatile long *) 0x10000000)

int username_counter;
int password_counter;

int login() {
	//char byte1 = 0;
	//char byte2 = 0;
	//char byte3 = 0;
	
  	volatile int * PS2_ptr = (int *) 0x10000100;  // PS/2 port address

	int PS2_data=0, RAVAIL;
	int pre_data=0;
	int fail;
	int username_array[10];
	int password_array[10];
	int i=0,j=0;
	char* ch;
	char byte3=0;
	
	ch="X!Plore AutoCashier System";
	int d=21;
	while (*ch) {
     write_c(d, 30, *ch);
	 d++;
	 ch++;
   }
   ch="Copyright @ Yue Wang & Yinghui Fan";
	d=18;
	while (*ch) {
     write_c(d, 34, *ch);
	 d++;
	 ch++;
   }
	
username:
PS2_data=*PS2_ptr;
	RAVAIL = (PS2_data & 0xFFFF0000) >> 16;	// extract the RAVAIL field
		while(RAVAIL > 0)
		{
			RAVAIL = (PS2_data & 0xFFFF0000) >> 16;
			byte3 = PS2_data & 0xFF;
		}

	ch="Please enter your username: ";
	int x=10;
	while (*ch) {
     write_c(x, 8, *ch);
	 x++;
	 ch++;
   }
   username_counter=x;
   while (*PS2_ptr!=0x5A) {
		PS2_data=*PS2_ptr;
		if(PS2_data==0x1C||PS2_data==0x32||PS2_data==0x21||PS2_data==0x23||PS2_data==0x24||PS2_data==0x2B||PS2_data==0x34||PS2_data==0x33||PS2_data==0x43||PS2_data==0x3B||PS2_data==0x42||
			PS2_data==0x4B||PS2_data==0x3A||PS2_data==0x31||PS2_data==0x44||PS2_data==0x4D||PS2_data==0x15||PS2_data==0x2D||PS2_data==0x1B||PS2_data==0x2C||PS2_data==0x3C||PS2_data==0x2A||
			PS2_data==0x1D||PS2_data==0x22||PS2_data==0x35||PS2_data==0x1A||PS2_data==0x45||PS2_data==0x16||PS2_data==0x1E||PS2_data==0x26||PS2_data==0x25||PS2_data==0x2E||PS2_data==0x36||
			PS2_data==0x3D||PS2_data==0x3E||PS2_data==0x46){
		fail=0;
		
		}
		
		else{
		fail=1;
		
		}
		
		if(fail==0&&pre_data!=PS2_data){
		char_converter(PS2_data,x);
		*GLEDs = PS2_data;
		username_array[i]=PS2_data;
		i++;
		x++;
		fail=1;
		pre_data=PS2_data;
	}
	}	
  /* pre_data=0;
   ch="Please enter your password: ";
   x=10;
   while (*ch) {
     write_c(x, 11, *ch);
	 x++;
	 ch++;
   }
	password_counter=x;
	
	
	while (*PS2_ptr!=0x5A) {
		PS2_data=*PS2_ptr;
		if(PS2_data==0x1C||PS2_data==0x32||PS2_data==0x21||PS2_data==0x23||PS2_data==0x24||PS2_data==0x2B||PS2_data==0x34||PS2_data==0x33||PS2_data==0x43||PS2_data==0x3B||PS2_data==0x42||
			PS2_data==0x4B||PS2_data==0x3A||PS2_data==0x31||PS2_data==0x44||PS2_data==0x4D||PS2_data==0x15||PS2_data==0x2D||PS2_data==0x1B||PS2_data==0x2C||PS2_data==0x3C||PS2_data==0x2A||
			PS2_data==0x1D||PS2_data==0x22||PS2_data==0x35||PS2_data==0x1A||PS2_data==0x45||PS2_data==0x16||PS2_data==0x1E||PS2_data==0x26||PS2_data==0x25||PS2_data==0x2E||PS2_data==0x36||
			PS2_data==0x3D||PS2_data==0x3E||PS2_data==0x46){
		fail=0;
		
		}
		
		else{
		fail=1;
		
		}
		
		if(fail==0&&pre_data!=PS2_data){
		char_converter(PS2_data,x);
		*GLEDs = PS2_data;
		password_array[j]=PS2_data;
		j++;
		x++;
		fail=1;
		pre_data=PS2_data;
	}
		
	}*/
	if(username_array[0]==0x2D&&username_array[1]==0x44&&username_array[2]==0x1B&&username_array[3]==0x1C
		){
		ch="                  Cashier: ";
		x=10;
		 while (*ch) {
		write_c(x, 8, *ch);
		x++;
		ch++;
		}
		
		return 0;
		}
	else{
		ch="Username wrong!";
		x=10;
		 while (*ch) {
		write_c(x, 13, *ch);
		x++;
		ch++;
		}
		ch="               ";
		x=10;
		 while (*ch) {
		write_c(x, 13, *ch);
		x++;
		ch++;
		}
		ch="                    ";
		x=37;
		 while (*ch) {
		write_c(x, 10, *ch);
		x++;
		ch++;
		}
		ch="                    ";
		x=37;
		 while (*ch) {
		write_c(x, 11, *ch);
		x++;
		ch++;
		}
		goto username;
	
	}
}


void write_c(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0x09000000 + (y<<7) + x);
  *character_buffer = c;
}

void char_converter(int ptr, int username_counter){
if(ptr==0x1C){
		write_c(username_counter, 8, 'A');
		  ;
		 }
else if(ptr==0x32){
		write_c(username_counter, 8, 'B');
		  ;
		 }
else if(ptr==0x21){
		write_c(username_counter, 8, 'C');
		  ;
		}
else if(ptr==0x23){
		write_c(username_counter, 8, 'D');
		  ;
		
	}
else if(ptr==0x24){
		 
		write_c(username_counter, 8, 'E');
		  ;
		}
else if(ptr==0x2B){
		write_c(username_counter, 8, 'F');
		  ;
		}
else if(ptr==0x34){
		write_c(username_counter, 8, 'G');
		  ;
		}
else if(ptr==0x33){
		write_c(username_counter, 8, 'H');
		  ;
		}
else if(ptr==0x43){
		write_c(username_counter, 8, 'I');
		  ;
		}
else if(ptr==0x3B){
		write_c(username_counter, 8, 'J');
		  ;
		}
else if(ptr==0x42){
		write_c(username_counter, 8, 'K');
		  ;
		}
else if(ptr==0x4B){
		write_c(username_counter, 8, 'L');
		  ;
		}
else if(ptr==0x3A){
		write_c(username_counter, 8, 'M');
		  ;
		}
else if(ptr==0x31){
		write_c(username_counter, 8, 'N');
		  ;
		}
else if(ptr==0x44){
		write_c(username_counter, 8, 'O');
		  ;
		}
else if(ptr==0x4D){
		write_c(username_counter, 8, 'P');
		  ;
		}
else if(ptr==0x15){
        write_c(username_counter, 8, 'Q');
		  ;
		}
else if(ptr==0x2D){
		write_c(username_counter, 8, 'R');
		  ;
		}
else if(ptr==0x1B){
		write_c(username_counter, 8, 'S');
		  ;
		}
else if(ptr==0x2C){
	    write_c(username_counter, 8, 'T');
		  ;
		}
else if(ptr==0x3C){
	    write_c(username_counter, 8, 'U');
		  ;
		}
else if(ptr==0x2A){
		write_c(username_counter, 8, 'V');
		  ;
		}
else if(ptr==0x1D){
		write_c(username_counter, 8, 'W');
		  ;
		}
else if(ptr==0x22){
		write_c(username_counter, 8, 'X');
		  ;
		}
else if(ptr==0x35){
		write_c(username_counter, 8, 'Y');
		  ;
		}
else if(ptr==0x1A){
		write_c(username_counter, 8, 'Z');
		  ;
		}
else if(ptr==0x45){
		write_c(username_counter, 8, '0');
		  ;
		}
else if(ptr==0x16){
		write_c(username_counter, 8, '1');
		  ;
		}
else if(ptr==0x1E){
	    write_c(username_counter, 8, '2');
		  ;
		}
else if(ptr==0x26){
		write_c(username_counter, 8, '3');
		  ;
		}
else if(ptr==0x25){
        write_c(username_counter, 8, '4');
		  ;
		}
else if(ptr==0x2E){
		write_c(username_counter, 8, '5');
		  ;
		}
else if(ptr==0x36){
		write_c(username_counter, 8, '6');
		  ;
		}
else if(ptr==0x3D){
		write_c(username_counter, 8, '7');
		  ;
		}
else if(ptr==0x3E){
		write_c(username_counter, 8, '8');
		  ;
		}
else if(ptr==0x46){
		write_c(username_counter, 8, '9');
		  ;
		}
}

