/***************************************************************************
                          mainqtwidget.h  -  The main Qt/KDE window
                             -------------------
    begin                : Tue Mar 16 00:00:00 CET 2003
    copyright            : (C) 2003 by Sebastian Stein
    email                : kbruch@hpfsc.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef MAINQTWIDGET_H
#define MAINQTWIDGET_H

#include <kmainwindow.h>


class KConfig;
class KWidgetAction;

class QLabel;

class StatisticsView;
class TaskView;

/*! Constructs the main window and presents the user interface.
 *  The window is seperated into 2 sections. In the left section is the
 *  statistic view and in the right section the task view.
 *  \author Sebastian Stein
 *  \author Eva Brucherseifer
 * */
class MainQtWidget : public KMainWindow
{
	Q_OBJECT
			  
	public:
		/** constructor */
		MainQtWidget();

		/** destructor */
		~MainQtWidget();

	private:
		/** read the config file */
		void readOptions();

		/** read the config file */
		void writeOptions();
		
		/** pointing to the statistics view */
		StatisticsView * m_statview;

		/** pointing to the task view */
		TaskView * m_taskview;
		
		bool m_addSub;
		bool m_mulDiv;
		unsigned int m_nrRatios;
		unsigned int m_maxMainDenominator;

		void setupActions();

		QComboBox * m_NrOfTermsBox;
		QLabel * m_NrOfTermsLabel;
		KWidgetAction * m_NrOfTermsBoxAction;
		KWidgetAction * m_NrOfTermsLabelAction;

		QComboBox * m_MaxMainDenominatorBox;
		QLabel * m_MaxMainDenominatorLabel;
		KWidgetAction * m_MaxMainDenominatorBoxAction;
		KWidgetAction * m_MaxMainDenominatorLabelAction;

		QComboBox * m_OperationBox;
		QLabel * m_OperationLabel;
		KWidgetAction * m_OperationBoxAction;
		KWidgetAction * m_OperationLabelAction;

		KAction * m_NewTaskAction;

		KConfig * m_config;

	private slots:
		void NewTask();
		void NrOfTermsBoxSlot();
		void MaxMainDenominatorBoxSlot();
		void OperationBoxSlot();
};

#endif // MainQtWidget
