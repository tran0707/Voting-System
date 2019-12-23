/**
 * @file opl.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */
#ifndef SRC_CPL_H
#define SRC_CPL_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "report.h"
#include "party.h"
#include "voting_type.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Closed Party List voting. Inherits VotingType.
 * This voting method votes only to parties. So, Candidate objects
 * will not recieve any votes. Party will recieve the votes instead.
 * This is informed to the Report class for Displaying results.
 */
class CPL : public VotingType {
  public:
    /**
		 * @brief  default Constructor.
		 */
		CPL() { }

    /**
		* @brief VotingType's destructor. `delete` all objects created.
		*/
		~CPL() { }

    /**
     * @brief Read the file info into some corresponding object.
     * This Readfile is used for CPL voting type.
     *
     * Steps:
     * - 1st Line: CPL for closed party listing
     * - 2nd Line: Number of Parties
     * - 3d Line: Parties in Order of Ballot Ordering
     * - 4th Line: Number of Seats
     * - 5th Line: Number of Ballots
     * - 6th Line: Number of Candidates
     * - Following line 6 are the candidates’ information followed immediately
     * by all of the ballots
     * - Then the ballots are listed on per line and commas are used
     * to separate the positions.
     *
     * All the information after reading are stored in report_
     *
     * @param file_name the file name is used to read
     */
		void ReadFile(std::string file_name) override;
    /**
		 * @brief  After ReadFile(), more information will be processed
     * into different classes and stored. This first calls PopulateVotes()
     * to input all the vote information into each instance of party.
     * Then, it calls DistributeSeats() to determine how many seats each party
     * gets. At the end, it selects the top parties and their elected candidates
     * and send this information to the Report class.
     * Tiebreaking is also implicitly used in case of tied votes.
		 */
		void Audit();

  private:

    /**
		 * @brief  A helper function that is called by Audit().
     * Since at ReadFile(), the parties only recieved a list of ballots,
     * this method counts the ballots and save it as a
     * proper variable within the party class that
     * can be accessed via getters.
     * Acts as a wrapper to clean up Audit() and make it
     * more organized.
		 */
		void PopulateVotes();
    // Number of seats available
		int total_seats_ = 0;
    // Number of voters
    int total_votes_ = 0;
    // used for calculating in auditing
		int quota_ = 0;
};

#endif  // SRC_CPL_H
