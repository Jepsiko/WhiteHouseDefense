

#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QTimer>
#include "GameGUI.hpp"
#include "../QCustomButton.h"
#include "../MapGUI.hpp"

GameGUI::GameGUI(unsigned seed, GameManager *manager) : GameUI(seed, manager) {

    playerInfo = new QGroupBox(this);
    towerShop = new QGroupBox(this);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(playerInfo, 1);
    map = new MapGUI(seed, this, layout);
    layout->addWidget(towerShop, 1);

    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    usernameL = new QLabel(playerInfo);
    usernameL->setAlignment(Qt::AlignHCenter);
    usernameL->setFont(font);
    usernameL->show();

    font.setBold(false);
    font.setPixelSize(15);

    playerStateL = new QLabel(playerInfo);
    playerStateL->setFont(font);
    playerStateL->show();

    playerInfo->show();
    towerShop->show();
    this->setLayout(layout);
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
    gunTowerB->show();

    tooltip = "Tower that can attack one npc at the time\nwith a great range but with small damages\n";
    tooltip += "\nPrice : " + std::to_string(SNIPER_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(SNIPER_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(SNIPER_TOWER_RANGE);

    sniperTowerB = new QCustomButton(1);
    sniperTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/snipertower.png"));
    sniperTowerB->setIconSize(size);
    sniperTowerB->setToolTip(QString::fromStdString(tooltip));
    sniperTowerB->setEnabled(false);
    sniperTowerB->show();

    tooltip = "Tower that attack all the npc in it's range\nwith a small range and small damages\n";
    tooltip += "\nPrice : " + std::to_string(SHOCK_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(SHOCK_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(SHOCK_TOWER_RANGE);

    shockTowerB = new QCustomButton(2);
    shockTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/shocktower.png"));
    shockTowerB->setIconSize(size);
    shockTowerB->setToolTip(QString::fromStdString(tooltip));
    shockTowerB->setEnabled(false);
    shockTowerB->show();

    QVBoxLayout *layout = new QVBoxLayout(towerShop);
    layout->addWidget(gunTowerB);
    layout->addWidget(sniperTowerB);
    layout->addWidget(shockTowerB);
    layout->addStretch();

    QObject::connect(gunTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(sniperTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(shockTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
}

void GameGUI::displayGameOver(GameState &gamestate) {

}

void GameGUI::displayPlayerInfos(GameState &gameState, int quadrant) {
    PlayerState playerState = gameState.getPlayerStates()[quadrant];
    std::string text = "\t" + playerState.getUsername();

    usernameL->setText(QString::fromStdString(text));

    text = "\n\n\n\tMoney : " + std::to_string(playerState.getMoney()) + " $";
    text += "\n\tHP : " + std::to_string(playerState.getHp());
    text += "\n\tNPC killed : " + std::to_string(playerState.getPnjKilled());
    text += "\n\tQuadrant : " + QUADRANT_NAMES[quadrant];

    playerStateL->setText(QString::fromStdString(text));
}

void GameGUI::displayInfoForSupporter(GameState &gameState) {

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
            manager->placeGunTower(map->getHighlighted());
        case 1:
            manager->placeSniperTower(map->getHighlighted());
        default:
            manager->placeShockTower(map->getHighlighted());
    }
    disableTowerShop();
}
