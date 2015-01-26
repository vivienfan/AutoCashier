This program uses interrupt, pulling, condition comparison, timer, keyboard, LEGO light sensor and LEGO motor to simulate a conveyor belt with barcode scanner.
The converyor belt is rotated by the motor at a certain speed detarmained by the timer period.
The attached light sensor scans the barcodes painted on the items on the conveyor belt.
Then the program converts barcodes into binary data to find item information in a given database, then using C functions, it prints formatted output onto LCD screen via a VGA connector.
Interrupt provides the ability of moving to different statages, such as "security login", "check out", "print the bill", "exit" or "handle timer".
