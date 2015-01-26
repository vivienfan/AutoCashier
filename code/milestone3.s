
.section .exceptions, "ax"

myISR:
	mov r12, et
	rdctl r13, ctl1
	mov r14, ea
	rdctl et, ctl4
	andi et, et, 0x100
	bne et, r0, HANDLE_KEYBOARD
	rdctl et, ctl4
	andi et, et, 0x1
	bne et, r0, HANDLE_TIMER
	br EXIT

HANDLE_KEYBOARD:
	ldwio et, 0(r11)
	andi r22, et, 0x8000
	beq r22, r0, HANDLE_KEYBOARD
	andi r22, et, 0x00ff
	movi et, 0x1b					/* 0x1b = 'esc' */
	beq r22, et, LOG_OFF
	br THE_BILL
	
LOG_OFF:
	addi r21, r0, 0b100				/* status register = LOG_OFF */
	br EXIT
	
THE_BILL:
	addi r21,r0, 0b010				/* status register = TOTAL */
	br EXIT

HANDLE_TIMER:
	stwio r0, 0(r9)					/* restart the timer */
	addi r21, r0, 0b001				/* status register = TIME_OUT */

EXIT:
	mov et, r12
	wrctl ctl1, r13
	subi r14, r14, 4
	mov ea, r14
	eret

.section .data

debug1: 
	.string ""
.section .text	

.equ LED, 0x10000000
.equ ADDR_JP1, 0x10000060
.equ KEYBOARD, 0x10001000
.equ TIMER, 0x10002000
.equ PERIOD, 16000000

.global main

main:
	call clear_screen
	movia r8, ADDR_JP1
	movia r9, TIMER
	movia r10, LED
	movia r11, KEYBOARD
	addi r20, r0, 1					/* item number initialize to 1 */

	/* timer set up */
	movui r15, %lo(PERIOD)
	stwio r15, 8(r9)				/* Set the lower period */
	movui r15, %hi(PERIOD)
    	stwio r15, 12(r9)				/* Set the higher period */
	stwio r0, 0(r9)					/* clear the timer */
	movi r15, 0b111
	stwio r15, 4(r9)				/* start, cont, enable interrupts */
	
	/*keyboard set up */
	movi r15, 0b1
	stwio r15, 4(r11)				/* enable read interrupts */
	
	/* enable external interrupts */
	movi r15, 0b100000001			
	wrctl ctl3, r15					/* enable timer and keyboard interrupts */
	movi r15, 0b1
	wrctl ctl0, r15					/* set PIE = 1, start interrupt */
	
	/* sensor and motor set up */
	movia r15, 0x07f557ff
	stwio r15, 4(r8)
		
START:
	movia r15, 0xfffeffff				/* sensor3 on, motor0 off */
	stwio r15, 0(r8)
	# call login	

NEW_CLIENT:
	mov r16, r0					/* initializing all registers */
	mov r17, r0
	mov r18, r0
	mov r19, r0
	mov r21, r0
	mov r22, r0
	call background
	movia r15, 0xfffefffe				/* (=) sensor3 on, motor0 on */
	stwio r15, 0(r8)				/* sensor3 on, motor0 on*/	

LOOP_FOREVER:
	addi r16, r0, 0b100
	beq r16, r21, START				/* if status = LOG_OFF, restart */
	addi r16, r0, 0b010
	beq r16, r21, TOTAL				/* if status = TOTAL, count the total price */
	addi r16, r0, 0b001
	beq r16, r21, READ				/* if status = TIME_OUT, read the bar code */
	br LOOP_FOREVER					/* else, do nothing */

TOTAL:
	mov r21, r0
	call print_total_price 

WAIT:
	addi r16, r0, 0b010
	beq r16, r21, NEW_CLIENT			/* if status = TOTAL, go to NEW_CLIENT */
	br WAIT
	
READ:
	mov r21, r0
	ldwio r16, 0(r8)				/* get the value from ADDR_JR1 */
	srli r16, r16, 17				/* check if sensor3 value is valid */
	andi r16, r16, 0x1
	bne r0, r16, READ
	ldwio r16, 0(r8)				/* if valid, get the value */
	srli r16, r16, 27
	andi r16, r16, 0x0f
	addi r17, r0, 0x0b
	mov r18, r0					/* r18 = 0 (invalid signal) */
	bge r16, r17, RETURN				/* if r16 >= b, return */
	addi r18, r0, 0b10				/* value valid */
	addi r17, r0, 5
	ble r16, r17, RETURN				/* if r16 <= 4, signal is low, r18 = 0b10 (valid low signal) */
	addi r18, r0, 0b11				/* if r16 > 4, signal is high, r18 = 0b11 (valid high signal) */
	
RETURN:
	
	beq r18, r0, LOOP_FOREVER
	slli r19, r19, 1				/* if signal is valid, bar code shift left one bit */
	addi r16, r0, 0b10
	beq r18, r16, CHECK				/* if signal is valid low, check if the bar code exists */
	addi r19, r19, 1				/* else, the signal is valid high */
	
CHECK:
	mov r4, r19
	call main_hex
	addi r20, r20, 1
	addi r16, r0, 3
	bne r20, r16, LOOP_FOREVER
	mov r20, r0
	addi r16, r0, 0b010
	beq r19, r16, ITEM0
	addi r16, r0, 0b101
	beq r19, r16, ITEM0
	
	addi r16, r0, 0b110
	beq r19, r16, ITEM1
	addi r16, r0, 0b111
	beq r19, r16, ITEM1

	addi r16, r0, 0b001
	beq r19, r16, ITEM2
	addi r16, r0, 0b100
	beq r19, r16, ITEM2
	mov r19, r0
	br LOOP_FOREVER

ITEM0:
	mov r19, r0
	addi r16, r0, 0b0101
	stwio r16, 0(r10)
	mov r4, r0
	call print_item_info 
	br LOOP_FOREVER

ITEM1:
	mov r19, r0
	addi r16, r0, 0b1101
	stwio r16, 0(r10)
	addi r4, r0, 1
	call print_item_info
	br LOOP_FOREVER

ITEM2:	
	mov r19, r0
	addi r16, r0, 0b0010
	stwio r16, 0(r10)
	addi r4, r0, 2
	call print_item_info
	br LOOP_FOREVER
