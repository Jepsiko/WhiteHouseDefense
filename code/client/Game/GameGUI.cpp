

#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include "GameGUI.hpp"
#include "../Other/MapGUI.hpp"

GameGUI::GameGUI(bool isSupporter, unsigned seed, GameManager *manager) : AbstractGUI(nullptr),
                                                                          GameUI(isSupporter, seed, manager) {


    mainLayout = new QHBoxLayout();
    leftPanel = new QVBoxLayout;

    //* RIGHT PANEL //*
    /* Player Info */
    actionLayout = new QVBoxLayout; //tower shop + sell/upgrage + spells

    if (!isSupporter) {
        setUpTowerShop();
        setUpDeleteAndUpgradBox();
        setUpSpellsBox();
    } else {
        setUpSpellsBoxForSupporter();
    }

    //* LEFT PANEL //*
    /* Player Info */

    QString playerStatsBoxTitle = QString::fromStdString("Stats");
    playerStatsBox = new QGroupBox(playerStatsBoxTitle);


    setUpStatsBox();


    /* In Game Chat UI */
    QString chatBoxTitle = QString::fromStdString("Chat");
    chatBox = new QGroupBox(chatBoxTitle);
    inGameChatWidget = new InGameChatWidget(manager);

    QHBoxLayout *chatLayout = new QHBoxLayout;
    chatLayout->addWidget(inGameChatWidget);
    chatBox->setLayout(chatLayout);


    leftPanel->addWidget(chatBox);
    leftPanel->setAlignment(inGameChatWidget, Qt::AlignCenter | Qt::AlignTop);

    /* Central Layout */
    QVBoxLayout *centralLayout = new QVBoxLayout;
    setUpHealthBar();
    centralLayout->addWidget(baseHealthBar);
    centralLayout->addStretch();
    map = new MapGUI(seed, this, centralLayout);
    centralLayout->addStretch();


    QVBoxLayout *Vlayout = new QVBoxLayout;
    QMovie *adImage = new QMovie("../../qt_ui/game_pictures/ads/kenoAd.gif");
    QLabel *imageLabel = new QLabel();
    // MAYBE: DYNAMIC CAST??
    imageLabel->setScaledContents(true);
    imageLabel->setMaximumSize((static_cast<MapGUI *> (map))->width(), 250);
    imageLabel->setMovie(adImage);
    adImage->start();
    centralLayout->addWidget(imageLabel);

    otherPlayerHealthBarBox = new QGroupBox;
    setUpOtherPlayerHealthBar();
    centralLayout->addWidget(otherPlayerHealthBarBox);


    /* Main Layout */
    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addLayout(centralLayout, 1);
    mainLayout->addLayout(actionLayout, 1);


    this->setLayout(mainLayout);
    //playerInfo->setLayout(playerInfoLayout);

    this->showMaximized();
//    this->showFullScreen();


}

void GameGUI::setUpTowerShop() {
    QString towerShopTitle = QString::fromStdString("Towers Shop");
    towerShop = new QGroupBox(towerShopTitle);
    displayTowerShop();
    actionLayout->addWidget(towerShop);
}


void GameGUI::setUpDeleteAndUpgradBox() {
    QString deleteAndUpgradeTitle = QString::fromStdString("On Tower Actions");
    deleteAndUpgradeBox = new QGroupBox(deleteAndUpgradeTitle);
    displayDeleteAndUpgradeBox();
    actionLayout->addWidget(deleteAndUpgradeBox);
}

void GameGUI::setUpSpellsBox() {
    QString spellBoxTitle = QString::fromStdString("Spells");
    spellBox = new QGroupBox(spellBoxTitle);
    displaySpellBox();
    actionLayout->addWidget(spellBox);
}

void GameGUI::setUpStatsBox() {
    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    usernameL = new QLabel;
    usernameL->setFont(font);

    font.setBold(false);
    font.setPixelSize(15);

    QHBoxLayout *playerStateLayout = new QHBoxLayout;
    playerStateL = new QLabel;
    playerStateL->setFont(font);
    playerStateLayout->addWidget(playerStateL);
    playerStatsBox->setLayout(playerStateLayout);

    leftPanel->addWidget(usernameL);
    leftPanel->addWidget(playerStatsBox);

    leftPanel->setAlignment(usernameL, Qt::AlignCenter | Qt::AlignTop);
    leftPanel->setAlignment(playerStateL, Qt::AlignCenter | Qt::AlignTop);
}


