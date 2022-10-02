// File: main.cc
#include "calc.hpp"
#include <gtkmm.h>
#include <iostream>
#include <string>
class MyWindow : public Gtk::Window {
  
  protected:
    std::string result;
    bool result_shown;
  
  
  private:



  
  public:
  MyWindow();
  void on_button_clicked();
  void on_exit_clicked();
  void on_1_clicked();
  void on_2_clicked();
  void on_3_clicked();
  void on_4_clicked();
  void on_5_clicked();
  void on_6_clicked();
  void on_7_clicked();
  void on_8_clicked();
  void on_9_clicked();
  void on_0_clicked();
  void on_plus_clicked();
  void on_minus_clicked();
  void on_div_clicked();
  void on_mult_clicked();
  void on_mod_clicked();
  void on_bropen_clicked();
  void on_brclosed_clicked();
  void on_dot_clicked();
  void on_enter_pressed();
  Gtk::Button m_button;
  Gtk::Button m2_button;
  Gtk::Button c1_button;
  Gtk::Button c2_button;
  Gtk::Button c3_button;
  Gtk::Button c4_button;
  Gtk::Button c5_button;
  Gtk::Button c6_button;
  Gtk::Button c7_button;
  Gtk::Button c8_button;
  Gtk::Button c9_button;
  Gtk::Button c0_button;
  Gtk::Button opl_button;
  Gtk::Button omi_button;
  Gtk::Button odi_button;
  Gtk::Button omu_button;
  Gtk::Button omo_button;
  Gtk::Button obo_button;
  Gtk::Button obc_button;
  Gtk::Button dot_button;
  Gtk::Entry entryBox;
  Gtk::Box box;
  Gtk::Box comboBox;
  Gtk::Box mainRow;
  Gtk::Box numberRow1;
  Gtk::Box numberRow2;
  Gtk::Box numberRow3;
  Gtk::Box numberRow4;
  Gtk::Box numberBox;
  Gtk::Box operatorRow1;
  Gtk::Box operatorRow2;
  Gtk::Box operatorBox;
};

