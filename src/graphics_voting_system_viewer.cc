/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string>
#include <cmath>

#include "graphics_voting_system_viewer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsVotingSystemViewer::GraphicsVotingSystemViewer(
    VotingSystem * voting_system, Controller * controller) :
    GraphicsApp(X_DIM, Y_DIM, "Voting System"), controller_(controller),
    voting_system_(voting_system) {

  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
      gui->addWindow( Eigen::Vector2i(MENU_X_POS, MENU_Y_POS), "Menu");
  // vvvvvvvvvvvv    ADDED THIS ONE LINE to register the window  vvvvvvvvvvvv
  // gui->addGroup creates a heading within the window
  window->setLayout(new nanogui::GroupLayout());

  // MENU - Buttons drawing
  gui->addGroup("Voting System Control");
  open_file_button_ = gui->addButton(
      "Open File",
      std::bind(&GraphicsVotingSystemViewer::OnOpenBtnPressed, this));
  run_audit_button_ =  gui->addButton(
      "Run Audit",
      std::bind(&GraphicsVotingSystemViewer::OnAuditBtnPressed, this));
  export_audit_button_ =  gui->addButton(
      "Export Audit",
      std::bind(&GraphicsVotingSystemViewer::OnExportAuditBtnPressed, this));
  export_sharing_button_ =  gui->addButton(
      "Export Sharing",
      std::bind(&GraphicsVotingSystemViewer::OnExportSharingBtnPressed, this));
  reset_button_ =  gui->addButton(
      "Reset",
      std::bind(&GraphicsVotingSystemViewer::OnRestartBtnPressed, this));
  exit_button_ =  gui->addButton(
      "Exit",
      std::bind(&GraphicsVotingSystemViewer::OnExitBtnPressed, this));
  // Screen size
  screen()->setSize({SCREEN_SIZE_X, SCREEN_SIZE_Y});
  // Without fixing the width, the button will span the entire window
  open_file_button_->setFixedWidth(DEFAULT_BUTTON_SIZE);
  run_audit_button_->setFixedWidth(DEFAULT_BUTTON_SIZE);
  export_audit_button_->setFixedWidth(DEFAULT_BUTTON_SIZE);
  export_sharing_button_->setFixedWidth(DEFAULT_BUTTON_SIZE);
  reset_button_->setFixedWidth(DEFAULT_BUTTON_SIZE);
  exit_button_->setFixedWidth(DEFAULT_BUTTON_SIZE);
  // vvvvvvvvvv  ADDED BELOW HERE (from nanogui example1.cc)   vvvvvvvvvvvvvvvv
  // // Creating a panel impacts the layout. Widgets, sliders, buttons can be
  // // assigned to either the window or the panel.

  // STATUS - Buttons + textboxes drawing
  window = gui->addWindow(
           Eigen::Vector2i(MENU_X_POS, MENU_Y_POS),
           "Status");
  window->setPosition( Eigen::Vector2i(STATUS_X_POS,STATUS_Y_POS));
  gui->addGroup("Process Status");
  window->setLayout(new nanogui::GroupLayout());

  // New panel
  nanogui::Widget *panel = new nanogui::Widget(window);
   /* FP widget */ {
  new nanogui::Label(panel, "File Selected :", "sans-bold");
  textBox1 = new nanogui::TextBox(panel);
  textBox1->setFixedSize(nanogui::Vector2i(TEXTBOX_SIZE_X, TEXTBOX_SIZE_Y));
  textBox1->setValue(voting_system_->open_file_status_);

  new nanogui::Label(panel, "Election Result :", "sans-bold");
  textBox2 = new nanogui::TextBox(panel);
  textBox2->setFixedSize(nanogui::Vector2i(TEXTBOX_SIZE_X, TEXTBOX_SIZE_Y));
  textBox2->setValue(voting_system_->run_audit_status_);

  new nanogui::Label(panel, "Audit File Saved :", "sans-bold");
  textBox3 = new nanogui::TextBox(panel);
  textBox3->setFixedSize(nanogui::Vector2i(TEXTBOX_SIZE_X, TEXTBOX_SIZE_Y));
  textBox3->setValue(voting_system_->audit_save_file_status_);

  new nanogui::Label(panel, "Sharing File Saved :", "sans-bold");
  textBox4 = new nanogui::TextBox(panel);
  textBox4->setFixedSize(nanogui::Vector2i(TEXTBOX_SIZE_X, TEXTBOX_SIZE_Y));
  textBox4->setValue(voting_system_->sharing_save_file_status_);

  // Panel layout
  nanogui::GridLayout *layout =
     new nanogui::GridLayout(nanogui::Orientation::Horizontal, 2,
                    nanogui::Alignment::Maximum, 10, 5);
  layout->setColAlignment(
     { nanogui::Alignment::Maximum, nanogui::Alignment::Maximum });
  layout->setSpacing(0, 10);
  panel->setLayout(layout); }

  // PERFROMING SCREEN
  screen()->performLayout();
} /* GraphicsVotingSystemViewer() */

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the menu.
// It will be called at each iteration of nanogui::mainloop()
  void GraphicsVotingSystemViewer::UpdateSimulation(double dt) {
    controller_->AdvanceTime(dt);
  } /* UpdateSimulation() */

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsVotingSystemViewer::OnRestartBtnPressed() {
  controller_->AcceptCommunication(bButtonRestart);
} /* OnRestartBtnPressed() */

void GraphicsVotingSystemViewer::OnOpenBtnPressed() {
  controller_->AcceptCommunication(bButtonOpen);
} /* OnOpenBtnPressed() */

void GraphicsVotingSystemViewer::OnExportAuditBtnPressed() {
  controller_->AcceptCommunication(bButtonExportAudit);
} /* OnExportAuditBtnPressed() */

void GraphicsVotingSystemViewer::OnExportSharingBtnPressed() {
  controller_->AcceptCommunication(bButtonExportSharing);
} /* OnExportSharingBtnPressed() */

void GraphicsVotingSystemViewer::OnAuditBtnPressed() {
  controller_->AcceptCommunication(bButtonAudit);
} /* OnAuditBtnPressed() */

void GraphicsVotingSystemViewer::OnExitBtnPressed() {
  std::cout << "Starting Exit..." << std::endl;
  /* @ TODO: Make sure everything have clean up before closing
   *
   */
  std::cout << "SAFE. GOOD BYE!!!" << std::endl;
  exit(1);
} /* OnExitBtnPressed() */

/*******************************************************************************
 * Drawing the VotingSystem Control menu
 ******************************************************************************/
void GraphicsVotingSystemViewer::UpdateStatus(){
  // update all textbox status
  textBox1->setValue(voting_system_->open_file_status_);
  textBox2->setValue(voting_system_->run_audit_status_);
  textBox3->setValue(voting_system_->audit_save_file_status_);
  textBox4->setValue(voting_system_->sharing_save_file_status_);
} /* UpdateStatus() */

void GraphicsVotingSystemViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  UpdateStatus();
} /* DrawUsingNanoVG() */
