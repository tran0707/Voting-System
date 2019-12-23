/**
 * @file report.h
 * @author Team#22
 * @brief Report Class
 * @version 0.1
 * @date 2019-11-09
 *
 * @copyright Copyright (c) 2019
 *
 */
#ifndef SRC_REPORT_H_
#define SRC_REPORT_H_

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "party.h"
#include "candidate.h"
#include "common.h"

/**
 * @brief The Report mainly handles outputs to the display.
 * It prints out the winners recieved from the OPL/CPL class.
 * It formats differently depending on which voting method is used.
 */
class Report {
 public:
   /**
   * @brief Report is a Constructor that holds 7 arguments to mainly handles
   * outputs to the display.
   */
	Report(std::vector <Party> all_parties_vec, std::vector <Party> winner_vec,
        std::string vote_type, int total_candidates, int nballots, int total_seats, std::string file);
  Report() {}
	~Report() {}
    /**
     * @brief Get the All Candidate Party object
     *
     * @return std::vector <Party>
     */
    std::vector <Party> GetAllCandidateParty() {return AllCandidateParty;}

    /**
     * @brief Get the Winner Party object
     *
     * @return std::vector <Party>
     */
    std::vector <Party> GetWinnerParty() {return Winner;}

    /**
     * @brief Get the Voting Type object
     *
     * @return std::string
     */
    std::string GetVotingType() {return voting_type;}

    /**
     * @brief Get the Num Total Candidates object
     *
     * @return int
     */
    int GetNumTotalCandidates() {return num_total_candidates;}

    /**
     * @brief Get the Num Ballots object
     *
     * @return int
     */
    int GetNumBallots() {return num_ballots;}

    /**
     * @brief Get the Num Total Seats object
     *
     * @return int
     */
    int GetNumTotalSeats() {return num_total_seats;}

    /**
     * @brief Get the File Auditing object
     *
     * @return std::string
     */
    std::string GetFileAuditing() {return file_auditing;}

    /**
     * @brief Set the Vec All Party object
     *
     * @param allpat
     */
    void SetVecAllParty(std::vector <Party> allpat) {
        AllCandidateParty = {};
        AllCandidateParty = allpat;
    }

    /**
     * @brief Set the Vec Winner Party object
     *
     * @param allpat
     */
    void SetVecWinnerParty(std::vector <Party> allpat) {
        Winner = {};
        Winner = allpat;
    }

    /**
     * @brief Set the Voting Type object
     *
     * @param vtype
     */
    void SetVotingType(std::string vtype) {
        voting_type = vtype;
    }

    /**
     * @brief Set the Num To Tal Candidates object
     *
     * @param total
     */
    void SetNumToTalCandidates(int total) {
        num_total_candidates = total;
    }

    /**
     * @brief Set the Num Ballots object
     *
     * @param ballot
     */
    void SetNumBallots(int ballot) {
        num_ballots = ballot;
    }

    /**
     * @brief Set the Num Total Seats object
     *
     * @param seat
     */
    void SetNumTotalSeats (int seat) {
        num_total_seats = seat;
    }

    /**
     * @brief Set the File Auditing object
     *
     * @param file
     */
    void SetFileAuditing (std::string file) {
        file_auditing = file;
    }
    /**
     * @brief audit the filename
     *
     * @param name
     */
    void SetAuditFileName (std::string name) {
       audit_result_file_name_ = name;
    }
    /**
     * @brief sharing the file name
     *
     * @param name
     */
    void SetSharingFileName (std::string name) {
       sharing_result_file_name_ = name;
    }

    /**
     * @brief Use to find max length of Party name
     *
     * @param c1
     * @param c2
     * @return true
     * @return false
     */
    static bool Candidate_comparator(Candidate& c1, Candidate& c2);

    /**
     * @brief Find the longest string when concat all name for each party CPL
     *
     * @param pa
     * @return int
     */
    int FindLongestCPLCandidateName(std::vector <Party> pa);
    /**
     * @brief Display information of the current voting to terminal
     *
     */
    void Display();
    /**
     * @brief Export Audit File to the same directotry
     *
     */
    void ExportToAuditFile();
    /**
     * @brief Export a public file to share result
     *
     */
    void ExportToPublicFile();
    /**
     * @brief Export a short report file for the election officials
     *
     */
    void ExportToShortReport();

    /**
     * @brief Extract Filename.csv to Filename only
     *
     * @param file
     * @return std::string
     */
    std::string ExtractFileName(std::string file);
 private:

   /**
    * @brief Get the current Date and Time
    *
    * @return std::string
    */
   std::string CurrentDateTime();
   /**
    * @brief display OPL voting type to the screen by reporting the winners
    * and all the neccesary information for OPL party to the screen
    */
    void DisplayOPL();
    /**
     * @brief display CPL voting type to the screen by reporting the winners
     * and all the neccesary information for CPL party to the screen
     */
    void DisplayCPL();
    /**
     * @brief display all general information for each party
     */
    void DisplayGeneral();

    /**
     * @brief export to audit file for OPL party by providing all neccesary
     * information and the voting result related to OPL party into the file
     */
    void ExportToAuditFileOPL();
    /**
     * @brief export to audit file for CPL party by providing all neccesary
     * infomation and voting result related to CPL party into the file
     */
    void ExportToAuditFileCPL();
    /**
     * @brief concatenate the string of ballot id to integer
     */
    std::string ConcatListInt(std::vector <int> intList);

    //! A Vector Party that contain all Candidates and Parties
    std::vector <Party> AllCandidateParty{};
    //! A Vector Party contain all Winner Candidates and Parties
    std::vector <Party> Winner{};
    //! String for the type of voting
    std::string voting_type{""};
    //! Int for total number of candidates
    int num_total_candidates{0};
    //! Int for total number of ballots run
    int num_ballots{0};
    //! Int for the total number available seats
    int num_total_seats{0};
    //! String file name that gets audit
    std::string file_auditing{""};
    // the filename of audit result
    std::string audit_result_file_name_{"audit_result.txt"};
    // the filename of sharing the report result
    std::string sharing_result_file_name_{"sharing_result.txt"};
};

#endif // SRC_REPORT_H_
