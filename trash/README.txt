//ROLL NUMBER:- 2018201003
//NAME :- VARUN GUPTA

GITLAB PROJECT NAME:- FILE_EXPLORER_LINUX
GITLAB USERNAME:- varun_2018201003

=>FILE CONATINING MAIN FUNCTION:-
osfinal.cpp

=> CHANGING TO NORMAL MODE FROM COMMAND MODE:-
 hit escape and then enter.

=> RECYCLE BIN:-

As per my implemented functionality, all the deleted files/directories are moving to the trash folder(which I have explicitly created), One can restore the file, by just typing the command "restore filename" <-- in  filename one has to just provide the filename and no path along with it. This will restore the file/directory in the directory where it was present earlier.

If any files/directories are deleted from trash folder, then that cannot be restored.

=> FILE/DIRECTORY NAME TOO BIG:-

To handle this, I storing the size of the terminal in a structure and the checking if the filename is greater than terminal size to fit in one line, I am trimming it and then priniting.

=> ONLY 15 ROWS(at max.) will be shown in the terminal while doing ls.
This can be changed,I have added a flag(variable) number_rows, which can be changed accordingly.



=>  