Position GameGUI::getPosBuyingTower() {
    return Position();
}

void GameGUI::displayPlayersPlacingTowersMessage() {

}

///HEALTH BARS
void GameGUI::setUpHealthBar() {
    baseHealthBar = new QProgressBar;
    baseHealthBar->setStyleSheet(QString("QProgressBar {color: black}"));
    baseHealthBar->setMaximum(PLAYER_STARTING_HP);
    baseHealthBar->setMinimum(0);
    QPalette p = baseHealthBar->palette();
    p.setColor(QPalette::Highlight, Qt::green);
    baseHealthBar->setPalette(p);
    baseHealthBar->setTextVisible(true);
}

void GameGUI::setUpOtherPlayerHealthBar() {
    QHBoxLayout *layout = new QHBoxLayout;
    for (int i = 0; i < 3; i++) {
        QProgressBar *healthBar = new QProgressBar;
        healthBar->setStyleSheet(QString("QProgressBar {color: black}"));
        healthBar->setMaximum(PLAYER_STARTING_HP);
        healthBar->setMinimum(0);
        QPalette p = healthBar->palette();
        p.setColor(QPalette::Highlight, Qt::green);
        healthBar->setPalette(p);
        healthBar->setTextVisible(true);
        layout->addWidget(healthBar);
        otherPlayerHealthBar.push_back(healthBar);

    }

    otherPlayerHealthBarBox->setLayout(layout);
}

void GameGUI::updateHealthBar(int value) {
    baseHealthBar->setValue(value);
    baseHealthBar->setFormat("HP : " + QString::number(value) + "/" + QString::number(PLAYER_STARTING_HP));
}

void GameGUI::updateHealthBarOfSupportedPlayer(int value) {
    baseHealthBar->setValue(value);
    baseHealthBar->setFormat(
            "HP of Supported Player : " + QString::number(value) + "/" + QString::number(PLAYER_STARTING_HP));
}

void GameGUI::updateOtherPlayerHealthBar(std::vector<PlayerState> &playerState, int quadrant) {
    int count = 0;
    for (int i = 0; i != playerState.size(); i++) {
        if (i != quadrant) {
            int value = playerState[i].getHp();
            otherPlayerHealthBar[count]->setValue(value);
            otherPlayerHealthBar[count]->setFormat(QString::fromStdString(playerState[i].getUsername())
                                                   + " (" + QString::fromStdString(QUADRANT_NAMES[i]) + ")"
                                                   + " :" + QString::number(value) + "/"
                                                   + QString::number(PLAYER_STARTING_HP));
            count++;
        }
    }
}


Position GameGUI::getPosSellingTower() {
    return Position();
}

void GameGUI::display(GameState &gameState, int quadrant) {
    map->display(gameState, quadrant);
    displayPlayerInfos(gameState, quadrant);
}

