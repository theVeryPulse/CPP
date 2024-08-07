#pragma once
#ifndef PRESIDENTIAL_PARDON_HPP
#define PRESIDENTIAL_PARDON_HPP

#include "AForm.hpp"

class Bureaucrat;

class PresidentialPardonForm : public AForm
{
  public:
    //--------------- Types: Classes, Enums, and Aliases (using) ---------------
    //----------------- Constructors, Assignments, Destructor ------------------

    PresidentialPardonForm(const std::string& target);
    ~PresidentialPardonForm();
    PresidentialPardonForm(const PresidentialPardonForm& other);
    PresidentialPardonForm& operator=(const PresidentialPardonForm& other);

    //------------------------------- Functions --------------------------------

    void          executeAction() const;
    static AForm* create(const std::string& target);

    //---------------------------------- Data ----------------------------------

  protected:
    //--------------- Types: Classes, Enums, and Aliases (using) ---------------
    //----------------- Constructors, Assignments, Destructor ------------------
    //------------------------------- Functions --------------------------------
    //---------------------------------- Data ----------------------------------

  private:
    //--------------- Types: Classes, Enums, and Aliases (using) ---------------
    //----------------- Constructors, Assignments, Destructor ------------------

    PresidentialPardonForm();

    //------------------------------- Functions --------------------------------
    //---------------------------------- Data ----------------------------------

    const std::string target_;
};

#endif /* PRESIDENTIAL_PARDON_HPP */
