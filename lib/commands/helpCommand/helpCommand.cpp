#include <iostream>
#include "helpCommand.h"

helpCommand::helpCommand() :command("help",0,"Display this information.",
                                 false,true,{"h"})
{
    // 'm_commands', 'm_programPath' and 'm_targetDescription' are initialized as empty.
}

/** Display the commands help for the user. */
void helpCommand::actionToDo()
{
    // 'find_last_of' and 'std::string::npos' return a size_t.
    size_t positionLastSlash = m_programPath.find_last_of("/");

    std::cout << std::endl << "Usage: ";
    // We display the program name.
    if (positionLastSlash != std::string::npos)
    {
        std::cout << m_programPath.substr(positionLastSlash + 1);
    }
    // Else we display a default name.
    else
    {
        std::cout << "programName" << std::endl;
    }
    std::cout << " [options] file..." << std::endl;

    std::cout << "Options: " << std::endl;
    for(command* com : m_commands)
    {
        int namesSize = com->getFullName().length();
        std::cout << "  -" << com->getFullName();
        for(const std::string& sn : com->getShortNames())
        {
            std::cout << ",-" << sn;
            namesSize += sn.length() + 2;
        }
        std::cout << " : ";
        for(int i = namesSize; i < 30; i++)
        {
            std::cout << " ";
        }
        std::cout << com->getDescription() << std::endl;
    }
    std::cout << "Files: " << std::endl << "  " << m_targetDescription << std::endl << std::endl;
}

/** Here initClass do nothing, we have a special treatment in the parser for it. */
int helpCommand::initClass([[maybe_unused]] const std::vector<std::string>& arg)
{
    return 0;
}

/** Initialize all the things that we need to display the help. */
int helpCommand::initClass(const std::string& programPath, const std::vector<command*>& coms, const std::string& targetDescription)
{
    m_commands = coms;
    m_programPath = programPath;
    m_targetDescription = targetDescription;
    return 0;
}
