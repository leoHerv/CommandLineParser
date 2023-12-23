#include <iostream>
#include "../../../lib/commands/command/command.h"

class requiredCommand : public command
{
public:
    requiredCommand() : command("required", 0, "Display 'Required', this command is required.",
                                true, false, {"r", "req"}) {}

    void actionToDo()
    {
        std::cout << ">>> Required action." << std::endl;
    }

    int initClass([[maybe_unused]] const std::vector<std::string>& arg)
    {
        // We do nothing here.
        return 0;
    }
};