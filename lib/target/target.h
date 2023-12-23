#pragma once

#include <string>
#include <vector>

class target
{
public:
    target(const std::string& description, bool canBeEmpty = true);
    void add(const std::string& target);
    const std::vector<std::string>& getCibles() const;
    const std::string& getDescription() const;
    bool isTargetEmpty() const;
    bool isCanBeEmpty() const;

private:
    // 'm_description' is not a reference because we need to have the control on it. So we make a copy in the constructor.
    const std::string m_description;
    const bool m_canBeEmpty;
    std::vector<std::string> m_targets;
};

