/***************************************************************************
                          ratiowidget.h  -  paint a ratio
                             -------------------
    begin                : 2004/06/03
    copyright            : (C) 2004 by Sebastian Stein
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

#include "ratiowidget.h"
#include "ratiowidget.moc"

/* these includes are needed for Qt support */
#include <qpainter.h>
//Added by qt3to4:
#include <QPaintEvent>

RatioWidget::RatioWidget(QWidget * parent = 0,
													const ratio para_ratio = ratio()) :
			FractionBaseWidget(parent), m_ratio(para_ratio)
{
#ifdef DEBUG
	kDebug() << "constructor RatioWidget";
#endif
}

RatioWidget::~RatioWidget()
{
#ifdef DEBUG
	kDebug() << "destructor RatioWidget";
#endif
}

void RatioWidget::setRatio(const ratio para_ratio)
{
	m_ratio = para_ratio;
	update();
}

void RatioWidget::setQuestionMixed(bool value)
{
	m_questionMixed = value;
}

void RatioWidget::paintEvent(QPaintEvent* /* p_paintEvent */)
{
	// our x position, we paint from left to right;
	// we don't want to start directly on the border, so add the margin
	int x_pos = _MARGIN_X;
	int y_pos = 0;

	// start the painter
	QPainter paint(this);

	// ratios and operation signs are painted with the same font
	paint.setFont(m_font);

	// set the pen for painting
	QPen pen(Qt::SolidLine);
	pen.setWidth(0);
	paint.setPen(pen);

	// get the font height; the font height doesn't change while painting
	QFontMetrics fm (paint.fontMetrics());

	// now we can correctly set the height of the widget
	setMinimumHeight(2 * fm.lineSpacing() + 10);
	setMaximumHeight(2 * fm.lineSpacing() + 10);

	// result as normal ratio
	paintRatio(paint, m_ratio, x_pos, y_pos, fm, m_questionMixed);

	// stop the painter
	paint.end();

	// the space we needed for painting is the minimum width of the widget
	setMinimumWidth(x_pos);

	return;
}
