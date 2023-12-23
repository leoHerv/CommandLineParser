#include "command.h"

//=== PUBLIC ===//

command::command(const std::string& fullName, unsigned short argumentNumber, const std::string& description,
                 bool isRequired, bool instanTrigger, const std::vector<std::string>& shortNames) :
                 m_fullName(fullName),
                 m_shortNames(shortNames),
                 m_argumentNumber(argumentNumber),
                 m_description(description),
                 m_isRequired(isRequired),
                 m_instanTrigger(instanTrigger)
{
    // Default init for 'm_commandsForLine' and 'm_commandsArguments'.
}

/** Give the full name of the command. */
const std::string& command::getFullName() const
{
    return m_fullName;
}

/** Give all the short names of the command. */
const std::vector<std::string>& command::getShortNames() const
{
    return m_shortNames;
}

/** Give the number of arguments needed of the command. */
unsigned short command::getArgumentNumber() const
{
    return m_argumentNumber;
}

/** Give the description of the command. */
const std::string& command::getDescription() const
{
    return m_description;
}

/** Tell if the command is required or not. */
bool command::getIsRequired() const
{
    return m_isRequired;
}

/** Tell if action of the command need to be prioritized or not. */
bool command::getInstanTrigger() const
{
    return m_instanTrigger;
}
