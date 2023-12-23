#include <iostream>
#include "../lib/commands/command/command.h"
#include "../lib/commands/helpCommand/helpCommand.h"
#include "../lib/parser/parser.h"
#include "commands/helloCommand/helloCommand.h"
#include "commands/instantTriggerCommand/instantTriggerCommand.h"
#include "commands/laterCommand/laterCommand.h"
#include "commands/requiredCommand/requiredCommand.h"
#include "commands/additionCommand/additionCommand.h"

int main(int argc, char* argv[])
{
    // Declaration of all the commands for this program.
    helpCommand help;

    helloCommand helloC;

    instantTriggerCommand itC;

    laterCommand laterC;

    requiredCommand requiredC;

    additionCommand addC;

    // We put all the commands in one list.
    std::vector<command*> vectorCom = {&help, &helloC, &itC, &laterC, &requiredC, &addC};

    // We give a description for the target files and we precise if target files can be empty or not.
    target t("Target description.", false);

    // We give the parser the command line, the list of commands and the targets.
    parser p(argc, argv, vectorCom, t);
    p.run();

    // Start of our program after the parser.
    std::cout << std::endl << "Test Program - HERVOUET Léo" << std::endl << std::endl;


    std::cout << "Display of all the targets: " << std::endl;
    std::vector<std::string> targ = p.getTargets();
    for(const std::string& tar : targ)
    {
        std::cout << tar << std::endl;
    }

    // If 'later' is in the command line, we display a message.
    if(p.isCommandActive("later"))
    {
        std::cout << "Special treament for the command 'later'." << std::endl;
    }

    return 0;
}
