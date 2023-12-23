#pragma once

#include <string>
#include <vector>

class command
{
public:
    command(const std::string& fullName, unsigned short argumentNumber, const std::string& description,
            bool isRequired = false, bool instanTrigger = false, const std::vector<std::string>& shortNames = {});

    /** Action that you need to do with your program when this command is used.*/
    virtual void actionToDo() = 0;
    /** Initialization of the attributes of this class with the arg the user give you.
     * @return : if everything is ok return 0 else a number. */
    virtual int initClass(const std::vector<std::string>& arg) = 0;

    const std::string& getFullName() const;
    const std::vector<std::string>& getShortNames() const;
    unsigned short getArgumentNumber() const;
    const std::string& getDescription() const;
    bool getIsRequired() const;
    bool getInstanTrigger() const;

private:
    // We make a copy of the strings, so the user doesn't need to worry about the scope for those one.
    // It's the same of the vector of 'm_shortNames'.
    const std::string m_fullName;
    const std::vector<std::string> m_shortNames;
    const unsigned short m_argumentNumber;
    const std::string m_description;
    const bool m_isRequired;
    const bool m_instanTrigger;
};