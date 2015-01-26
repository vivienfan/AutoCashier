.equ ADDR_VGA, 0x08000000
.equ ADDR_CHAR, 0x09000000
.type print_number_of_item,@function
.global print_number_of_item
 
 
 
  

  
print_number_of_item:
	movia r5, ADDR_VGA
	movia r7, ADDR_CHAR
  stbio r20,6418(r7) 
  addi r20,r20,1
  ret