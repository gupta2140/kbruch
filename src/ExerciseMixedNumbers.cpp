/*
    KBruch - exercise to convert mixed numbers in ratios and vice versa
    Copyright 2011 - Sebastian Stein <seb.kde@hpfsc.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "ExerciseMixedNumbers.h"
#include "ExerciseMixedNumbers.moc"

/* these includes are needed for KDE support */
#include <klineedit.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <knumvalidator.h>

/* these includes are needed for Qt support */
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

/* KBruch includes */
#include "settingsclass.h"


/* constructor; build UI for this exercise */
ExerciseMixedNumbers::ExerciseMixedNumbers(QWidget * parent) :
    ExerciseBase(parent)
{
#ifdef DEBUG
    kDebug() << "constructor ExerciseMixedNumbers()";
#endif

    // define initial state
    m_isMixedTask = true;
    m_currentState = _CHECK_TASK;

    // create a new task
    QApplication::setOverrideCursor(Qt::WaitCursor);    // show the sand clock
    createTask();
    QApplication::restoreOverrideCursor(); // show the normal cursor

    // create layout
    //
    // create 2 base widgets
    m_tmpTaskWidget = new QWidget(this);
    m_tmpTaskWidget->setObjectName("m_tmpTaskWidget");
    m_checkWidget = new QWidget(this);
    m_checkWidget->setObjectName("m_checkWidget");

    // add base widgets to base grid layout
    m_baseGrid = new QGridLayout(this);
    m_baseGrid->setObjectName("m_baseGrid");
    m_baseGrid->setColumnStretch(0, 1);
    m_baseGrid->addWidget(m_tmpTaskWidget, 0, 0);
    m_baseGrid->addWidget(m_checkWidget, 0, 1);

    // prepare task layout
    m_taskLayout = new QGridLayout(m_tmpTaskWidget);
    m_taskLayout->setObjectName("m_taskLayout");
    m_taskLayout->setRowStretch(0, 1);
    m_taskLayout->setRowStretch(4, 1);
    m_taskLayout->setColumnStretch(0, 1);
    m_taskLayout->setColumnStretch(5, 1);

    // prepare check layout
    m_checkLayout = new QGridLayout(m_checkWidget);
    m_checkLayout->setObjectName("m_checkLayout");

    // set up task layout
    //
    // create task widget
    m_taskWidget = new TaskWidget(m_tmpTaskWidget, m_task);
    m_taskWidget->setObjectName("m_taskWidget");
    m_taskLayout->addWidget(m_taskWidget, 1, 1, 3, 1);

    // int input validator
    KIntValidator * intValidator = new KIntValidator(this);

    // default font
    QFont defaultFont = SettingsClass::taskFont();
    defaultFont.setBold(true);
    defaultFont.setPointSize(18);

    // input fields for solution
    //
    // integer input
    m_integerEdit = new KLineEdit(m_tmpTaskWidget);
    m_integerEdit->setObjectName("m_integerEdit");
    m_integerEdit->setValidator(intValidator);
    m_integerEdit->setToolTip(i18n("Enter the integer part of the fraction"));
    m_integerEdit->setFont(defaultFont);
    m_integerEdit->setFixedSize(85, 42);
    m_integerEdit->setAlignment(Qt::AlignHCenter);
    QObject::connect(m_integerEdit, SIGNAL(returnPressed(QString)),
                     this, SLOT(integerReturnPressed(QString)));
    m_taskLayout->addWidget(m_integerEdit, 1, 3, 3, 1, Qt::AlignVCenter |
                            Qt::AlignRight);
    m_integerEdit->setEnabled(false);
    m_integerEdit->hide();

    // numerator input
    m_numerEdit = new KLineEdit(m_tmpTaskWidget);
    m_numerEdit->setObjectName("m_numerEdit");
    m_numerEdit->setValidator(intValidator);
    m_numerEdit->setToolTip(i18n("Enter the numerator of the fraction"));
    m_numerEdit->setFont(defaultFont);
    m_numerEdit->setFixedSize(85, 42);
    m_numerEdit->setAlignment(Qt::AlignHCenter);
    QObject::connect(m_numerEdit, SIGNAL(returnPressed(QString)),
                     this, SLOT(numerReturnPressed(QString)));
    m_taskLayout->addWidget(m_numerEdit, 1, 4);

    // add a line between the input boxes
    m_editLine = new QFrame(m_tmpTaskWidget);
    m_editLine->setGeometry(QRect(100, 100, 20, 20));
    m_editLine->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    m_taskLayout->addWidget(m_editLine, 2, 4);

    // denominator input
    m_denoEdit = new KLineEdit(m_tmpTaskWidget);
    m_denoEdit->setObjectName("m_numerEdit");
    m_denoEdit->setValidator(intValidator);
    m_denoEdit->setToolTip(i18n("Enter the denominator of the fraction"));
    m_denoEdit->setFont(defaultFont);
    m_denoEdit->setFixedSize(85, 42);
    m_denoEdit->setAlignment(Qt::AlignHCenter);
    QObject::connect(m_denoEdit, SIGNAL(returnPressed(QString)),
                     this, SLOT(denoReturnPressed(QString)));
    m_taskLayout->addWidget(m_denoEdit, 3, 4);


    // set up check layout
    //
    // add result widget
    m_resultWidget = new ResultWidget(m_checkWidget, ratio());
    m_resultWidget->setObjectName("m_resultWidget");
    m_checkLayout->addWidget(m_resultWidget, 0, 0, 1, 2);

    // new font size
    defaultFont.setPointSize(10);

    // check button
    m_checkButton = new QPushButton(m_checkWidget);
    m_checkButton->setObjectName("m_checkButton");
    m_checkButton->setText(i18n("&Check"));
    m_checkButton->setDefault(true);    // is the default button of the dialog
    m_checkButton->setToolTip(i18n("Click on this button to check your result. The button will not work if you have not entered a result yet."));
    m_checkButton->setFont(defaultFont);
    QObject::connect(m_checkButton, SIGNAL(clicked()), this, SLOT(slotCheckButtonClicked()));
    m_checkLayout->addWidget(m_checkButton, 1, 0);

    // skip button
    m_skipButton = new QPushButton(m_checkWidget);
    m_skipButton->setObjectName("m_skipButton");
    m_skipButton->setText(i18n("&Skip"));
    m_skipButton->setToolTip(i18n("Click on this button to skip this question."));
    m_skipButton->setFont(defaultFont);
    QObject::connect(m_skipButton, SIGNAL(clicked()), this, SLOT(slotSkipButtonClicked()));
    m_checkLayout->addWidget(m_skipButton, 1, 1);

    // add tooltip and qwhatsthis help to the exercise widget
    setToolTip(i18n("In this exercise you have to convert a mixed number into a ratio and vice versa."));
    setWhatsThis(i18n("In this exercise you have to convert a mixed number into a ratio and vice versa. Do not forget to reduce the result."));
}

