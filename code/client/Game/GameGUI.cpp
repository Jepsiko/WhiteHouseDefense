

#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QTimer>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGroupBox>
#include "GameGUI.hpp"
#include "../QCustomButton.h"
#include "../MapGUI.hpp"

GameGUI::GameGUI(unsigned seed, GameManager *manager) : GameUI(seed, manager) {

    playerInfo = new QGroupBox;
    QVBoxLayout* playerInfoLayout = new QVBoxLayout;


    QVBoxLayout *actionLayout  = new QVBoxLayout; //tower shop + sell/upgrage + spells

    QString towerShopTitle = QString::fromStdString("Towers Shop");
    towerShop = new QGroupBox(towerShopTitle);
    actionLayout->addWidget(towerShop);


    QString deleteAndUpgradeTitle = QString::fromStdString("On Tower Actions");
    deleteAndUpgradeBox = new QGroupBox();
    actionLayout->addWidget(deleteAndUpgradeBox);

    QString spellBoxTitle = QString::fromStdString("Spells");
    spellBox = new QGroupBox(this);
    actionLayout->addWidget(spellBox);


    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    usernameL = new QLabel;
    usernameL->setFont(font);

    font.setBold(false);
    font.setPixelSize(15);

    playerStateL = new QLabel;
    playerStateL->setFont(font);

    playerInfoLayout->addWidget(usernameL);
    playerInfoLayout->addWidget(playerStateL);

    playerInfoLayout->setAlignment(usernameL, Qt::AlignCenter|Qt::AlignTop);
    playerInfoLayout->setAlignment(playerStateL, Qt::AlignCenter|Qt::AlignTop);

    playerInfo->setLayout(playerInfoLayout);


    displayTowerShop();
    displayDeleteAndUpgradeBox();


    QHBoxLayout *Mainlayout = new QHBoxLayout;
    Mainlayout->addWidget(playerInfo, 1);
    map = new MapGUI(seed, this, Mainlayout);
    Mainlayout->addLayout(actionLayout, 1);

    this->setLayout(Mainlayout);
    this->showFullScreen();

    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update_map()));
    timer->start(10);
}

Position GameGUI::getPosBuyingTower() {
    return Position();
}

void GameGUI::displayPlayersPlacingTowersMessage() {

}

Position GameGUI::getPosSellingTower() {
    return Position();
}

void GameGUI::display(GameState &gameState, int quadrant) {
    map->display(gameState, quadrant);
}

void GameGUI::displayTowerShop() {
    int scl = 5;
    QSize size = QSize(1400/scl, 1060/scl);
    std::string tooltip;

    tooltip = "Tower that can attack one npc at the time\nwith a small range but with great damages\n";
    tooltip += "\nPrice : " + std::to_string(GUN_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(GUN_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(GUN_TOWER_RANGE);

    gunTowerB = new QCustomButton(0);
    gunTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/guntower.png"));
    gunTowerB->setIconSize(size);
    gunTowerB->setToolTip(QString::fromStdString(tooltip));
    gunTowerB->setEnabled(false);

    tooltip = "Tower that can attack one npc at the time\nwith a great range but with small damages\n";
    tooltip += "\nPrice : " + std::to_string(SNIPER_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(SNIPER_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(SNIPER_TOWER_RANGE);

    sniperTowerB = new QCustomButton(1);
    sniperTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/snipertower.png"));
    sniperTowerB->setIconSize(size);
    sniperTowerB->setToolTip(QString::fromStdString(tooltip));
    sniperTowerB->setEnabled(false);

    tooltip = "Tower that attack all the npc in it's range\nwith a small range and small damages\n";
    tooltip += "\nPrice : " + std::to_string(SHOCK_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(SHOCK_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(SHOCK_TOWER_RANGE);

    shockTowerB = new QCustomButton(2);
    shockTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/shocktower.png"));
    shockTowerB->setIconSize(size);
    shockTowerB->setToolTip(QString::fromStdString(tooltip));
    shockTowerB->setEnabled(false);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(gunTowerB);
    layout->addWidget(sniperTowerB);
    layout->addWidget(shockTowerB);
    layout->addStretch();
    towerShop->setLayout(layout);

    QObject::connect(gunTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(sniperTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(shockTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
}

void GameGUI::displayDeleteAndUpgradeBox() {

    deleteTowerB = new QCustomButton(3);
    deleteTowerB->setEnabled(false);

    upgradeTowerB = new QCustomButton(4);
    upgradeTowerB->setEnabled(false);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(deleteAndUpgradeBox);
    layout->addWidget(upgradeTowerB);
    layout->addStretch();
    deleteAndUpgradeBox->setLayout(layout);


}

void GameGUI::displayGameOver(GameState &gamestate) {

}

void GameGUI::displayPlayerInfos(GameState &gameState, int quadrant) {
    PlayerState playerState = gameState.getPlayerStates()[quadrant];
    std::string &text = playerState.getUsername();

    usernameL->setText(QString::fromStdString(text));
    usernameL->show();

    text = "Money : " + std::to_string(playerState.getMoney()) + " $";
    text += "\nHP : " + std::to_string(playerState.getHp());
    text += "\nNPC killed : " + std::to_string(playerState.getPnjKilled());
    text += "\nQuadrant : " + QUADRANT_NAMES[quadrant];

    playerStateL->setText(QString::fromStdString(text));
    playerStateL->show();
}

void GameGUI::displayInfoForSupporter(GameState &gameState) {

}

void GameGUI::displayDeadMessage() {

}

void GameGUI::update_map() {
    manager->updateMap();
}

void GameGUI::disableTowerShop() {
    gunTowerB->setEnabled(false);
    sniperTowerB->setEnabled(false);
    shockTowerB->setEnabled(false);
}

void GameGUI::enableTowerShop() {
    int playerMoney = manager->getGameState().getPlayerStates()[manager->getQuadrant()].getMoney();
    if (playerMoney > GUN_TOWER_PRICE) gunTowerB->setEnabled(true);
    if (playerMoney > SNIPER_TOWER_PRICE) sniperTowerB->setEnabled(true);
    if (playerMoney > SHOCK_TOWER_PRICE) shockTowerB->setEnabled(true);
}

void GameGUI::handleBuyingTower(int typeOfTower) {
    switch (typeOfTower) {
        case 0:
            manager->placeGunTower(map->getHighlightedPosition());
        case 1:
            manager->placeSniperTower(map->getHighlightedPosition());
        default:
            manager->placeShockTower(map->getHighlightedPosition());
    }
    disableTowerShop();
}

void GameGUI::addChatMessage(const std::string &message, const std::string &sender) {
    // TODO: pour tester, faudra faire la vraie fonction apres
    QString totalMessage(sender.c_str());
    totalMessage.append(": ");
    totalMessage.append(message.c_str());

    QMessageBox::critical(this, "New message", totalMessage);
}


