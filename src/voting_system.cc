/**
 * @file voting_system.cc
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <list>
#include <time.h>
#include<cstdio>
#include <string>
#include <unistd.h>
#include "communication.h"
#include "voting_system.h"
#include "opl.h"
#include "cpl.h"
#include "params.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
using namespace std;
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
VotingSystem::VotingSystem() { }

VotingSystem::~VotingSystem() { }

/*******************************************************************************
 * Helper Functions
 ******************************************************************************/

using namespace std;
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void VotingSystem::AdvanceTime(double dt) {
   if (!(dt > 0)) {
     return;           // Error time input
   }
   for (size_t i = 0; i < 1; ++i) {
     // TODO: if update something call a function, e.g UpdateEntitiesTimestep();
   } /* for(i..) */
 } /* AdvanceTime() */

 bool VotingSystem::IsFileValid(const std::string& file_name) {
 	ifstream fin;
 	fin.open(file_name);
 	return !fin.fail();
 } /* IsFileValid() */

void VotingSystem::RunAuditProcess() {
	ifstream fin(input_file_name_);
  if (!fin) { // error open file
        cout << "OPS...! Error opening input file." << endl;
        run_audit_status_ = INPUT_ERROR_AUDIT_FILE_STATUS ;
  } else {
    string line;
    getline(fin, line);	// Get the first line to see what voting type is
    if (line=="OPL") { // Run the approriate voting process, OPL
      OPL opl;
      // Set up some value of the report
      opl.report_.SetVotingType("OPL");
      opl.report_.SetAuditFileName(audit_file_name_);
      opl.report_.SetSharingFileName(sharing_file_name_);
      // Read from input file
      opl.ReadFile(input_file_name_);
      // Audit
      opl.Audit();
      // Display
      opl.report_.Display();
      // Report and sharing
      opl.report_.ExportToAuditFile();
      opl.report_.ExportToPublicFile();

      run_audit_status_ = SUCCESS_AUDIT_FILE_STATUS;
    } else {	// Run the approriate voting process, CPL
      CPL cpl;
      // Set up some value of the report
      cpl.report_.SetVotingType("CPL");
      cpl.report_.SetAuditFileName(audit_file_name_);
      cpl.report_.SetSharingFileName(sharing_file_name_);
      // Read from input file
      cpl.ReadFile(input_file_name_);
      // Audit
      cpl.Audit();
      // Display
      cpl.report_.Display();
      // Report and sharing
      cpl.report_.ExportToAuditFile();
      cpl.report_.ExportToPublicFile();
    }
    // Clean up and status
    fin.close();
    fin.clear();
    run_audit_status_ = SUCCESS_AUDIT_FILE_STATUS;
  }
} /* RunAuditProcess() */

bool VotingSystem::CheckInputFilenameFormat (std::string filename) {
  // 4 last chars should be .csv
  if(filename.substr(filename.find_last_of("."),4).compare(CSV) == 0) {
    return true;
  } else {
    std::cout << "Please Enter a Valid Filename's Format (.csv)" << std::endl;
    return false;
  }
} /* CheckInputFilenameFormat */

bool VotingSystem::CheckOutputFilenameFormat (std::string filename) {
  // 4 last chars should be .txt
  if(filename.substr(filename.find_last_of("."),4).compare(TXT) == 0) {
    return true;
  } else {
    std::cout << "Please RE-Enter a Valid Filename's Format (.txt)"
            << std::endl;
    return false;
  }
} /* CheckOutputFilenameFormat */

std::string VotingSystem::SelectingFileForOpening() {
  char filename[MAXIMUM_FILE_NAME_SIZE];
  FILE *f = popen("zenity --file-selection", "r");
  if (fgets(filename, MAXIMUM_FILE_NAME_SIZE, f) == NULL ) { // if cancel
    std::cout << "File Selecting Canceled!" << std::endl;
    return "";
  } else  {
    string converted_filename = filename;
    if (CheckInputFilenameFormat(filename)) { // if file is .csv
      // Remove \n at the end of string then update
      open_file_status_ =
        converted_filename.substr(0,converted_filename.size()-1);
      // Remove \n at the end of string then update
      input_file_name_ = converted_filename.substr(0,
        converted_filename.size()-1);
      return input_file_name_;
    } else { // file is not .csv
      return SelectingFileForOpening();
    }
  }
} /* SelectingFileForOpening() */

std::string VotingSystem::SelectingDirectoryForSavingAudit() {
  char filename[MAXIMUM_FILE_NAME_SIZE];
  // use zenity  to select a save file / audit file
  FILE *f = popen("zenity --file-selection --save", "r");
  if (fgets(filename, MAXIMUM_FILE_NAME_SIZE, f) == NULL ) { // if cancel
    std::cout << "File Selecting Canceled!" << std::endl;
    return "";
  } else  {
    string converted_filename = filename;
    if (CheckOutputFilenameFormat(filename)) {  // if file is .txt
      // Remove \n at the end of string then update
      audit_save_file_status_ =
        converted_filename.substr(0,converted_filename.size()-1);
      // Remove \n at the end of string then update
      audit_file_name_ = audit_save_file_status_;
      return audit_file_name_;
    } else {  // file is not .txt
      return SelectingDirectoryForSavingAudit();
    }
  }
} /* SelectingDirectoryForSavingAudit() */

std::string VotingSystem::SelectingDirectoryForSavingSharing() {
  char filename[MAXIMUM_FILE_NAME_SIZE ];
  // use zenity to select a save file / sharing file
  FILE *f = popen("zenity --file-selection --save", "r");

  if (fgets(filename, MAXIMUM_FILE_NAME_SIZE, f) == NULL ) { // if cancel
    std::cout << "File Selecting Canceled!" << std::endl;
    return "";
  } else  {
    string converted_filename = filename;
    if (CheckOutputFilenameFormat(filename)) { // if file is .txt
      // Remove \n at the end of string then update
      sharing_save_file_status_ =
        converted_filename.substr(0,converted_filename.size()-1);
      // Remove \n at the end of string then update
      sharing_file_name_ = sharing_save_file_status_ ;
      return sharing_file_name_;
    } else { // file is not .txt
      return SelectingDirectoryForSavingSharing();
    }
  }
} /* SelectingDirectoryForSavingSharing() */

void VotingSystem::Reset() {
  std::cout << "Starting Reset Voting System..." << std::endl;
  // Reset all status display in GUI
  open_file_status_ = DEFAULT_OPEN_FILE_STATUS;
  audit_save_file_status_ = DEFAULT_SAVE_FILE_STATUS;
  run_audit_status_ = DEFAULT_AUDIT_FILE_STATUS;
  // Reset all file names
  audit_file_name_ = AUDIT_FILE_NAME ;
  sharing_file_name_ = SHARING_FILE_NAME;
  input_file_name_ = INPUT_FILE_NAME;
  std::cout << "RESET SUCCESS!!!" << std::endl;
} /* Reset() */

// Accept communication from the controller. Dispatching as appropriate.
void VotingSystem::AcceptCommand(Communication com) {
  switch (com) {
    case(kOpen): SelectingFileForOpening(); break;
    case(kSaveAudit): SelectingDirectoryForSavingAudit(); break;
    case(kSaveSharing): SelectingDirectoryForSavingSharing(); break;
    case(kReset): Reset(); break;
    case(kAudit): RunAuditProcess(); break;
    case(kNone): break;
    default: break;
  }
} /* AcceptCommand */
