#pragma once

#include <vector>
#include "../commands/command/command.h"
#include "../target/target.h"

class parser
{
public:
    parser(int argc, char* argv[], std::vector<command*>& commands, target& targets);

    void run();
    const std::vector<std::string>& getTargets() const;
    bool isCommandActive(const std::string& comName) const;

private:
    int m_argc;
    char** m_argv;
    // We store 'command*' and not 'const' one because when we call the 'actionToDo' or 'initClass' function the user
    // may want to change things in the class, so it needs to be not 'const'.
    std::vector<command*>& m_commands;
    // target need to be modified when we read the command line, so it's not 'const'.
    target& m_targets;
    // Same as 'm_commands'.
    std::vector<command*> m_commandsForLine;
    std::vector<std::string> m_commandsArguments;

    void analyseCommandLine();
    void checkAllNeededCommands();
    void initCommandsArgs();
    void runAllInstanTrigger();
    void runAllDelayedTrigger();

    bool isACommand(const std::string& com) const;
    // Return a copy of the 'com' string but without the '-' or the '--' in front.
    std::string removeCommandSpecifier(const std::string& com);
    command* getCommand(const std::string& comName) const;
};