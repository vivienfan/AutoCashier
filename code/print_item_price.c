
int x;
char* ch;

void print_item_price(int i){
clear_previous_price();
if(i==0){
	x=63;
	ch="$2199";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;

	}
	

}

else if(i==1){
	x=63;
	ch="$30";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;
	}
}
else if(i==2){
	x=63;
	ch="$270";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;

	}
}
else if(i==3){
	x=63;
	ch="$320";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;

	}
}
else if(i==4){
	x=63;
	ch="$150";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;

	}
}


}

void clear_previous_price(){
	x=63;
	ch="      ";
	while(*ch){
	write_char(x, 10, *ch);
	 x++;
	 ch++;

	}

}