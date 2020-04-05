# comp322-Project 6: Forks and Pipes

(25 points)

Modify your mywc program so that it creates as many processes as there are files on the command line (in the case that there are no files on the command line, only one child process should be created.) Each process should count words, lines and character, according to the specified options, of one file only and write the result to a pipe. The parent process should read from the pipe and display the grand total. In addition to displaying the same count information as wc, your program should also display the process-id of the counting process next to the file name.

See [example.c](example.c)

