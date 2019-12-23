/**
 * @file graphics_arena_viewer.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_GRAPHICS_VOTING_SYSTEM_VIEWER_H_
#define SRC_GRAPHICS_VOTING_SYSTEM_VIEWER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <MinGfx-1.0/mingfx.h>

#include <params.h>
#include "controller.h"
#include "voting_system.h"
#include "common.h"
#include "communication.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

class Controller;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 *  @brief An application that uses the MinGfx library to open up a window that
 *  includes a few buttons for controlling the simulation and can be used to
 *  draw circles and other computer graphics.
 *
 *  After constructing a new GraphicsVotingSystemViewer, call Run to start and run the
 *  application. Run will not return until the application window is closed.
 *  Example:
 *
 *  ```
 *  int main(int argc, char **argv) {
 *      RobotViewer *app = new RobotViewer();
 *      app->Run();
 *      return 0;
 *  }
 *  ```
 *
 *  While the window is open UpdateSimulation will be called repeatedly,
 *  once per frame. Fill this in to update your simulation or perform any other
 *  processing that should happen over time as the simulation progresses.
 *
 *  Fill in the `On*()` methods as desired to respond to user input events.
 *
 *  Fill in the `Draw*()` methods to draw graphics on the screen using
 *  either the `nanovg` library or raw `OpenGL`.
 */
class GraphicsVotingSystemViewer : public GraphicsApp {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A arena_params passed down from main.cc for the
   * initialization of the Arena and the entities therein.
   */
  explicit GraphicsVotingSystemViewer(
                               VotingSystem *voting_system, Controller *controller);

  /**
   * @brief Destructor.
   *
   * `delete` the contained Arena.
   */
  ~GraphicsVotingSystemViewer() override { delete voting_system_; }

  /**
   * @brief Informs the Arena of the new time, so that it can update.
   *
   * @param dt The new timestep.
   */
  void UpdateSimulation(double dt) override;

  /**
   * @brief Handle the user pressing the Open button on the GUI.
   *
   * This will prompt the user to select/search for an input file
   */
  void OnOpenBtnPressed();

  /**
   * @brief Handle the user pressing the Export Audit button on the GUI.
   *
   * This will export audit file to a location user selected.
   * Req: Select before running audit
   */
  void OnExportAuditBtnPressed();

  /**
   * @brief Handle the user pressing the Reset button on the GUI.
   *
   * This will reset the graphics
   */
  void OnRestartBtnPressed();

  /**
   * @brief Handle the user pressing the Audit button on the GUI.
   *
   * This will run the whole audit process base on the user input
   */
   void OnAuditBtnPressed();

   /**
    * @brief Handle the user pressing the Export Sharing button on the GUI.
    *
    * This will export Sharing file to a location user selected.
    * Req: Select before running audit
    */
   void OnExportSharingBtnPressed();

   /**
    * @brief Handle the user pressing the Exit button on the GUI.
    *
    * This will close the graphics, exit the program
    */
   void OnExitBtnPressed();

   /**
    * @brief Auto check status from VotingSystem every timestep then display in
    * corresponding textbox
    */
   void UpdateStatus();

  /**
   * @brief Draw the VotingSystem with all of its entities using `nanogui`.
   *
   * This is the primary driver for drawing all entities in the VotingSystem.
   * It is called at each iteration of `nanogui::mainloop()`.
   *
   * @param[in] ctx Context for nanogui.
   */
  void DrawUsingNanoVG(NVGcontext *ctx) override;

  /**
   * @brief Draw using `OpenGL`. This method is unimplemented, as currently
   * we are doing all drawing with `nanovg` in this application, so it is empty.
   */
  void DrawUsingOpenGL() override {}

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  GraphicsVotingSystemViewer &operator=(
    const GraphicsVotingSystemViewer &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  GraphicsVotingSystemViewer(const GraphicsVotingSystemViewer &other) = delete;

 private:
  // Using for communicating between VotingSystem, controller and graphics
  Controller *controller_{nullptr};
  // Using for communicating between VotingSystem, controller and graphics
  VotingSystem *voting_system_{nullptr};

  // buttons
  nanogui::Button *open_file_button_{nullptr};
  nanogui::Button *run_audit_button_{nullptr};
  nanogui::Button *export_audit_button_{nullptr};
  nanogui::Button *export_sharing_button_{nullptr};
  nanogui::Button *reset_button_{nullptr};
  nanogui::Button *exit_button_{nullptr};
  // status textbox
  nanogui::TextBox *textBox1 {nullptr}; // open file link
  nanogui::TextBox *textBox2 {nullptr}; // open audit status
  nanogui::TextBox *textBox3 {nullptr}; // save audit file link
  nanogui::TextBox *textBox4 {nullptr}; // save sharing file link
};

#endif  // SRC_GRAPHICS_VOTING_SYSTEM_VIEWER_H_
