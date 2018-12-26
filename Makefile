shell: \
			main.o \
			displaypath.o \
			displayprompt.o \
			readinput.o \
			split_firstdelim.o \
			split_seconddelim.o \
			execute_cd.o \
			execute_pinfo.o \
			execute_pwd.o \
			execute_echo.o \
			print_all.o \
			execute_env.o \
			print_files.o \
			print_all_l.o \
			print_files_l.o \
			redirect.o \
			jobs.o \
			print_detail.o \
			execute_ls.o \
			execute_remindme.o \
			execute_clock.o \
			check_command.o \
			execute.o \
			checkexit.o \
			interpretCommands.o \
			split_pipes.o
	gcc -g -o shell $^

clean:
	@rm -f *.o shell

main.o: shellheader.h main.c
	gcc -g -c main.c

displaypath.o: shellheader.h displaypath.c
	gcc -g -c displaypath.c

displayprompt.o: shellheader.h displayprompt.c
	gcc -g -c displayprompt.c

readinput.o: shellheader.h readinput.c
	gcc -g -c readinput.c

split_firstdelim.o: shellheader.h split_firstdelim.c
	gcc -g -c split_firstdelim.c

split_seconddelim.o: shellheader.h split_seconddelim.c
	gcc -g -c split_seconddelim.c

execute_cd.o: shellheader.h execute_cd.c
	gcc -g -c execute_cd.c

execute_pinfo.o: shellheader.h execute_pinfo.c
	gcc -g -c execute_pinfo.c

execute_pwd.o: shellheader.h execute_pwd.c 
	gcc -g -c execute_pwd.c

execute_echo.o: shellheader.h execute_echo.c
	gcc -g -c execute_echo.c

print_all.o: shellheader.h print_all.c
	gcc -g -c print_all.c

print_all_l.o: shellheader.h print_all_l.c
	gcc -g -c print_all_l.c

print_files.o: shellheader.h print_files.c
	gcc -g -c print_files.c

print_files_l.o: shellheader.h print_files_l.c
	gcc -g -c print_files_l.c

print_detail.o: shellheader.h print_detail.c
	gcc -g -c print_detail.c

execute_ls.o: shellheader.h execute_ls.c
	gcc -g -c execute_ls.c

execute_remindme.o: shellheader.h execute_remindme.c
	gcc -g -c execute_remindme.c

execute_clock.o: shellheader.h execute_clock.c
	gcc -g -c execute_clock.c

check_command.o: shellheader.h check_command.c
	gcc -g -c check_command.c

execute.o: shellheader.h execute.c
	gcc -g -c execute.c

checkexit.o: shellheader.h checkexit.c
	gcc -g -c checkexit.c

interpretCommands.o: shellheader.h interpretCommands.c
	gcc -g -c interpretCommands.c

redirect.o: shellheader.h redirect.c
	gcc -g -c redirect.c

split_pipes.o: shellheader.h split_pipes.c
	gcc -g -c split_pipes.c

execute_env.o: shellheader.h execute_env.c
	gcc -g -c execute_env.c

jobs.o: shellheader.h jobs.c
	gcc -g -c jobs.c


