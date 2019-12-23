/**
 * @file opl.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */
#ifndef SRC_OPL_H
#define SRC_OPL_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include<fstream>
#include "report.h"
#include "party.h"
#include "voting_type.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Open Party List voting. Inherits VotingSystem.
 * This voting method votes only to Candidates. In turn,
 * Candidates will hold vote individual vote count.
 * Also, parties will also hold a sum vote count by their
 * own candidates. This is done to calculate distribution of
 * seats.
 * The information is then sent to the Report class.
 */
class OPL : public VotingType {
  public:
    /**
     * @brief  default Constructor.
     */
		OPL() {}
    /**
    * @brief VotingSystem's destructor. `delete` all objects created.
    */
		~OPL() {}

    /**
	   * @brief Read the file info into some corresponding object.
     * This Readfile is used for OPL voting type.
     *
     * Steps:
     * - 1st Line: OPL for open party listing
     * - 2th Line: Number of Seats
     * - 3rd Line: Number of Ballots
     * - 4th Line: Number of Candidates
     * - Following the 4th line are the candidates info.
     * The candidates and their party are in [ ].
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
     * It distribute seats to parties according to the
     * votes each party gets.
     * It uses the Largest Remainder method to allocate
     * seats for the second distribution after first has been done,
     * when there are still seats remaining.
     * Acts as a wrapper to clean up Audit() and make it
     * more organized.
		 */
    void DistributeSeats();

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

    // std::vector<Party> GetIndexList(std::vector<Party> accum, int rem_seats);
    // Candidate position in list of party <p_pos, c_pos>
    // Provide a faster way to access the candidate in vector <Party> instead of
    // walking though each element
		std::vector <std::pair<int, int>> candidate_pos_{};
    // Number of seats available
    int total_seats_ = 0;
    // Number of voters
    int total_votes_ = 0;
    // used for calculating in auditing
    int quota_ = 0;
};

#endif  // SRC_OPL_H
