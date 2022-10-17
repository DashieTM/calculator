#include "main.hpp"
#include "Calc.hpp"

MyWindow::MyWindow()
    : m_button("="), m2_button("clear"), m3_button("delete"), sin_button("sin"),
      cos_button("cos"), tan_button("tan"), log_button("log"),
      exp_button("exp"), c1_button("1"), c2_button("2"), c3_button("3"),
      c4_button("4"), c5_button("5"), c6_button("6"), c7_button("7"),
      c8_button("8"), c9_button("9"), c0_button("0"), opl_button("+"),
      omi_button("-"), omu_button("*"), odi_button("/"), omo_button("%"),
      fac_button("!"), obo_button("("), obc_button(")"), dot_button("."),
      menu_button(), box(Gtk::Orientation::VERTICAL),
      menuBox(Gtk::Orientation::VERTICAL), varEntry(), menu(), comboBox(),
      resultWindow(), mainRow(), numberRow1(), numberRow2(), numberRow3(),
      numberRow4(), numberBox(Gtk::Orientation::VERTICAL),
      operatorRow1(Gtk::Orientation::VERTICAL),
      operatorRow2(Gtk::Orientation::VERTICAL), operatorBox(), entryBox() {
  calculator = new Calculator();
  calculator->readVars();
  set_title("Calculator");
  set_default_size(300, 400);
  m_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_button_clicked));
  m2_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_clear_clicked));
  m3_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_delete_clicked));
  sin_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_sin_clicked));
  cos_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_cos_clicked));
  tan_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_tan_clicked));
  log_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_tan_clicked));
  exp_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_exp_clicked));
  c1_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_1_clicked));
  c2_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_2_clicked));
  c3_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_3_clicked));
  c4_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_4_clicked));
  c5_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_5_clicked));
  c6_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_6_clicked));
  c7_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_7_clicked));
  c8_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_8_clicked));
  c9_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_9_clicked));
  c0_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_0_clicked));
  opl_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_plus_clicked));
  omi_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_minus_clicked));
  omu_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_mult_clicked));
  odi_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_div_clicked));
  omo_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_mod_clicked));
  fac_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_fac_clicked));
  obo_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_bropen_clicked));
  obc_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_brclosed_clicked));
  dot_button.signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_dot_clicked));
  menu.signal_show().connect(sigc::mem_fun(*this, &MyWindow::on_menu_clicked));
  entryBox.signal_activate().connect(
      sigc::mem_fun(*this, &MyWindow::on_enter_pressed));
  varEntry.signal_activate().connect(
      sigc::mem_fun(*this, &MyWindow::on_varenter_pressed));

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
  box.append(specialRow);
  specialRow.set_margin_start(10);
  specialRow.set_margin_top(5);
  box.append(comboBox);

  comboBox.append(numberBox);
  comboBox.append(operatorBox);
  box.append(resultWindow);
  resultWindow.set_policy(Gtk::PolicyType::AUTOMATIC,
                          Gtk::PolicyType::AUTOMATIC);
  resultWindow.set_expand();
  resultWindow.set_margin(5);
  resultView.set_editable(false);

  resultWindow.set_child(resultView);
  resultBuffer = Gtk::TextBuffer::create();
  resultView.set_buffer(resultBuffer);

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
  mainRow.append(m3_button);

  specialRow.set_spacing(5);
  specialRow.append(sin_button);
  specialRow.append(cos_button);
  specialRow.append(tan_button);
  specialRow.append(log_button);
  specialRow.append(exp_button);

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
  numberRow4.append(menu_button);
  menu_button.set_popover(menu);
  menu_button.set_label("var");
  menu_button.set_always_show_arrow(false);
  numberRow4.set_spacing(5);

  operatorRow1.append(opl_button);
  operatorRow1.append(omi_button);
  operatorRow1.append(omu_button);
  operatorRow1.append(odi_button);
  operatorRow1.set_spacing(5);

  operatorRow2.append(omo_button);
  operatorRow2.append(fac_button);
  operatorRow2.append(obo_button);
  operatorRow2.append(obc_button);
  operatorRow2.set_spacing(5);

  menu.set_child(menuBox);
  menuBox.append(varEntry);
  menuBox.append(treeView);
  menuBox.set_spacing(5);
  varEntry.set_margin(5);
  treeView.set_margin(5);
  treeView.set_margin_top(0);

  treeModel = Gtk::ListStore::create(varList);
  treeView.set_model(treeModel);

  treeView.append_column("Variable Name", varList.key);
  treeView.append_column("Variable Value", varList.value);

  // main structure:      comboBox:           Numbers:    Operators:
  // EntryBox          Numbers | Operators    Row1        Row1
  // mainRow                                  Row2        Row2
  // specialRow                               Row3        Row3
  // combobox
  // resultList

  // PopupList
  // EntryBox
  // varList
}

MyWindow::~MyWindow() { delete this->calculator; }

