/**
 * @file mainpage.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/**
 * \mainpage Voting System CSCI 5801
 *
 *
 * \section intro_sec Introduction to Voting System
 *
 *
 * Welcome to The Voting System Sotfware of CSCI 5801 -
 * Fall 2019 University of Minnesota
 * The goal of this software project is be able to perform two types of Voting
 * System: Open Party List (OPL) and Closed Party List (CPL).
 *
 * \section overview Overview
 *
 * This project is a Voting System Software that allows many users who
 * participate in the election of Open Party List (CPL) and
 * Closed Party List (OPL) to produce election results. For Open Party List
 * ballet, voters express a preference for a particular candidate and party that
 * each ballot will only have one candidate indicated as choice for the vote.
 * For Closed Party List ballet, voters express a preference for a particular
 * party that the order of the "elected" officials is dependent on the order of
 * the party's numbering of teh candidates on the ballet.
 *
 * In this system, the users can assume that there are no numbering error in the
 * file, and the file will always be in the same directory as the program.
 * In the Voting System Software, the users can enter the prompt command in
 * the keyboard.
 *
 * \section candidate Candidate
 *
 * Candidate represents a person who applies for election. In the candidate
 * class, the system be able to access the information from the candidates in
 * CLP and OPl. Closed Party List (CPL) contains the name of candidate and the
 * priority party. Open Party List (OPl) contains only the name of candidate.
 * Candidate's class provides more information about ballot numbers and the list
 * of ballot id.
 *
 * \section party Party
 *
 * According to wikipedia.or, Party is a political party that organized group
 * of people who have the same ideology, or who otherwise have the same
 * political positions, and who field candidates for elections, in an attempt
 * to get them elected and thereby implement the party's agenda
 * (https://en.wikipedia.org/wiki/Political_party). In our Voting System,
 * there are five parties, such as Democratic, Republican, Reform, Green, and
 * Independent Candidate. In the party's class, the system can access the
 * information for each parties with the list of candidates and the name of
 * each party. In this class, the system be able to get access the number of
 * of seats, number of votes and number of candidates. Also, we implement the
 * functions that can add the candidate into the list of candidate and add the
 * ballot id into the list of ballot id.
 *
 * \section cpl CPL
 *
 * CPL stands for Closed Party List that the party fixes the order in which the
 * candidates are listed and elected, and the voter simply casts a vote for the
 * party as a whole. The voters are not be able to indicate their preference for
 * any candidates on the list but must accept the list in the order presented by
 * the party. Winning candidates are selected in the exact order they appear on
 * the original list. In this class, we implement the ReadFile function which
 * reads the file information into some corresponding object for CPL voting
 * type. After reading the file, all the inormation are stored in report_.
 * In this class, we implement PopulateVotes() function to count the votes.
 * Also, we use struct sortbypartyvote to sort the order of the vote by
 * comparing the number of votes. Whatever party gets the highest vote, it will
 * appear at the top. Then, we implement the DistributreSeats() to get a total
 * of seats. Also, we sort the priority order of the candidate. We implement
 * Audit() function which counts votes and modify a party list into only
 * containing the winners.
 *
 * \section opl OPL
 *
 * OPl stands for Open Party List that voters express a preference for a
 * particular candidate and a party. Each ballot will only have one candidate
 * indicated as choice for the vote. In this class, we use similar method to
 * CPL class. We implement the ReadFile function which reads the file
 * information into some corresponding object for OPL. After reading the file,
 * all the information will store in report_. All other functions that we
 * implement are similar to CPL, such as ReadFile(), struct sortbypartyvote,
 * Audit(), DistributeSeats(), and PopulateVotes(). The only different is, we
 * implement struct sortbycandvote in OPL.
 *
 * \section voting_type VotingType
 *
 * Voting System allows many users who participate in the election for Open List
 * Party (OPL) and Closed Party List (CPL) to produce election results with
 * accurate, consistent, fair and helpful for all users. In this class, it
 * contains general methods and variables which both OPL and CPL use.
 * For example, both OPL and CPL use same Report object, use same SplitByComma()
 * method for reading information from file. In this class, we implement
 * ReadFile() to read the information into some corresponding object depending
 * on OPL or CPL. In this class, we randomly select the winner by using a
 * unique number begin from 1. Then, we implement the SplitByComma() to split
 * the string with delimiter comma ",".
 *
 * \section voting_system VotingSystem
 *
 * VotingSystem will call to run the method as main function runs.
 * In this class, the user can input a file name for their voting system types,
 * the user input will be save to this input_file_name_. Also, we implement the Run()
 * function to launches the system and starts to ask user to select options.
 * Then, RunAuditProcess() will run every steps of voting system. In this class,
 * we implement some functions to handle the correct filename format and the directory
 * to save the file.
 *
 * \section report Report
 *
 * Report is used to report all the information related to election, such as
 * candidates, party, voting type, number of ballots, number of seats,
 * result of the election and winner. In this class, it will display all the
 * election's information for both OPL and CPL to the visible screen. Then, it
 * exports both OPL and CPL to audit file by writing its into the file.
 * After that, the report will export to the public file by sharing the report
 * to other organization, such as Journalism, TV, and other official
 * institutions as needed.
 *
 * @author
 * - Source code: UMN CSE Staffs
 * - Editor: Team 22
 */

#endif  // SRC_MAINPAGE_H_
