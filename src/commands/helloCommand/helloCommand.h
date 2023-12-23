#include <iostream>
#include "../../../lib/commands/command/command.h"

class helloCommand : public command
{
public:
    helloCommand() : command("hello", 0, "Display 'Hello World !'.",
                             false, false, {"hel"}) {}

    void actionToDo()
    {
        std::cout << ">>> Hello World !" << std::endl;
    }

    int initClass([[maybe_unused]] const std::vector<std::string>& arg)
    {
        // We do nothing here.
        return 0;
    }
};