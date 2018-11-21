#include <iostream>

#include "hashmap.h"
#include "binarysearchtree.h"
#include "trail.h"
#include "menu.h"

int main(int argc, char **argv) {
  IHashMap<const char *, Trail *> *pHashMap;
  IBinarySearchTree<float, Trail *> *pBinarySearchTree;
  IMenu *pMenu;
  
  while (pMenu->IsMenuRunning()) {
    pMenu->Print();
    MenuOption::Type option = pMenu->ReadMenuOption();
    pMenu->ProcessMenuOption(option);
  }

  return 0;
}