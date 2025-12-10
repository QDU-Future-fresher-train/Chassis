#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: No description provided
constructor_args: 
  - motor_left: '@&motor'
template_args: []
required_hardware: []
depends: []
=== END MANIFEST === */
// clang-format on

#include "app_framework.hpp"
#include "thread.hpp"
#include "TTMotor.hpp"

class Chassis : public LibXR::Application {
public:
  Chassis(LibXR::HardwareContainer &hw, LibXR::ApplicationManager &app,TTMotor *motor_left):
  motor_left_(motor_left) {
    thread_.LibXR::Thread::Create(this, ThreadFunc, "chassis", 1024,
                                  LibXR::Thread::Priority::MEDIUM);
    app.Register(*this);
  }
  static void ThreadFunc(Chassis *chassis) {
    while (true) {
      chassis->Relax();
      LibXR::Thread::Sleep(100);
    }
  }

  void Relax() {
    motor_left_->Relax();
  }
  void OnMonitor() override {}

private:
  LibXR::Thread thread_;
  TTMotor *motor_left_;
};
