/**
 * @file voting_system.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

#ifndef SRC_VOTING_SYSTEM_H_
#define SRC_VOTING_SYSTEM_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>
#include "communication.h"
#include "params.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main controller class for Voting System
 *
 * When the main function run, this will call the Voting System Controller
 * Run() method.
 */

class VotingSystem {
public:
	/**
	 * @brief default Constructor.
	 *
	 */
	explicit VotingSystem();

	/**
	* @brief VotingSystem's destructor. `delete` all objects created.
	*/
	~VotingSystem();

	/**
   * @brief Run every steps of voting system.
	 * Readfile -> Audit -> Display result -> Export Audit file -> Export Sharing
	 * file
   */
	void RunAuditProcess();

	/**
	 * @brief Set the input file_name
	 *
	 * @param file name
	 */
	void SetFileName(std::string name) {
			input_file_name_ = name;
	}

	/**
	 * @brief Getter file_name
	 */
	std::string GetFileName() {return input_file_name_;}

	/**
 	* @brief Recieve a command from user and handle it
 	*/
	void AcceptCommand(Communication com);

	/**
 * @brief Advance the simulation by the specified # of steps.
 *
 * @param[in] dt The # of steps to increment by. This is
 * practically unused because the arena state is advanced
 * incrementally at a fixed rate.
 *
 * If `dt == 0`, `return` immediately. Otherwise calls
 * VotingSystem::....() once to update
 */
	void AdvanceTime(double dt);

	/**
 * @brief Reset all variables in VotingSystem.
 */
	void Reset();

	/**
 	* All public variable which can be extracted from Graphic viewer to
	* display information
 	*/
	std::string open_file_status_ { DEFAULT_OPEN_FILE_STATUS };
	std::string audit_save_file_status_ { DEFAULT_SAVE_FILE_STATUS };
	std::string sharing_save_file_status_ { DEFAULT_SAVE_FILE_STATUS };
	std::string run_audit_status_ { DEFAULT_AUDIT_FILE_STATUS };

private:
	/**
	 * @brief Check whether this is a valid file name (file can be opened)
	 *
	 * @param file_name the file name need to be checked
	 *
	 * @return True if user inputs a valid file name, False if user's input is
	 * invalid.
	 */
	bool IsFileValid(const std::string& file_name);

	/**
	* @brief Check the input filename format which is ".csv" format
	*
	* @return bool types (true or false)
	*/
	bool CheckInputFilenameFormat (std::string filename);

	/**
	* @brief Check the output filename format which is ".txt" format
	*
	* @return bool types (true or false)
	*/
	bool CheckOutputFilenameFormat (std::string filename) ;
	
	/**
	 * @brief Promt to GUI for user to select the Input Filename
	 *
	 * @return a path of the file where it is located in the directory
	 */
	std::string SelectingFileForOpening() ;

	/**
	 * @brief Promt to GUI for user to select the Saving audit Filename
	 *
	 * @return a path of the file where it is located in the directory
	 */
	std::string SelectingDirectoryForSavingAudit();
	/**
	 * @brief Promt to GUI for user to select the Sharing filename
	 *
	 * @return a path of the file where it is located in the directory
	 */
	std::string SelectingDirectoryForSavingSharing();

	// Used to hold the input file name which the user enter from terminal
	std::string input_file_name_ { INPUT_FILE_NAME };
	// Used to hold the audit file name which will be exported after auditting
	std::string audit_file_name_ { AUDIT_FILE_NAME  };
	// Used to hold the sharing file name which will be exported after auditting
	std::string sharing_file_name_ { SHARING_FILE_NAME };

};

#endif  // SRC_VOTING_SYSTEM_H_