void GameGUI::displayTowerShop() {
    int scl = 10;
    QSize size = QSize(1400 / scl, 1060 / scl);
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

    tooltip = "Tower that can attack one npc at the time\nbut deal zone damage around the npc\nwith a middle range and great damages\n";
    tooltip += "\nPrice : " + std::to_string(MISSILE_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(MISSILE_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(MISSILE_TOWER_RANGE);
    tooltip += "\nSub Damage : " + std::to_string(MISSILE_TOWER_SUBDAMAGE);
    tooltip += "\nSub Range : " + std::to_string(MISSILE_TOWER_SUBRANGE);

    missileTowerB = new QCustomButton(3);
    missileTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/missiletower.png"));
    missileTowerB->setIconSize(size);
    missileTowerB->setToolTip(QString::fromStdString(tooltip));
    missileTowerB->setEnabled(false);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(gunTowerB, 0, 0);
    layout->addWidget(sniperTowerB, 0, 1);
    layout->addWidget(shockTowerB, 1, 0);
    layout->addWidget(missileTowerB, 1, 1);
    towerShop->setLayout(layout);

    QObject::connect(gunTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(sniperTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(shockTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(missileTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
}

void GameGUI::displayDeleteAndUpgradeBox() {

    int scl = 10;
    QSize size = QSize(1400 / scl, 1060 / scl);

    deleteTowerB = new QHandPointerButton;
    deleteTowerB->setEnabled(false);
    deleteTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/sell.png"));
    deleteTowerB->setIconSize(size);

    upgradeTowerB = new QHandPointerButton;
    upgradeTowerB->setEnabled(false);
    upgradeTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/upgrade.png"));
    upgradeTowerB->setIconSize(size);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(deleteTowerB, 0, 0);
    layout->addWidget(upgradeTowerB, 0, 1);
    deleteAndUpgradeBox->setLayout(layout);


    QObject::connect(deleteTowerB, SIGNAL(clicked()), this, SLOT(handleSellingTower()));
    QObject::connect(upgradeTowerB, SIGNAL(clicked()), this, SLOT(handleUpgradingTower()));


}

void GameGUI::disableTowerShop() {
    gunTowerB->setEnabled(false);
    sniperTowerB->setEnabled(false);
    shockTowerB->setEnabled(false);
    missileTowerB->setEnabled(false);
}

void GameGUI::enableTowerShop() {
    if (map->getHighlightedPosition() == Position(-1, -1)) { return; }

    int quadrant = manager->getQuadrant();
    if (map->computeQuadrant(map->getHighlightedPosition()) != quadrant) {
        disableTowerShop();
        disableDeleteAndUpgradeBox();
    } else {
        if (manager->isTowerInPosition(manager->getGameState(), map->getHighlightedPosition())) {
            disableTowerShop();
            enableDeleteAndUpgradeBox();
        } else {
            int playerMoney = manager->getGameState().getPlayerStates()[quadrant].getMoney();
            if (playerMoney > GUN_TOWER_PRICE) gunTowerB->setEnabled(true);
            if (playerMoney > SNIPER_TOWER_PRICE) sniperTowerB->setEnabled(true);
            if (playerMoney > SHOCK_TOWER_PRICE) shockTowerB->setEnabled(true);
            if (playerMoney > MISSILE_TOWER_PRICE) missileTowerB->setEnabled(true);
        }
    }
}

void GameGUI::handleBuyingTower(int typeOfTower) {
    switch (typeOfTower) {
        case 0:
            manager->placeGunTower(map->getHighlightedPosition());
            break;
        case 1:
            manager->placeSniperTower(map->getHighlightedPosition());
            break;
        case 2:
            manager->placeShockTower(map->getHighlightedPosition());
            break;
        default:
            manager->placeMissileTower(map->getHighlightedPosition());
            break;
    }
    disableTowerShop();
    enableDeleteAndUpgradeBox();
}

void GameGUI::handleSellingTower() {
    manager->sellTower(map->getHighlightedPosition());
}

void GameGUI::handleUpgradingTower() {
    manager->upgradeTower(map->getHighlightedPosition());
}


void GameGUI::displaySpellBox() {
    int scl = 10;
    QSize size = QSize(1400 / scl, 1060 / scl);
    QGridLayout *layout = new QGridLayout;

    nukeB = new QHandPointerButton;
    nukeB->setEnabled(false);
    nukeB->setIcon(QIcon("../../qt_ui/game_pictures/spells/trumpnuclear.png"));
    nukeB->setIconSize(size);

    freezeB = new QHandPointerButton;
    freezeB->setEnabled(false);
    freezeB->setIcon(QIcon("../../qt_ui/game_pictures/spells/frozentrump.png"));
    freezeB->setIconSize(size);

    airStrikeB = new QHandPointerButton;
    airStrikeB->setEnabled(false);
    airStrikeB->setIcon(QIcon("../../qt_ui/game_pictures/spells/airstrike.png"));
    airStrikeB->setIconSize(size);
    if (manager->getMode() == TEAM_MODE) {
        healTeamB = new QHandPointerButton;
        healTeamB->setIcon(QIcon("../../qt_ui/game_pictures/spells/heal.png"));
        healTeamB->setIconSize(size);
        QObject::connect(healTeamB, SIGNAL(clicked()), this, SLOT(handleHealTeam()));
        layout->addWidget(healTeamB, 1,1);

    }

    layout->addWidget(nukeB, 0, 0);
    layout->addWidget(freezeB, 0, 1);
    layout->addWidget(airStrikeB, 1, 0);

    spellBox->setLayout(layout);

    QObject::connect(nukeB, SIGNAL(clicked()), this, SLOT(handleNukeSpell()));
    QObject::connect(freezeB, SIGNAL(clicked()), this, SLOT(handleFreezeSpell()));
    QObject::connect(airStrikeB, SIGNAL(clicked()), this, SLOT(handleAirStrike()));


}

void GameGUI::handleNukeSpell() {
    manager->nuclearBombSpell();
    playSound("../../qt_ui/game_pictures/sounds/explosion.mp3");
}

void GameGUI::handleFreezeSpell() {
    manager->launchFreezeSpell();
    playSound("../../qt_ui/game_pictures/sounds/freezeSpell.mp3");
}

void GameGUI::handleAirStrike() {
    int targetQuadrant = map->computeQuadrant(map->getHighlightedPosition());
    manager->launchAirStrike(targetQuadrant);
    playSound("../../qt_ui/game_pictures/sounds/airstrike.mp3");
}

void GameGUI::handleHealTeam() {
    manager->launchHealTeam();
    //TODO: rajouter un son
}

void GameGUI::displayPlayerInfos(GameState &gameState, int quadrant) {
    if (!isSupporter()) {
        displayCurrentPlayerInfo(gameState, quadrant);
    } else {
        displayInfoForSupporter(gameState, quadrant);
    }
}

void GameGUI::displayCurrentPlayerInfo(GameState &gameState, int quadrant) {
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

    updateHealthBar(playerState.getHp());
    updateOtherPlayerHealthBar(gameState.getPlayerStates(), quadrant);
}

void GameGUI::displayDeadMessage() {

}

void GameGUI::addChatMessage(const std::string &message, const std::string &sender) {
    inGameChatWidget->addChatMessage(message, sender);
}

void GameGUI::disableNukeSpell() {
    nukeB->setEnabled(false);
}

void GameGUI::enableNukeSpell() {
    nukeB->setEnabled(true);
}

void GameGUI::disableFreezeSpell() {
    freezeB->setEnabled(false);
}

void GameGUI::enableFreezeSpell() {
    freezeB->setEnabled(true);
}

void GameGUI::disableAirStrike() {
    airStrikeB->setEnabled(false);

}

void GameGUI::enableAirStrike() {
    if ((map->isEnemyBaseInHighlightedPosition(manager->getQuadrant())) && (manager->isAirStikeAvailable())) {
        std::cout << "Enabling air strike" << std::endl;
        airStrikeB->setEnabled(true);
    }

}

void GameGUI::disableHealTeam() {
    healTeamB->setEnabled(false);
}

void GameGUI::enableSpells() {
    if (manager->isNukeSpellAvailable()) {
        enableNukeSpell();
    }
    if (manager->isFreezeSpellAvailable()) {
        enableFreezeSpell();
    }
}

void GameGUI::disableSpells() {
    if (manager->isNukeSpellAvailable()) {
        disableNukeSpell();
    }
    if (manager->isFreezeSpellAvailable()) {
        disableFreezeSpell();
    }
}

void GameGUI::disableDeleteAndUpgradeBox() {
    upgradeTowerB->setEnabled(false);
    deleteTowerB->setEnabled(false);
}

void GameGUI::enableDeleteAndUpgradeBox() {
    upgradeTowerB->setEnabled(true);
    deleteTowerB->setEnabled(true);
}


//////////// END OF GAME SCREEN PART //////////////////////

void GameGUI::displayGameOverAndStats(GameState &gamestate) {
    setUpEndOfGameLayout(gamestate);
    switchToEndGameDisplay();
}

void GameGUI::switchToEndGameDisplay() {
    this->hide();
    endofGameWidget = new QWidget;
    endofGameWidget->setLayout(endOfGameLayout);
    endofGameWidget->showMaximized();
}

void GameGUI::setUpEndOfGameLayout(GameState &gameState) {
    endOfGameLayout = new QVBoxLayout;
    setUpWinnerLooserBox(gameState);
    setUpStatsLayout(gameState);
    backToMenu = new QHandPointerButton(QString::fromStdString("Back to menu"));
    endOfGameLayout->addWidget(backToMenu);
    endOfGameLayout->setAlignment(backToMenu, Qt::AlignCenter);
    QObject::connect(backToMenu, SIGNAL(clicked()), this, SLOT(goToMenu()));

}

void GameGUI::setUpWinnerLooserBox(GameState &gameState) {
    winnerLoserInfos = new QGroupBox;
    QHBoxLayout *layout = new QHBoxLayout;
    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    int myQuadrant = manager->getQuadrant();
    std::string info = bool_to_victory_defeat(gameState.getPlayerStates()[myQuadrant].getIsWinner());
    QLabel *label = new QLabel();
    label->setFont(font);
    if (!isSupporter()) {
        label->setText(QString::fromStdString(info));
        if (info == "Victory") label->setStyleSheet("QLabel { color : green; }");
        else label->setStyleSheet("QLabel { color : red; }");
    } else {
        label->setText("Winner: " + QString::fromStdString(manager->getWinner()));
    }

    layout->addWidget(label);

    layout->setAlignment(Qt::AlignCenter);
    winnerLoserInfos->setLayout(layout);
    endOfGameLayout->addWidget(winnerLoserInfos);

}

void GameGUI::setUpStatsLayout(GameState &gameState) {
    setUpstatBox(gameState);
    endOfGameLayout->addWidget(statBox);
}

void GameGUI::setUpstatBox(GameState &gameState) {

    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    statBox = new QGroupBox;

    statsLayout = new QGridLayout;


    /////////PLAYER 1

    int index = 0;
    QString statString1 = "Username : " + QString::fromStdString(gameState.getPlayerStates()[index].getUsername()) + "\n"
                          + "NPC killed : " + QString::number(gameState.getPlayerStates()[index].getNPCKilled()) + "\n"
                          + "Damagage dealt : " + QString::number(gameState.getPlayerStates()[index].getDamageDealt()) + "\n"
                          + "Money spend : " + QString::number(gameState.getPlayerStates()[index].getMoneySpend()) + "\n"
                          + "Towers placed : " + QString::number(gameState.getPlayerStates()[index].getNbTowersPlaced());

    statViewP1 = new QLabel;
    statViewP1->setFont(font);
    statViewP1->setText(statString1);
    QVBoxLayout *statViewP1Layout = new QVBoxLayout();
    statViewP1Layout->addWidget(statViewP1);
    QGroupBox *box1 = new QGroupBox();
    box1->setLayout(statViewP1Layout);
    statsLayout->addWidget(box1, 0, 0);


    /////////PLAYER 2

    index = 1;
    QString statString2 = "Username : " + QString::fromStdString(gameState.getPlayerStates()[index].getUsername()) + "\n"
                          + "NPC killed : " + QString::number(gameState.getPlayerStates()[index].getNPCKilled()) + "\n"
                          + "Damagage dealt : " + QString::number(gameState.getPlayerStates()[index].getDamageDealt()) + "\n"
                          + "Money spend : " + QString::number(gameState.getPlayerStates()[index].getMoneySpend()) + "\n"
                          + "Towers placed : " + QString::number(gameState.getPlayerStates()[index].getNbTowersPlaced());

    statViewP2 = new QLabel;
    statViewP2->setText(statString2);
    statViewP2->setFont(font);
    QVBoxLayout *statViewP2Layout = new QVBoxLayout();
    statViewP2Layout->addWidget(statViewP2);
    QGroupBox *box2 = new QGroupBox();
    box2->setLayout(statViewP2Layout);
    statsLayout->addWidget(box2, 0, 1);


    /////PLAYER 3

    index = 2;
    QString statString3 = "Username : " + QString::fromStdString(gameState.getPlayerStates()[index].getUsername()) + "\n"
                          + "NPC killed : " + QString::number(gameState.getPlayerStates()[index].getNPCKilled()) + "\n"
                          + "Damagage dealt : " + QString::number(gameState.getPlayerStates()[index].getDamageDealt()) + "\n"
                          + "Money spend : " + QString::number(gameState.getPlayerStates()[index].getMoneySpend()) + "\n"
                          + "Towers placed : " + QString::number(gameState.getPlayerStates()[index].getNbTowersPlaced());

    statViewP3 = new QLabel;
    statViewP3->setText(statString3);
    statViewP3->setFont(font);
    QVBoxLayout *statViewP3Layout = new QVBoxLayout();
    statViewP3Layout->addWidget(statViewP3);
    QGroupBox *box3 = new QGroupBox();
    box3->setLayout(statViewP3Layout);
    statsLayout->addWidget(box3, 1, 0);

    /////PLAYER 4

    index = 3;
    QString statString4 = "Username : " + QString::fromStdString(gameState.getPlayerStates()[index].getUsername()) + "\n"
                          + "NPC killed : " + QString::number(gameState.getPlayerStates()[index].getNPCKilled()) + "\n"
                          + "Damagage dealt : " + QString::number(gameState.getPlayerStates()[index].getDamageDealt()) + "\n"
                          + "Money spend : " + QString::number(gameState.getPlayerStates()[index].getMoneySpend()) + "\n"
                          + "Towers placed : " + QString::number(gameState.getPlayerStates()[index].getNbTowersPlaced());

    statViewP4 = new QLabel;
    statViewP4->setText(statString4);
    statViewP4->setFont(font);
    QVBoxLayout *statViewP4Layout = new QVBoxLayout();
    statViewP4Layout->addWidget(statViewP4);
    QGroupBox *box4 = new QGroupBox();
    box4->setLayout(statViewP4Layout);
    statsLayout->addWidget(box4, 1, 1);

    statsLayout->setAlignment(Qt::AlignCenter);

    statBox->setLayout(statsLayout);

}


//////////// SUPPORTER UI PART //////////////////////

void GameGUI::displayInfoForSupporter(GameState &gameState, int quadrant) {
    PlayerState playerSupported = gameState.getPlayerStates()[quadrant];
    std::string &playerSupportedUsrName = playerSupported.getUsername();

    usernameL->setText("You are Supporting " + QString::fromStdString(playerSupportedUsrName)
                       + " (" + QString::fromStdString(QUADRANT_NAMES[quadrant]) + ")");
    usernameL->show();

    std::string text;
    int i = 0;
    for (PlayerState &player : gameState.getPlayerStates()) {
        text += "Player : " + player.getUsername();
        text += "\nMoney : " + std::to_string(player.getMoney()) + " $";
        text += "\nHP : " + std::to_string(player.getHp());
        text += "\nNPC killed : " + std::to_string(player.getPnjKilled());
        text += "\nQuadrant : " + QUADRANT_NAMES[i] + "\n\n";
        i++;
    }

    playerStateL->setText(QString::fromStdString(text));
    playerStateL->show();

    updateHealthBarOfSupportedPlayer(playerSupported.getHp());
    updateOtherPlayerHealthBar(gameState.getPlayerStates(), quadrant);

}

void GameGUI::setUpSpellsBoxForSupporter() {
    supporterActionBox = new QGroupBox();
    displaySupporterActionBox();
    actionLayout->addWidget(supporterActionBox);
}

void GameGUI::displaySupporterActionBox() {
    int scl = 10;
    QSize size = QSize(1400 / scl, 1060 / scl);

    adSpellB = new QHandPointerButton;
    adSpellB->setIcon(QIcon("../../qt_ui/game_pictures/spells/adSpell.jpg"));
    adSpellB->setIconSize(size);
    adSpellB->setEnabled(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(adSpellB, 0, 0);

    supporterActionBox->setLayout(layout);

    QObject::connect(adSpellB, SIGNAL(clicked()), this, SLOT(handleAdSpell()));

}

void GameGUI::handleAdSpell() {
    manager->launchAdSpell();
}

void GameGUI::adPopUp() {
    QWidget *popUpWindow = new QWidget;
    popUpWindow->setFixedSize(500, 500);
    QVBoxLayout *adLayout = new QVBoxLayout;
    QLabel *adPictureLabel = new QLabel;
    if (rand() % 2 == 0){
        adPictureLabel->setPixmap(QPixmap("../../qt_ui/game_pictures/ads/loreal.jpg"));
    } else {
        adPictureLabel->setPixmap(QPixmap("../../qt_ui/game_pictures/ads/Trump-Lego-Box.png"));
    }

    adLayout->addWidget(adPictureLabel);
    popUpWindow->setLayout(adLayout);
    popUpWindow->move(QApplication::desktop()->screen()->rect().center() - popUpWindow->rect().center());
    popUpWindow->setWindowModality(Qt::ApplicationModal);
    popUpWindow->show();
}

void GameGUI::goToMenu() {
    endofGameWidget->close();
    endofGameWidget->deleteLater();
    manager->comeBackToMenu();

}

void GameGUI::playSound(QString musicPath) {

    QMediaPlayer *mediaPlayer = new QMediaPlayer;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo(musicPath).absoluteFilePath()));

    mediaPlayer->setVolume(100);
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->play();
}