/* destructor */
ExerciseMixedNumbers::~ExerciseMixedNumbers()
{
#ifdef DEBUG
    kDebug() << "destructor ExerciseMixedNumbers()";
#endif
}

/* handle user action to show a new task */
void ExerciseMixedNumbers::forceNewTask()
{
#ifdef DEBUG
    kDebug() << "forceNewTask ExerciseMixedNumbers()";
#endif

    if (m_currentState == _CHECK_TASK) {
        // emit the signal for skipped
        signalExerciseSkipped();
    }
    m_currentState = _CHECK_TASK;
    m_checkButton->setText(i18n("&Check"));

    // generate next task
    (void) nextTask();
}

/* generate new task */
void ExerciseMixedNumbers::createTask()
{
    // generate ratio; constraints:
    // - reduced
    // - numerator is larger than denominator
    // - denominator is not 1
    ratio tmpRatio = ratio();
    int numerator = 0;
    int denominator = 1;
    do {
        // numerator should be between 1..15
        numerator = int ((double(rand()) / RAND_MAX) * 15 + 1);

        // denominator should be between 1..(numerator-1)
        denominator = int ((double(rand()) / RAND_MAX) * numerator);

        // eventually make ratio negative
        if (double(rand()) / RAND_MAX >= 0.5) {
            numerator *= -1;
        }
        tmpRatio.setRatio(numerator, denominator);
    } while (tmpRatio.denominator() == 1);

    // store new task
    m_task = task();
    m_task.add_ratio(tmpRatio);

    return;
}

/* show next task to user */
void ExerciseMixedNumbers::nextTask()
{
    // create a new task
    //
    // alternate between converting ratio into mixed number and vice versa
    m_isMixedTask = ! m_isMixedTask;
    QApplication::setOverrideCursor(Qt::WaitCursor);    // show the sand clock
    createTask();
    QApplication::restoreOverrideCursor(); // show the normal cursor

    // update the task widget
    m_taskWidget->setQuestionMixed(m_isMixedTask);
    m_taskWidget->setTask((const task) m_task);

    // hide result widget
    m_resultWidget->setResult(ratio(), -1);

    // change check button
    m_checkButton->setToolTip(i18n("Click this button to check your result. The button will not work if you have not entered a result yet."));
    m_checkButton->setText(i18n("&Check"));

    // clear user input and restore input fields
    m_denoEdit->setText("");
    m_numerEdit->setText("");
    m_integerEdit->setText("");
    m_numerEdit->setEnabled(true);
    m_denoEdit->setEnabled(true);
    m_skipButton->setEnabled(true);
    if (m_isMixedTask) {
        m_integerEdit->hide();
        m_integerEdit->setEnabled(false);
        m_numerEdit->setFocus();
    } else {
        m_integerEdit->setEnabled(true);
        m_integerEdit->show();
        m_integerEdit->setFocus();
    }

    return;
}

