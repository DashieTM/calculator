#include "calc.hpp"
#include <gtkmm.h>
class MyWindow : public Gtk::Window {
  
  protected:
    std::string result;
    bool result_shown;
    bool menu_shown;
    calc* calculator;
  
  private:
  
  public:
  MyWindow();
  void on_button_clicked();
  void on_clear_clicked();
  void on_delete_clicked();
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
  void on_menu_clicked();
  void on_enter_pressed();
  void on_varenter_pressed();
  Gtk::Button m_button;
  Gtk::Button m2_button;
  Gtk::Button m3_button;
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
  Gtk::MenuButton menu_button;
  Gtk::PopoverMenu menu;
  Gtk::Box menuBox;
  Gtk::Entry varEntry;
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

  class Columns : public Gtk::TreeModel::ColumnRecord {
    public:
      Columns() {
        add(key);
        add(value);
      }

      Gtk::TreeModelColumn<std::string> key;
      Gtk::TreeModelColumn<std::string> value;
  };

  Columns varList;
  Gtk::TreeView treeView;
  Glib::RefPtr<Gtk::ListStore> treeModel;
  void get_list();



};
