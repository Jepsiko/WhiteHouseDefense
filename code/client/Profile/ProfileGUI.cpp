#include <QtCore/QFile>
#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include "ProfileGUI.hpp"

ProfileGUI::ProfileGUI(ProfileManager *manager) : ProfileUI(manager), usernameT(new QString), victoriesT(new QString),
pnjKilledT(new QString) {}

ProfileGUI::~ProfileGUI() {
    close();
}


void ProfileGUI::display() {
    QFile File("../../qt_ui/profile.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    this->setFixedHeight(480);
    this->setFixedWidth(852);
    QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/profile_bckgrd.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QFont police("calibri");

    QFrame *fields = new QFrame(this);
    QFormLayout *fieldsLayout = new QFormLayout(this);

    usernameL = new QLineEdit(fields);
    usernameL->setSelection(0, 10);

    QString usernameString = "Username";
    QString searchButtonString = "SEARCH";

    QLabel *label = new QLabel(fields);
    label->setText(usernameString);
    label->setFont(police);

    searchButton = new QPushButton(searchButtonString, fields);
    searchButton->setFixedSize(QSize(212, 45));

    QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(showUser()));
    QObject::connect(usernameL, SIGNAL(returnPressed()), searchButton, SIGNAL(clicked()));

    fieldsLayout->addRow(label, usernameL);
    fieldsLayout->addRow(searchButton);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 + 105);

    // TODO: add profile data

    *usernameT = QString::fromStdString(profileManager->getUsername());
    *victoriesT = QString::number(profileManager->getVictories());
    *pnjKilledT = QString::number(profileManager->getNPCKilled());

    QLabel *label_username = new QLabel(this);
    label_username->setText(*usernameT);
    label_username->setFont(police);

    label_username->move(this->size().width() / 2 - label_username->width()/2, 30);

    this->show();
}

void ProfileGUI::displayNoSuchProfileError() {
    QMessageBox::critical(this, "No such profile", "Error : There is no profile with that username");
}

void ProfileGUI::updateProfile() {
    *usernameT = QString::fromStdString(profileManager->getUsername());
    *victoriesT = QString::number(profileManager->getVictories());
    *pnjKilledT = QString::number(profileManager->getNPCKilled());
    this->update();
}

void ProfileGUI::showUser() {
    // TODO
}
