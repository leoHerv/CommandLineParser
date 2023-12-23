#pragma once

#include "../command/command.h"
#include "../../target/target.h"

class helpCommand : public command
{
public:
    helpCommand();

    void actionToDo();
    int initClass([[maybe_unused]] const std::vector<std::string>& arg);
    int initClass(const std::string& programPath, const std::vector<command*>& coms, const std::string& targetDescription);

private:
    // They need to be modified when 'initClass' is call, so they are not 'const' and a reference because they cannot
    // be initialized in the constructor.
    std::vector<command*> m_commands;
    std::string m_programPath;
    std::string m_targetDescription;
};