int main(int argc, char *argv[]) {
  if (argc > 1) {
    std::string test = argv[1];
    if (test == "--gui") {
      auto app = Gtk::Application::create("org.shitgaem.Calculator");
      argc = 1;
      return app->make_window_and_run<MyWindow>(argc, argv);
    } else if (test == "--fancy") {
      Calculator *calculator = new Calculator();
      calculator->readVars();
      Calculator::greeting();
      calculator->interface(true);
      delete (calculator);
    } else if (test == "--help") {
      std::cout << "--gui GUI version\n"
                   "--fancy fancy oldschool calculator output\n"
                   "None, regular terminal calculator\n";
    } else {
      try {
        std::string expression;
        for (int i = 1; i < argc; i++) {
          expression += argv[i];
        }
        std::cout << Calculator::test_interface(expression) << "\n";
      } catch (std::exception e) {
        return -1;
      }
    }
  } else {
    Calculator *calculator = new Calculator();
    calculator->readVars();
    Calculator::greeting();
    calculator->interface(false);
    delete (calculator);
  }
}

// read the text, check if it is valid, aka not empty and push it to the
// calculator then display the result and flush the string buffer used to enter
// an expression
void MyWindow::on_button_clicked() {
  this->result = this->entryBox.get_text();
  if (this->result != "") {
    this->result = this->calculator->gui(this->result, false);
  } else {
    this->entryBox.set_placeholder_text("Enter an expression.");
    this->result_shown = false;
    return;
  }
  this->entryBox.set_text("");
  if (this->result == "") {
    this->entryBox.set_placeholder_text("Enter an expression.");
  } else {
    this->entryBox.set_placeholder_text("Result: " + this->result);
    this->result = "";
    this->result_shown = true;
  }
  this->setResults(this->calculator->getResults());
}

// flush the buffer to enter
void MyWindow::on_clear_clicked() {
  this->result.clear();
  this->result_shown = false;
  this->entryBox.set_text("");
  this->entryBox.set_placeholder_text("Enter an expression.");
  this->result = "";
}

// popback one element -> char
void MyWindow::on_delete_clicked() {
  this->result = this->entryBox.get_text();
  if (this->result_shown) {
    this->result_shown = false;
    this->result.clear();
    this->entryBox.set_placeholder_text("Enter an expression.");
    return;
  } else if (this->result == "")
    return;
  this->result.pop_back();
  this->entryBox.set_text(this->result);
}

// read the text, check if it is valid, aka not empty and push it to the
// calculator then display the result and flush the string buffer used to enter
// an expression
void MyWindow::on_enter_pressed() {
  this->result = this->entryBox.get_text();
  if (this->result != "") {
    this->result = this->calculator->gui(this->result, false);
  }
  this->entryBox.set_text("");
  if (this->result == "") {
    this->entryBox.set_placeholder_text("Enter an expression.");
  } else {
    this->entryBox.set_placeholder_text("Result: " + this->result);
    this->result_shown = true;
    this->result = "";
  }
  this->setResults(this->calculator->getResults());
}

void MyWindow::on_sin_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "sin(";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_cos_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "cos(";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_tan_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "tan(";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_log_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "log(";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_exp_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "^";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_1_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "1";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_2_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "2";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_3_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "3";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_4_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "4";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_5_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "5";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_6_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "6";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_7_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "7";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_8_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "8";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_9_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "9";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_0_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "0";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_plus_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "+";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_minus_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "-";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_div_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "/";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_mult_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "*";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_mod_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "%";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_fac_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "!";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_bropen_clicked() {
  this->result = this->entryBox.get_text();
  this->result += "(";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_brclosed_clicked() {
  this->result = this->entryBox.get_text();
  this->result += ")";
  this->entryBox.set_text(this->result);
}
void MyWindow::on_dot_clicked() {
  this->result = this->entryBox.get_text();
  this->result += ".";
  this->entryBox.set_text(this->result);
}

void MyWindow::on_menu_clicked() { this->get_list(); }

// handles variable deletion and addition
void MyWindow::on_varenter_pressed() {
  std::string varcommand;
  varcommand = this->varEntry.get_text();
  if (varcommand != "") {
    varcommand = this->calculator->gui(varcommand, true);
    this->get_list();
  }
  this->varEntry.set_text("");
  if (varcommand == "") {
    this->varEntry.set_placeholder_text("enter variable command");
  } else {
    this->varEntry.set_placeholder_text(varcommand);
  }
  varcommand = "";
}

// return the list of results
void MyWindow::get_list() {
  this->treeModel->clear();
  for (auto e : this->calculator->getVars()) {
    auto row = *(this->treeModel->append());
    row[varList.key] = e.first;
    row[varList.value] = e.second;
  }
}

void MyWindow::setResults(std::string str) {
  this->resultBuffer = Gtk::TextBuffer::create();
  this->resultBuffer->set_text(str);
  this->resultView.set_buffer(this->resultBuffer);
}
