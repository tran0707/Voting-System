/**
 * @file voting_system.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

#ifndef SRC_VOTING_TYPE_H_
#define SRC_VOTING_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>
#include "report.h"
#include "party.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The generic class of Voting System
 *
 * This class contain general methods and variables which both OPL and CPL use.
 * (e.g both OPL and CPL use same Report object, use same SplitByComma() method
 * for reading information from file)
 *
 * OPL and CPL are inherited from VotingType class.
 */
class VotingType {
	public:
		/**
		 * @brief  default Constructor.
		 */
		VotingType();

		/**
		* @brief VotingType's destructor. `delete` all objects created.
		*/
		virtual ~VotingType();

		/**
	   * @brief Read the file info into some corresponding object. Readfile will
		 * be different depend on CPL or OPL
		 *
		 * @param file_name the file name is used to read
	   */
		virtual void ReadFile(__unused std::string file_name) { }

		// /**
		//  * @brief Audit the ballots infomation after reading to identify winners.
		//  * Audit will be different depend on CPL or OPL
		//  */
		// virtual void Audit() { }

		/**
		 * @brief Random an array/vector of unique number begin from 1.
		 * The length of array are specify by parameter.
		 * (e.g RandomSelectWinner(4) => [4,2,3,1] )
		 *
		 * @param num the length of vector result
		 *
		 * @return A vector of unique integer number.
		 */
		std::vector<int> RandomSelectWinner(int num);

		/**
		 * @brief Split a string with delimiter is comma ","
		 * (e.g "Mike, D, 11" => ["Mike", "D", "11"])
		 *
		 * @param str the string need to be splited
		 *
		 * @return A vector of string of the result after spliting
		 */
		std::vector<std::string> SplitByComma(std::string str);

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
		void DistributeSeatsToParty();
		/**
		 * @brief  This function will check all candidates within the input party,
		 * then see how many seats are assigned to party, start distribute those
		 * seat for candidates within the input party base on candidate priority
		 *
		 * @param p, the party we consider distributing Seats
		 *
		 * @return A new list of party contains only candidate who has a seat
		 */
		Party DistributeSeatToCandidate(Party p);

		/**
		* PUBLIC variable, holding all information of the report
		* after auditing process
		*/
		Report report_{Report()};

	protected:
		// List of all parties (include candidates) information of the election
		std::vector <Party> parties_{};
};

#endif  // SRC_VOTING_TYPE_H_
