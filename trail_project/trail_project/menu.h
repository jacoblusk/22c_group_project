#pragma once

enum MenuOption {
  MenuOptionAddNewData,
  MenuOptionDeleteData,
  MenuOptionFind,
  MenuOptionListHashSequence,
  MenuOptionListKeySequence,
  MenuOptionPrintIndentedTree,
  MenuOptionEfficency,
  MenuOptionQuit
};

class IMenu {
public:
  virtual void ProcessMenuOption(MenuOption option) = 0;
  virtual MenuOption ReadMenuOption() = 0;
  virtual bool IsMenuRunning() = 0;
  virtual void Print() = 0;
};
