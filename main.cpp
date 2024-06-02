#include <iostream>
#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

struct PromptResult
{
  bool wasKilled;
  int  indexSelected;
};

PromptResult doPrompt(const std::string&              prompt,
                      const std::vector<std::string>& optionList);

int main(int argc, char** argv)
{
  if (argc < 3) {
    std::cerr
        << "Must provide a prompt and at least one option to select from.\n";
    return EXIT_SUCCESS;
  }

  std::vector<std::string> optionList;

  for (int i = 2; i < argc; ++i) {
    optionList.push_back(argv[i]);
  }

  const auto [wasKilled, indexSelected] = doPrompt(argv[1], optionList);

  if (!wasKilled) {
    std::cout << optionList[static_cast<size_t>(indexSelected)] << '\n';
  }

  return EXIT_SUCCESS;
}

PromptResult doPrompt(const std::string&              prompt,
                      const std::vector<std::string>& optionList)
{
  const size_t longestString = std::max(
      prompt.length(),
      std::max_element(optionList.cbegin(),
                       optionList.cend(),
                       [](const std::string& s1, const std::string& s2) {
                         return s1.length() < s2.length();
                       })
          ->length());

  int  selectedIndex = 0;
  bool wasKilled     = true;
  auto screen        = ftxui::ScreenInteractive::TerminalOutput(std::cerr);

  auto menu = ftxui::Menu(&optionList, &selectedIndex)
              | ftxui::CatchEvent([&wasKilled, &screen](ftxui::Event event) {
                  if (event == ftxui::Event::Return) {
                    wasKilled = false;
                    screen.Exit();
                    return true;
                  }
                  
                  // Provides an exit system for PowerShell, which doesn't seem to send
                  // an abort signal when using Ctrl+C. See the comment lower down about
                  // the mouse tracking not being turned off.
                  if (event == ftxui::Event::Escape) {
                    screen.Exit();
                    return true;
                  }
                  return false;
                });

  auto window = ftxui::Renderer(menu, [&menu, &prompt, &longestString] {
    return ftxui::window(ftxui::text(prompt), menu->Render())
           | ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 10)
           | ftxui::size(ftxui::WIDTH,
                         ftxui::LESS_THAN,
                         static_cast<int>(longestString) + 5)
           | ftxui::vscroll_indicator;
  });

  // When running the executable from a separate PowerShell script, the
  // terminal's mouse tracking functionality is never turned off when the
  // program is stopped. I have no idea why this would be the case,
  // but since I'm using this with arrow keys only anyways, I'm just
  // going to disable mouse tracking altogether.
  // screen.TrackMouse(false);
  screen.Loop(window);

  return {wasKilled, selectedIndex};
}