#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <iostream>


namespace Ehsan
{
    class MyException : public std::exception{};
    class CantUnionSameGroup : public MyException
    {
        public:
        const char* what() const noexcept
        {
            return "A game related error has occurred: CanUnionSameGroup";
        }
    };
    class GroupDoesntExist : public MyException
    {
        public:
        const char* what() const noexcept
        {
            return "A game related error has occurred: GroupDoesntExist";
        }
    };
    
   
    
    


} // namespace Ehsan


#endif