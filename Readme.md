Read me CSCI 5801
Project Prepared by Team 22

# Team Members -

1. Berni Duong (duong142)
2. Danet Chheng (chhen004)
3. Khoa Tran (tran0707)
4. Hon Kwan Sin (sin00001)

# Purpose:
The purpose of this README is to describe the Voting System that is being
developed as a part of the class project for the class CSCI 5801 - Software
Engineering I at University of Minnesota (Twin Cities). The intended audience for
the document includes the instructor of the class, teaching assistants and
fellow classmates. Also this README would be used to explain various parts of
the project including the directory structure of the Project1 repository,
the various files used and their intention/work and also the various locations
these files are.

# Scope:
The Voting System software was developed for everyone, such as programmers,
testers, election officials and students who want to learn and use Voting System
software. This Voting System software focuses on two types of voting, such as
Open Party List (OPL) and Closed Party List (CPL). Voting System can handle
prompt users for a filename, a user selection options, read the input file,
export the output file, audit file, report and display winners, flip coin when
tie, and share the election's result. The Voting System software will develop
in C++ programming language by providing all the sources files, and the program
will run from the command prompt. The system will read the input file, and it
will be comma-separated values for the ballots where each row is separated by a
new line. Also, the file will be exported from Excel into run 100, 000 ballots
in under 5 minutes. The system will assume that there are no numeric errors
and no security needed. The software is an open-source project, and it has a
very active developer team to support it and provide feedback to users.

# Overview:
The voting system would ask the user to select the appropriate voting algorithm
with the name of the input files (opl.csv or cpl.csv) and the number of seats
that need to be filled in the election. The voting system will be printing
the results of the election to the standard output and then will redirect
the user to the main menu again in case they want to get the results of some
different election (another input csv files).

# Directory Structure:
Project2/
src/
Contains all the source code files for the project. The files includes:

	candidate.cc
	candidate.h
	common.h
	communication.h
	controller.cc
	controller.h
	cpl.cc
	cpl.h
	graphics_voting_system_viewer.cc
	graphics_voting_system_viewer.h
	graphics_voting_system_viewer.h~HEAD
	main.cc
	mainpage.h
	Makefile
	opl_random.csv
	opl.cc
	opl.h
	params.h
	party.cc
	party.h
	report.cc
	report.h
	sortby.h
	voting_system.cc
	voting_system.h
	voting_type.cc
	voting_type.h

The testing files in Prject2 directory includes:
	testing/
	build
	Makefile
	cpl_audit_unittest.cc
	cpl_audit.txt
	cpl_efficiency.cc
	cpl_readfile_unittest.cc
	cpl_share.txt
	cpl.csv
	opl_audit_unittest.cc
	opl_audit.txt
	opl_random.csv
	opl_readfile_unittest.cc
	opl_share.txt
	opl.csv
	party_UT.cc
	report_UT.cc
	testing.txt
	testinglogs_P1.docx
	testinglogs_P2.docx
	voting_system_unittest.cc
	voting_type_unittest.cc

	misc/
	Contains some files that were not directly used in the voting system, but it will be helpful for the audience to understand the Voting System by reading SRS, SDD. Also, the users will understand the whole system by looking at UML class diagram for a whole system.

Currently three files reside in this directory as follows:

	- Copy of UML Class Diagram Voting System.pdf
	- SDD_Team22.pdf
	- SRS_Team22.pdf

- Readme.md
	This file. Is responsible to outline basic information about the project and
	how it should be used.

- buglist
	Contains data about possible bugs that were found in the whole system.

# Running the Voting System
To run the Voting System, users can use a terminal opened in the Project2/src/
directory. Then run the following two commands:

__$ make all
$ cd ..
$ cd Project2/
$ cd build/
$ cd bin/
$ ./votingsystem__

or
__In Project2/src/
$ make
then in Project2/build/bin
$ ./votingsystem__

### Notes: REMEMBER COPY all input file from Project2/Input/ to Project2/build/bin and Project2/testing/build/bin

Here is the example before graphical interface of the output in terminal:

WELCOME TO VOTING AUDITING SYSTEM
	> Please enter the number corresponding to the following option.
		1 - Input file name
		2 - Exit
	=> 1
	Please enter your input filename: opl.csv
	Voting Type: OPL
	Number of Total Candidates: 6
	Number of Total Seats: 3
	WINNER:
	Candidate Name    Party Name    Number of Vote    Number of Seats    
	Smith                  I              1                1
	Deutsch                R              3                1
	Borg                   R              3                1
	Jones                  R              3                1
	Pike                   D              5                1
	Foster                 D              5                1

