/***************************************************************************
                          Ratio.h  -  class Ratio
                             -------------------
    begin                : Tue Nov 27 16:40:42 CET 2001
    copyright            : (C) 2001-2004 by Sebastian Stein
    email                : seb.kde@hpfsc.de

    copyright            : (C) 2008 by Tadeu Araujo, tadeu.araujo@ltia.fc.unesp.br
    copyright            : (C) 2008 by Danilo Balzaque, danilo.balzaque@ltia.fc.unesp.br
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef RATIO_H
#define RATIO_H

#include <QTextStream>

/** Represents a ratio
 *  This class represents 1 ratio. There are several functions provided to
 *  modify the numerator and denominator. It is also possible to calculate with
 *  objects of the class ratio. Overloaded operation functions are provided for
 *  this task.
 *  \author Sebastian Stein */
class Ratio
{
public:
    /** constructor */
    explicit Ratio(int pnumerator = 0, int pdenominator = 1);

    /** constructor with reduce option */
    Ratio(int pnumerator, int pdenominator, bool reduce_fraction);

    /** copy constructor */
    Ratio(const Ratio & copy_ratio);

    /** destructor */
    ~Ratio();

    /** returns the ratio as QTextStream object */
    QTextStream & display(QTextStream & str) const;

    /** returns the numerator */
    int numerator() const;

    /** returns the denominator */
    int denominator() const;

    /** set numerator and reduce the ratio */
    void setNumerator(int pnumerator = 0, bool reduce = true);

    /** set denominator and reduce the ratio */
    void setDenominator(int pdenominator = 1, bool reduce = true);

    /** set both numerator and denominator;
     *  reducing will be done after numerator and denominator were set!
     */
    void setRatio(int pnumerator, int pdenominator, bool reduce = true);

    /** set new ratio using mixed numbers;
     *  reducing will be done after numerator and denominator were set!
     */
    void setRatio(int pinteger, int pnumerator, int pdenominator, bool reduce = true);

    /** operator overloading for: c = object + summand */
    Ratio operator+ (Ratio addend);

    /** operator overloading for: c = object - subtrahend */
    Ratio operator- (Ratio subtrahend);

    /** operator overloading for: c = object * factor */
    Ratio operator*(Ratio factor);

    /** operator overloading for: c = object / divisor */
    Ratio operator/ (Ratio divisor);

    /** set numerator with dummy and denominator = 1 */
    Ratio operator= (int dummy);

    /** compares the current ratio with a given one */
    bool operator== (Ratio right);

    /** compares the current ratio with a given one */
    bool operator< (Ratio right);

    /** compares the current ratio with a given one */
    bool operator> (Ratio right);

    /** exchange numerator and denominator */
    void reziproc();

    /** reduce the ratio */
    void reduce();

private:
    /** numerator */
    int m_numerator;

    /** denominator */
    int m_denominator;

    /** change sign of the ratio */
    void change_sign();
}
;

/* ------ some prototyps of non class functions ------ */

/** it is possible to code: cout << ratio_object << endl; */
QTextStream & operator<< (QTextStream & str, const Ratio & pratio);

#endif
