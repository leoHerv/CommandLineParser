#include <iostream>
#include "parser.h"
#include "../commands/helpCommand/helpCommand.h"

/** To construct parser, we take the command line, all the commands and
 * the targets initialize with a description and if it can be empty or not*/
parser::parser(int argc, char** argv, std::vector<command*>& commands, target& targets) :
    m_argc(argc), m_argv(argv), m_commands(commands), m_targets(targets)
{
    // 'm_commandsForLine' and 'm_commandsArguments' are initialized as empty.
}

//=== PUBLIC ===//

void parser::run()
{
    analyseCommandLine();
    initCommandsArgs();
    checkAllNeededCommands();
    if(!m_targets.isCanBeEmpty())
    {
        if( m_targets.isTargetEmpty())
        {
            std::cout << "Error : target(s) is(are) needed." << std::endl;
            exit(1);
        }
    }
    runAllInstanTrigger();
    runAllDelayedTrigger();
}

/** Give all the targets that the user put in the command line. */
const std::vector<std::string>& parser::getTargets() const
{
    return m_targets.getCibles();
}

/** Look in the commands provided from the user if 'comName' is in it.*/
bool parser::isCommandActive(const std::string& comName) const
{
    for(command* com : m_commandsForLine)
    {
        if(com->getFullName() == comName)
        {
            return true;
        }
    }
    return false;
}

/** Give to all the commands the arguments that we received from the user. */
void parser::initCommandsArgs()
{
    for(command* com : m_commandsForLine)
    {
        int error = 0;
        // If the command is of type helpCommand then we do a specific treatment to print the help.
        helpCommand* hc = dynamic_cast<helpCommand*>(com);
        if(hc)
        {
            error = hc->initClass(m_argv[0], m_commands, m_targets.getDescription());
        }
        else
        {
            unsigned short nbArgs = com->getArgumentNumber();

            // Iterator pointing where we want to separate the vector.
            auto itSeparator = m_commandsArguments.begin() + nbArgs;
            // Separation
            std::vector<std::string> arg(m_commandsArguments.begin(), itSeparator);
            m_commandsArguments.erase(m_commandsArguments.begin(), itSeparator);
            error = com->initClass(arg);
        }
        if(error != 0)
        {
            std::cout << "Error : The arguments of the command " << com->getFullName() << " are invalid." << std::endl;
            exit(error);
        }
    }
}

/** Check in 'm_commandsForLine' if all the commands needed are there. */
void parser::checkAllNeededCommands()
{
    for(command* com : m_commands)
    {
        if(com->getIsRequired())
        {
            bool isUsed = false;
            for(command* comOnLine : m_commandsForLine)
            {
                // If the required command is in the line.
                if(com == comOnLine)
                {
                    isUsed = true;
                    break;
                }
            }
            // If the command is not on the line, we stop the program.
            if(!isUsed)
            {
                std::cout << "Error : -" << com->getFullName() << " command is missing." << std::endl;
                exit(1);
            }
        }
    }
}

/** Run all the functions that need to be run first. */
void parser::runAllInstanTrigger()
{
    for(command* com : m_commandsForLine)
    {
        if(com->getInstanTrigger())
        {
            com->actionToDo();
        }
    }
}

/** Run all the functions that need to be run after the one needed.*/
void parser::runAllDelayedTrigger()
{
    for(command* com : m_commandsForLine)
    {
        if(!com->getInstanTrigger())
        {
            com->actionToDo();
        }
    }
}

/** Look if all the commands in the command line are syntactically valid,
 * init the 'm_commandsNames' list and store all the commands of the line in 'm_commandsForLine'. */
void parser::analyseCommandLine()
{
    for(int i = 1; i < m_argc; i++)
    {
        // For all the commands, we verify if they are correct.
        if(isACommand(m_argv[i]))
        {
            command* com = getCommand(removeCommandSpecifier(m_argv[i]));
            // If the command exist, we store them in 'm_commandsForLine', put the name inside 'm_commandsNames'
            // and go to the next command.
            if(com)
            {
                m_commandsForLine.push_back(com);
                unsigned short argNb = com->getArgumentNumber();
                for(unsigned short y = i+1; y < i+1 + argNb; y++)
                {
                    if(isACommand(m_argv[y]))
                    {
                        std::cout << "Error : invalid number of argument for " << com->getFullName() << "." << std::endl;
                        exit(1);
                    }
                    m_commandsArguments.push_back(m_argv[y]);
                }
                i += com->getArgumentNumber();
            }
            else
            {
                std::cout << "Error : the command " << m_argv[i] << " does not exist." << std::endl;
                exit(1);
            }
        }
        else // Not a command
        {
            int z = i;
            for(; z < m_argc; z++)
            {
                if(!isACommand(m_argv[z]))
                {
                    m_targets.add(m_argv[z]);
                }
                else
                {
                    break;
                }
            }
            if(z != m_argc)
            {
                std::cout << "Error : " << m_argv[i] << " is not a command." << std::endl;
                exit(1);
            }
            else
            {
                break;
            }
        }
    }
}

/** Look if 'com' have a "--" or "-" prefix, which means, this is a command. */
bool parser::isACommand(const std::string& com) const
{
    return com.rfind("--", 0) == 0 || com.rfind('-', 0) == 0;
}

/** Return the command name without the "-" or the "--" if front of the name. */
std::string parser::removeCommandSpecifier(const std::string& com)
{
    std::string res = com;
    if(res.rfind('-', 0) == 0)
    {
        res = res.substr(1, res.size() - 1);
        if(res.rfind('-', 0) == 0)
        {
            res = res.substr(1, res.size() - 1);
        }
    }
    return res;
}

/** Return the command that is link with the 'comName', if 'comName' is not linked with a command we return nullptr*/
command* parser::getCommand(const std::string& comName) const
{
    for(command* command : m_commands)
    {
        if(command->getFullName() == comName)
        {
            return command;
        }
        for(const std::string& shortName : command->getShortNames())
        {
            if(shortName == comName)
            {
                return command;
            }
        }
    }
    return nullptr;
}