/***************************************************************************
                          mainqtwidget.h  -  The main Qt/KDE window
                             -------------------
    begin                : Tue Mar 16 00:00:00 CET 2003
    copyright            : (C) 2003-2004 by Sebastian Stein
    email                : seb.kde@hpfsc.de
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

#include <kxmlguiwindow.h>
class KAction;
class KComboBox;
class KPageDialog;
class KPageWidgetItem;

class QLabel;

class ExerciseCompare;
class ExerciseConvert;
class ExerciseFactorize;
class StatisticsView;
class TaskView;

/** Constructs the main window and presents the user interface.
 *  The window is separated into 2 sections. In the left section is the
 *  statistic view and in the right section the task view.
 *  \author Sebastian Stein
 *  \author Eva Brucherseifer
 **/
class MainQtWidget : public KXmlGuiWindow
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

		/** the iconlist for the different exercises */
		KPageDialog * m_exercises;

		/** pointing to the exercise solving a task with fractions; added as page
		 * to the iconlist */
		TaskView * m_taskview;

		/** pointing to the exercise comparing ratios; added as page to the
		 * iconlist */ 
		ExerciseCompare * m_exerciseCompare;

		/** pointing to the exercise convert rational number; added as page to the
		 * iconlist */ 
		ExerciseConvert * m_exerciseConvert;

		/** pointing to the exercise factorize a given number; added as page to
		 * the iconlist */ 
		ExerciseFactorize * m_exerciseFactorize;
		
		bool m_addSub;
		bool m_mulDiv;
		unsigned int m_nrRatios;
		unsigned int m_maxMainDenominator;

		void setupActions();

		KComboBox * m_NrOfTermsBox;
		QLabel * m_NrOfTermsLabel;
		KAction * m_NrOfTermsBoxAction;
		KAction * m_NrOfTermsLabelAction;

		KComboBox * m_MaxMainDenominatorBox;
		QLabel * m_MaxMainDenominatorLabel;
		KAction * m_MaxMainDenominatorBoxAction;
		KAction * m_MaxMainDenominatorLabelAction;

		KComboBox * m_OperationBox;
		QLabel * m_OperationLabel;
		KAction * m_OperationBoxAction;
		KAction * m_OperationLabelAction;

		KAction * m_NewTaskAction;
		KPageWidgetItem *pageItemFraction, *pageItemComparison, *pageItemConversion, *pageItemFactorization;
		KPageWidgetItem *pageItems[4]; // same as above, just for mapping from pointer to index

	private slots:
		/** 
		 * called to force generation of a new task 
		 */
		void NewTask();
		/** 
		 * called when the user changes the number of terms in the ComboBox 
		 */
		void NrOfTermsBoxSlot();
		/** 
		 *called, when the user changes the max. size of the main denominator in
 		 * the ComboBox 
		 */
		void MaxMainDenominatorBoxSlot();
		/** 
		 * called, when the user changes the wished task's operations 
		 */
		void OperationBoxSlot();

		/**
		 * calls the settings dialog
		 */
		void slotPrefs();

		/**
		 * makes sure, all parts of the UI update to new settings
		 */
		void slotApplySettings();

		/**
		 * called just before another page is shown
		 */
		void slotAboutToShowPage(KPageWidgetItem *);

	protected:
		/** Function is called when user calls termination.
		 *  Used to save the current statistics and settings before exiting.
		 **/
		bool queryExit();
};

#endif // MainQtWidget
