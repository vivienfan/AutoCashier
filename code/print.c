/* set a single pixel on the screen at x,y
 * x in [0,319], y in [0,239], and colour in [0,65535]
 */
void write_pixel(int x, int y, short colour) {
  volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1));
  *vga_addr=colour;
}

/* use write_pixel to set entire screen to black (does not clear the character buffer) */
void clear_screen() {
  int x, y;
  for (x = 0; x < 320; x++) {
    for (y = 0; y < 240; y++) {
	  write_pixel(x,y,0);
	}
  }
}

/* write a single character to the character buffer at x,y
 * x in [0,79], y in [0,59]
 */
void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0x09000000 + (y<<7) + x);
  *character_buffer = c;
}

void background () {

   clear_screen();
   int x;
   int y;
   char* hw;
   

   
   
draw_lines1:
   for (x=65;x<130;x++)
   {
      // Draw a straight line in red across the screen centre
      write_pixel(x, 60, 0xf800);
      // Draw a "diagonal" line in green
	}
	for(y=60;y<90;y++){
         write_pixel(65, y, 0xf800);
   }
   goto draw_lines2;
draw_lines2:
	 for (x=65;x<130;x++)
   {
      // Draw a straight line in red across the screen centre
      write_pixel(x, 90, 0xf800);
      // Draw a "diagonal" line in green
	}
	for(y=60;y<91;y++){
         write_pixel(130, y, 0xf800);
   }
   goto draw_lines3;
   draw_lines3:
   for (x=189;x<254;x++)
   {
      // Draw a straight line in red across the screen centre
      write_pixel(x, 60, 0xf800);
      // Draw a "diagonal" line in green
	}
	for(y=60;y<91;y++){
         write_pixel(189, y, 0xf800);
   }
   goto draw_lines4;
draw_lines4:
	 for (x=189;x<255;x++)
   {
      // Draw a straight line in red across the screen centre
      write_pixel(x, 91, 0xf800);
      // Draw a "diagonal" line in green
	}
	for(y=60;y<91;y++){
         write_pixel(254, y, 0xf800);
   }

  
 write_item:
	hw = "Item Name";
   x = 20;
   while (*hw) {
     write_char(x, 10, *hw);
	 x++;
	 hw++;
   }
   goto write_price;
 write_price:
 hw = "Item Price";
   x = 50;
   while (*hw) {
     write_char(x, 10, *hw);
	 x++;
	 hw++;
   }
 goto write_total_number;
 
 write_total_number:
 hw = "Total Number: ";
   x = 3;
   while (*hw) {
     write_char(x, 50, *hw);
	 x++;
	 hw++;
   }
  goto write_total_amount_due;
  
  
write_total_amount_due:
 hw = "Total Amount Due: ";
   x = 3;
   while (*hw) {
     write_char(x, 54, *hw);
	 x++;
	 hw++;
   }
 
 
 
 
}