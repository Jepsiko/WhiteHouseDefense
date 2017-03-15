#ifndef PROJET_ABSTRACT_GUI_HPP
#define PROJET_ABSTRACT_GUI_HPP


#include <QtWidgets/QWidget>
#include <iostream>
#include "AbstractUI.hpp"

class AbstractGUI : public QWidget, public virtual AbstractUI {
public:
    //virtual void setUp() = 0; // MUST BE IMPLEMENTED IN INHERITORS

    // NE PAS ENLEVER. FONDAMENTAL POUR ASSURER LA DESTRUCTION CORRECTE DES OBJETS;
    virtual ~AbstractGUI() = default;

    void destroy() override;

    virtual void setStylesheetFromPath(QString stylesheetPath);

    virtual void setBackgroundFromPath(QString backgroundPath);

    virtual void setMusicFromPath(QString musicPath);
};


#endif //PROJET_ABSTRACTGUI_HPP
