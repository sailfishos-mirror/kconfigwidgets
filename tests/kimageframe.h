/*
 * Copyright 2009 Matthew Woehlke <mw_triad@users.sourceforge.net>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KIMAGEFRAME_H
#define KIMAGEFRAME_H

#include <QFrame>

class KImageFrame : public QFrame
{
    Q_OBJECT
public:
    KImageFrame(QWidget *parent = nullptr);
    virtual ~KImageFrame() {}

public Q_SLOTS:
    void setImage(const QImage &);

protected Q_SLOTS:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

protected:
    QImage _img;
    int _w, _h;
};

#endif
