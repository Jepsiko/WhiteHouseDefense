//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_LOGINGUI_HPP
#define PROJET_LOGINGUI_HPP


#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "AbstractGUI.hpp"

class LoginManager;

class LoginGUI : public AbstractGUI {
    Q_OBJECT

public slots:
    void loginUser();

private:
    LoginManager *manager;
    QLineEdit *usernameL;
    QLineEdit *passwordL;
    QPushButton *connect;
    std::string username;
    std::string password;

public:
    LoginGUI(LoginManager *manager);
    void setupGUI();
    std::string getUsername();
    std::string getPassword();
    void displayError();
    void displayAlreadyConnected();
};


#endif //PROJET_LOGINGUI_HPP
