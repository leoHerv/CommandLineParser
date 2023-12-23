#include <iostream>
#include "../../../lib/commands/command/command.h"

class additionCommand : public command
{
public:
    additionCommand() : command("Addition", 2, "Display the sum of two 'int'. Exemple: -a 1 2.",
                                false, false, {"a", "add"}),
                                m_numberOne(0), m_numberTwo(0) {}

    void actionToDo()
    {
        std::cout << ">>> Addtion of " << m_numberOne << " + " << m_numberTwo << " = " <<
        m_numberOne + m_numberTwo << std::endl;
    }

    int initClass(const std::vector<std::string>& arg)
    {
        for(short i = 0; i < 2; i++)
        {
            try
            {
                int res = std::stoi(arg[i]);
                if(i == 0)
                {
                    m_numberOne = res;
                }
                else
                {
                    m_numberTwo = res;
                }
            }
            catch (const std::invalid_argument& e)
            {
                std::cerr << "Error invalid argument : " << e.what() << std::endl;
                return i;
            }
            catch (const std::out_of_range& e)
            {
                std::cerr << "Error : " << arg[i] << " is to big : " << e.what() << std::endl;
                return i;
            }
        }
        return 0;
    }
private:
    int m_numberOne;
    int m_numberTwo;
};