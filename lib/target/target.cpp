#include "target.h"

//=== PUBLIC ===//

/** To construct target, we take a description to have a description of what the user need and
 * if the targets can be empty or not. */
target::target(const std::string& description, bool canBeEmpty) : m_description(description), m_canBeEmpty(canBeEmpty)
{
    // 'm_targets' is initialized as empty.
}

/** Add a target to the target vector. */
void target::add(const std::string& target)
{
    m_targets.push_back(target);
}

/** Give all the target that we have, we make a copie here so it do not change the original vector of targets. */
const std::vector<std::string>& target::getCibles() const
{
    return m_targets;
}

/** Give the description of the targets. */
const std::string& target::getDescription() const
{
    return m_description;
}

/** Tell is the targets are empty or not. */
bool target::isTargetEmpty() const
{
    return m_targets.empty();
}

/** Tell is the targets can be empty or not. */
bool target::isCanBeEmpty() const
{
    return m_canBeEmpty;
}
