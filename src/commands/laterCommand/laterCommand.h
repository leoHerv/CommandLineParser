#include <iostream>
#include "../../../lib/commands/command/command.h"

class laterCommand : public command
{
public:
    laterCommand() : command("later", 0, "Display 'Later', at the end of important commands.",
                             false, false, {}) {}

    void actionToDo()
    {
        std::cout << ">>> Later action." << std::endl;
    }

    int initClass([[maybe_unused]] const std::vector<std::string>& arg)
    {
        // We do nothing here.
        return 0;
    }
};