#ifndef TOOLS_SUITE_UNABLETOBALANCEEXCEPTION_H
#define TOOLS_SUITE_UNABLETOBALANCEEXCEPTION_H

#include <exception>
#include <iostream>
#include <string>

class UnableToBalanceException : public std::exception {
public:
    explicit UnableToBalanceException(const std::string &message);

    friend std::ostream &operator<<(std::ostream &stream, const UnableToBalanceException &e);

    const std::string &getMessage() const;

private:
    std::string message;

};

#endif //TOOLS_SUITE_UNABLETOBALANCEEXCEPTION_H