In the above example, "opl.csv" must be located in the same directory as ./votingsystem,
as should any other input file provided by the user.

# Expected Working of Voting System
Assuming that the user is able to run the system as discussed in the previous
section, the Voting System will immediately print a message to the standard
output alerting the user that the system is running. It will ask the user about
the relevant details related to the election which includes details like name of
the user name, type of voting (Open Party List (OPL) or Closed Party List (CPL)),
and then prompt the user about various details about the file (election)
like name of the file, number of seats that need to be filled, number of
candidates in the election, number of ballots in the election. Once all the user
input is processed the system will implement the voting algorithm and print the
results of the election back to the standard output.

# Assumptions Made
Several assumptions have been made when designing the voting system and its is
very important to review these for the users. In this Voting System, the election
file that is input and output files will always be in the same directory as the
program. Also, there are no numbering error and no security needed, and the
Voting System will assume that the user will use the most up-to-date CSELabs
machines. In details the files will follows some guidelines as follows:

	Open Party List (OPL)
	First Line (1st): OPL for open party listing
	Second Line (2nd): Number of Seats
	Third Line (3rd): Number of Ballots
	Fourth Line (4th): Number of Candidates
	Following the fourth line are the candidates (one per line) and in the format
	above. The candidates and their party are in [].
	Then, the ballots are listed on per line and commas are used to separate the
	positions.

All the ballots in the file will start immediately after the header.
No line is left as blank
Currently the CSV file should be error free
It is also assumed that the user input through the menu would be error free
The number of candidates in file is equal to the number of candidates entered
The number of ballots in file is equal to the number of ballots in file
The number of seats that need to be filled is less than the number of candidates
and greater than 0
The file name (relative path) is valid

	Closed Party List (CPL)
	First Line (1st): CPL for Closed Party Listing
	Second Line (2nd): Number of Parties
	Third Line (3rd): Parties in Order of Ballot Ordering
	Fourth Line (4th): Number of Seats
	Fifth Line (5th): Number of Ballots
	Sixth Line (6th): Number of Candidates
	Following line sixth line are the candidates' information followed immediately
	by all of the ballots. The order of the party is indicates their position in the
	ballot.

All the ballots in the file will start immediately after the header.
No line is left as blank
Currently the CSV file should be error free
It is also assumed that the user input through the menu would be error free
The number of candidates in file is equal to the number of candidates entered
The number of ballots in file is equal to the number of ballots in file
The number of seats that need to be filled is less than the number of candidates
and greater than 0
The file name (relative path) is valid

# Testing Project2 (Unit Test)
To run the unit tests for different parts of the voting system users can
use a terminal opened in the Project2/testing directory.

commands:

In Project2/Input/, copy all the csv files these and paste it to Project2/testing/build/bin

In Project2/testing/
__$ make__

then in Project2/testing/build/bin
__$ ./unittest__

By default, ALL the tests we have written for the system will run.
It is possible to decrease compile time by omitting the compiling of selected tests.

In Project2/testing, open Makefile.

Find the line that says

"##### Below is a list of tests. Comment out unwanted tests to increase runtime #####",

located at near the top of the file. Below this line is a sequence of

"DEFINES += <TEST_NAME>" lines.

Comment out unwanted tests using "#". For example, to omit the OPL Tiebreaker Test:

"#DEFINES += -DOPL_TIEBREAKER_TEST"

### Notes: REMEMBER COPY opl.csv and cpl.csv from Project2/testing/ to Project2/testing/build/bin

TODO:
	>Change the file names so it goes parent directory.
	Tomorrow CSE LABS Machine System Testing
	Make Sure Documentation is taken care of
	All tests are working
	Menu feature is thoroughly tested.
	Make a new branch for each team members to keep track of the development in the
	project of Voting System implementation
	All changes are merged in the Master branch
	Summit the final submission in Master branch
	Read me CSCI 5801
	Project Prepared by Team


### Update: Using GUI:
- Open file button: You must select the Open file button first, you can search for a file, but it allows to select only (.csv)
- Nothing happens when cancel selection.
- Audit and sharing button: Then you must select the location to save audit and sharing file, you can enter file name, or select a file,
but it must be .txt,  if not select, you still able to run audit, then the default "audit_result.txt"
and "sharing_result.txt" will be your reporting files at the program's current Directory
- Audit button: Running the audit process the auto generate audit file and sharing file at location you selected
- Reset button: works as normal, reset all variable of voting system
- Exit button: is to close the program
