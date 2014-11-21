/***************************************************************************
                              ExercisePercentage.h
                             -------------------
    begin                : 2008/10/10
    copyright            : (C) 2008 by Tiago Porangaba
    email                : tiago.porangaba@ltia.fc.unesp.br
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef EXERCISEPERCENTAGE_H
#define EXERCISEPERCENTAGE_H

#include "ExerciseBase.h"
#include "Ratio.h"

#include <QLabel>

class RationalWidget;
class ResultWidget;

class QLineEdit;

class QGridLayout;
class QLabel;
class QPushButton;

/*! Construct the exercise widget to work with percentage
 *
 *  \author Sebastian Stein
 *  \author Tiago Porangaba
 * */
class ExercisePercentage : public ExerciseBase
{
    Q_OBJECT

public:
    /** constructor */
    explicit ExercisePercentage(QWidget * parent = 0);

    /** destructor */
    ~ExercisePercentage();

    /** force the creation of a new task */
    void forceNewTask();

    void update();

Q_SIGNALS:
    /** class emits this signal, if the task was solved correctly by the user */
    void signalExerciseSolvedCorrect();

    /** class emits this signal, if the task was skipped by the user */
    void signalExerciseSkipped();

    /** class emits this signal, if the task was solved not correctly by the user
     * */
    void signalExerciseSolvedWrong();

private:
    short m_currentState;

    Ratio m_result;

    QString m_numberPercentage;
    QString m_numberPercentageOf;
    QString m_resultPercentage;

    QLabel * m_taskLabel;

    RationalWidget * m_rationalWidget;
    ResultWidget * m_resultWidget;
    QFrame * edit_line;
    QLineEdit * answer_edit;

    QPushButton* m_checkButton;
    QPushButton* m_skipButton;

    QGridLayout* checkLayout;
    QGridLayout* taskLayout;
    QGridLayout* baseGrid;

    QWidget * checkWidget;
    QWidget * taskWidget;

    void createTask();
    void showResult();
    void nextTask();

    void slotCheckButtonClicked();
    void slotSkipButtonClicked();
    void answerReturnPressed();
};

#endif

