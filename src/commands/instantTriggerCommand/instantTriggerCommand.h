#include <iostream>
#include "../../../lib/commands/command/command.h"

class instantTriggerCommand : public command
{
public:
    instantTriggerCommand() : command("instantTrigger", 0, "Display 'Instant Trigger' before the other commands.",
                             false, true, {"it", "trigger"}) {}

    void actionToDo()
    {
        std::cout << ">>> Instant Trigger action." << std::endl;
    }

    int initClass([[maybe_unused]] const std::vector<std::string>& arg)
    {
        // We do nothing here.
        return 0;
    }
};