MyWindow::MyWindow():
  m_button("="),
  m2_button("clear"),
  c1_button("1"),
  c2_button("2"),
  c3_button("3"),
  c4_button("4"),
  c5_button("5"),
  c6_button("6"),
  c7_button("7"),
  c8_button("8"),
  c9_button("9"),
  c0_button("0"),
  opl_button("+"),
  omi_button("-"),
  omu_button("*"),
  odi_button("/"),
  omo_button("%"),
  obo_button("("),
  obc_button(")"),
  dot_button("."),
  box(Gtk::Orientation::VERTICAL),
  comboBox(),
  mainRow(),
  numberRow1(),
  numberRow2(),
  numberRow3(),
  numberRow4(),
  numberBox(Gtk::Orientation::VERTICAL),
  operatorRow1(Gtk::Orientation::VERTICAL),
  operatorRow2(Gtk::Orientation::VERTICAL),
  operatorBox(),
  entryBox()
  {
  set_title("Calculator");
  set_default_size(300, 300);
  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_button_clicked));
  m2_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_exit_clicked));
  c1_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_1_clicked));
  c2_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_2_clicked));
  c3_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_3_clicked));
  c4_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_4_clicked));
  c5_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_5_clicked));
  c6_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_6_clicked));
  c7_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_7_clicked));
  c8_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_8_clicked));
  c9_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_9_clicked));
  c0_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_0_clicked));
  opl_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_plus_clicked));
  omi_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_minus_clicked));
  omu_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_mult_clicked));
  odi_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_div_clicked));
  omo_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_mod_clicked));
  obo_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_bropen_clicked));
  obc_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_brclosed_clicked));
  dot_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MyWindow::on_dot_clicked));
  entryBox.signal_activate().connect( sigc::mem_fun(*this, 
              &MyWindow::on_enter_pressed) );

  // This packs the button into the Window (a container).
  //(m_button);
  set_child(box);
  box.set_spacing(5);
  box.set_margin(5);
  box.append(entryBox);
  entryBox.set_placeholder_text("Enter an expression.");
  entryBox.set_margin_start(10);
  entryBox.set_margin_end(10);
  entryBox.set_margin_top(5);
  box.append(mainRow);
  mainRow.set_margin_start(10);
  mainRow.set_margin_top(10);
  box.append(comboBox);
  
  comboBox.append(numberBox);
  comboBox.append(operatorBox);

  numberBox.append(numberRow1);
  numberBox.append(numberRow2);
  numberBox.append(numberRow3);
  numberBox.append(numberRow4);
  numberBox.set_margin(10);
  numberBox.set_spacing(5);

  operatorBox.append(operatorRow1);
  operatorBox.append(operatorRow2);
  operatorBox.set_margin(10);
  operatorBox.set_spacing(5);

  entryBox.set_editable(true);
  mainRow.set_spacing(5);
  mainRow.append(m_button);
  mainRow.append(m2_button);

  numberRow1.append(c1_button);
  numberRow1.append(c2_button);
  numberRow1.append(c3_button);
  numberRow1.set_spacing(5);
  
  numberRow2.append(c4_button);
  numberRow2.append(c5_button);
  numberRow2.append(c6_button);
  numberRow2.set_spacing(5);

  numberRow3.append(c7_button);
  numberRow3.append(c8_button);
  numberRow3.append(c9_button);
  numberRow3.set_spacing(5);

  numberRow4.append(c0_button);
  numberRow4.append(dot_button);
  numberRow4.set_spacing(5);

  operatorRow1.append(opl_button);
  operatorRow1.append(omi_button);
  operatorRow1.append(omu_button);
  operatorRow1.append(odi_button);
  operatorRow1.set_spacing(5);

  operatorRow2.append(omo_button);
  operatorRow2.append(obo_button);
  operatorRow2.append(obc_button);
  operatorRow2.set_spacing(5);
  // The final step is to display this newly created widget...
  //set_child(box);
}

int main(int argc, char* argv[]) {
  if(argc == 2){
  std::string test =  argv[1];
    if(test == "--gui") {
      auto app = Gtk::Application::create("org.shitgaem.Calculator");
      argc = 1;
      return app->make_window_and_run<MyWindow>(argc, argv);
    } else {
      std::cout << "To run the program in gui launch it with the --gui flag\n Otherwise leave it empty for command line\n";
    }
  } else {
    calc::greeting();
    calc::interface();
  }
}
void MyWindow::on_button_clicked() {
    this->result = calc::gui(this->result);
    this->entryBox.set_text("");
    if(this->result == ""){
      this->entryBox.set_placeholder_text("Enter an expression.");  
    } else {
      this->entryBox.set_placeholder_text(this->result);
    }
    this->result_shown = true;
}

void MyWindow::on_exit_clicked() {
  this->result.clear();
  this->result_shown = false;
  this->entryBox.set_text("");
  this->entryBox.set_placeholder_text("Enter an expression.");
}
void MyWindow::on_enter_pressed() {
  this->result = this->entryBox.get_text();
    this->result = calc::gui(this->result);
    this->entryBox.set_text("");
    if(this->result == ""){
      this->entryBox.set_placeholder_text("Enter an expression.");  
    } else {
      this->entryBox.set_placeholder_text(this->result);
    }
    this->result_shown = true;
}
void MyWindow::on_1_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "1";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_2_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "2";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_3_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "3";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_4_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "4";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_5_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "5";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_6_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "6";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_7_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "7";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_8_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "8";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_9_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "9";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_0_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "0";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_plus_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "+";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_minus_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "-";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_div_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "/";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_mult_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "*";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_mod_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "%";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_bropen_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += "(";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_brclosed_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += ")";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_dot_clicked() {
  if(this->result_shown){
    this->result_shown = false; 
    this->result.clear();
  }
  this->result += ".";
  this->entryBox.set_text(this->result);
}
