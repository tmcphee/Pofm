#pragma once

/*Append text to the end of a file Insert text in a specific position(counted in characters) of the file, 
Remove all text in a file, Show the content of a text file, with the ability to pause per page.The number
of lines per page can be specified by the user.*/
void editText(char choice) {
	switch (choice) {
		case('O')://read a files conents line by line
			break;
		case('D')://Remove all text from a file
			break;
		case('I')://Insert text to a certain position in a file
			break;
		case('A')://Append text to the end of a text document
			break;
	}
	return;
}