/* exercise gets shown */
void ExerciseMixedNumbers::showEvent(QShowEvent *)
{
    // that the user can start typing without moving the focus
    if (m_isMixedTask) {
        m_numerEdit->setFocus();
    } else {
        m_integerEdit->setFocus();
    }
    m_taskWidget->setQuestionMixed(m_isMixedTask);
}

/* check entered result and show solution */
void ExerciseMixedNumbers::showResult()
{
    bool wrong = false;

    // update UI while solution is shown
    m_checkButton->setToolTip(i18n("Click this button to get the next question."));
    m_checkButton->setText(i18n("N&ext"));
    m_integerEdit->setEnabled(false);
    m_numerEdit->setEnabled(false);
    m_denoEdit->setEnabled(false);
    m_skipButton->setEnabled(false);

    // an empty numerator field is interpreted as 0
    if (m_numerEdit->text().isEmpty()) {
        m_numerEdit->setText("0");
    }
    int resultNumerator = m_numerEdit->text().toInt();

    // an empty denominator field is interpreted as 1
    if (m_denoEdit->text().isEmpty()) {
        m_denoEdit->setText("1");
    }
    int resultDenominator = m_denoEdit->text().toInt();
    if (resultDenominator == 0) {
        // don't allow denominator to be 0
        wrong = true;
    }

    // get integer if user had to input it
    int resultInteger = 0;
    if (! m_isMixedTask) {
        resultInteger = m_integerEdit->text().toInt();

        // in mixed notation, numerator must be smaller than denominator
        if (qAbs(resultNumerator) >= qAbs(resultDenominator)) {
            wrong = true;
        }
    }

    // create result ratio, but don't try to reduce it yet
    ratio resultRatio = ratio();
    resultRatio.setRatio(resultInteger, resultNumerator, resultDenominator,
                         false);

    // check for correct solution
    ratio solutionRatio = m_task.get_ratio_n(0);
    if (!(resultRatio == solutionRatio)) {
        wrong = true;
    }

    // wrong solution, try to give some hints what might be wrong
    if (wrong) {
        // emit the signal for wrong
        signalExerciseSolvedWrong();
        m_resultWidget->setAnswerMixed(! m_isMixedTask);
        m_resultWidget->setResult(solutionRatio, 0);

        // check if user entered 0 as denominator
        if (resultDenominator == 0) {
            KMessageBox::information(this, i18n("You entered 0 as the denominator. This means division by zero, which is not allowed. This question will be counted as not correctly solved."));
        } else {
            // first reduce entered result to identify more problems
            resultRatio.reduce();
            if ((! m_isMixedTask) && (resultRatio == solutionRatio) &&
                    (qAbs(resultNumerator) >= qAbs(resultDenominator))) {
                // maybe didn't enter mixed number notation
                KMessageBox::information(this, i18n("You entered the correct result, but not in the mixed number notation. This question will be counted as not correctly solved."));
            } else if (resultRatio == solutionRatio) {
                // maybe the user entered the correct result but not reduced
                KMessageBox::information(this, i18n("You entered the correct result, but not reduced. This question will be counted as not correctly solved."));
            }
        }
    } else {
        // emit the signal for correct
        signalExerciseSolvedCorrect();
        m_resultWidget->setResult(solutionRatio, 1);
    }

    return;
}

/* handle check button */
void ExerciseMixedNumbers::slotCheckButtonClicked()
{
    // button is used to check result and get to next task
    if (m_currentState == _CHECK_TASK) {
        // don't check result if nothing was entered yet
        if (m_numerEdit->text().isEmpty() && m_denoEdit->text().isEmpty()) {
            return;
        }

        m_currentState = _NEXT_TASK;
        (void) showResult();
    } else {
        m_currentState = _CHECK_TASK;
        (void) nextTask();
    }

    return;
}

/* handle skip button */
void ExerciseMixedNumbers::slotSkipButtonClicked()
{
    forceNewTask();
}

/* handle integer edit */
void ExerciseMixedNumbers::integerReturnPressed(const QString &)
{
    m_numerEdit->setFocus();
}

/* handle numerator edit */
void ExerciseMixedNumbers::numerReturnPressed(const QString &)
{
    m_denoEdit->setFocus();
}

/* handle denominator edit */
void ExerciseMixedNumbers::denoReturnPressed(const QString &)
{
    slotCheckButtonClicked();
}
