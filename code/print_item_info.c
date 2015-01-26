#include <stdio.h>
int x;
char* ch;
int check[5]={0,0,0,0,0};
int price[5]={0,0,0,0,0};
char p[4];

void print_item_info(int i){
clear_previous();
if(i==0){
	x=33;
	ch="Apple Macbook Pro 15'";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;
	 
	}
	check[0]=1;
	price[0]=2199;

}

else if(i==1){
	x=33;
	ch="Tekni PS/2 keyboard";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;
	}
	check[1]=1;
	price[1]=30;
}
else if(i==2){
	x=33;
	ch="Samsung LED display 23'";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;
	}
	check[2]=1;
	price[2]=270;
}
else if(i==3){
	x=33;
	ch="Sony MDR-10RBT Headphone";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;
	}
	check[3]=1;
	price[3]=320;
}
else if(i==4){
	x=33;
	ch="Logitec Camera";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;
	}
	check[4]=1;
	price[4]=150;
}


}

void write_char_c_c(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0x09000000 + (y<<7) + x);
  *character_buffer = c;
}

void clear_previous(){
	x=33;
	ch="                        ";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;

	}

}

void print_total_price(){
	int i=0;
	int total_price=0;
	while(i<5){
		if(check[i]==1){
			total_price=price[i]+total_price;
			sprintf(p,4,"%d",total_price);
		}
	}
	
	x=20;
	int k=0;
	while(k<4){
	write_char(x,54,p[k]);
	x++;
	k++;
	}

}
