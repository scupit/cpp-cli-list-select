#include <iostream>
#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

int main(int argc, char** argv)
{
  if (argc < 3) {
    std::cerr
        << "Must provide a prompt and at least one option to select from.\n";
    return EXIT_SUCCESS;
  }

  std::vector<std::string> optionList;

  for (int i = 1; i < argc; ++i) {
    optionList.push_back(argv[i]);
  }

  const size_t longestString =
      std::max_element(optionList.cbegin(),
                       optionList.cend(),
                       [](const std::string& s1, const std::string& s2) {
                         return s1.length() < s2.length();
                       })
          ->length();

  int  selected = 0;
  auto screen   = ftxui::ScreenInteractive::TerminalOutput(std::cerr);

  bool wasKilled = true;

  auto menu = ftxui::Menu(&optionList, &selected) | ftxui::frame
              | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 10) | ftxui::border
              | ftxui::size(ftxui::WIDTH,
                            ftxui::LESS_THAN,
                            static_cast<int>(longestString) + 5)
              | ftxui::vscroll_indicator
              | ftxui::CatchEvent([&wasKilled, &screen](ftxui::Event event) {
                  if (event == ftxui::Event::Return) {
                    wasKilled = false;
                    screen.Exit();
                    return true;
                  }
                  return false;
                });

  screen.Loop(menu);

  if (!wasKilled) {
    std::cout << optionList[static_cast<size_t>(selected)] << '\n';
  }

  return EXIT_SUCCESS;
}
