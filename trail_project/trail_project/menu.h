#pragma once

class MenuOption {
 public:
  enum Type {
    AddNewData,
    DeleteData,
    Find,
    ListHashSequence,
    ListKeySequence,
    PrintIndentedTree,
    Efficency,
    Quit
  };
};

class IMenu {
public:
  virtual void ProcessMenuOption(MenuOption::Type option) = 0;
  virtual MenuOption::Type ReadMenuOption() = 0;
  virtual bool IsMenuRunning() = 0;
  virtual void Print() = 0;
};
