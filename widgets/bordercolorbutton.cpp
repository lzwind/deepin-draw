/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     RenRan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "bordercolorbutton.h"

#include <QPainter>
#include <QDebug>

#include "utils/baseutils.h"
#include "drawshape/cdrawparamsigleton.h"
#include "frame/cviewmanagement.h"
#include "frame/cgraphicsview.h"

const qreal COLOR_RADIUS = 4;
const int BTN_RADIUS = 8;
const QPoint CENTER_POINT = QPoint(12, 12);

BorderColorButton::BorderColorButton(DWidget *parent)
    : DPushButton(parent)
    , m_isHover(false)
    , m_isChecked(false)
    , m_isMultColorSame(false)
{
    setFixedSize(55, 32);
    setCheckable(false);
    m_color = CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getLineColor();
}

void BorderColorButton::updateConfigColor()
{
    m_isMultColorSame = true;
    QColor configColor = CManageViewSigleton::GetInstance()->getCurView()->getDrawParam()->getLineColor();

    if (m_color == configColor) {
        return;
    }

    m_color = configColor;

    update();
}

BorderColorButton::~BorderColorButton()
{
}

void BorderColorButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (m_isMultColorSame) {
        painter.setRenderHints(QPainter::Antialiasing
                               | QPainter::SmoothPixmapTransform);
        painter.setPen(Qt::transparent);

        QPen colorPen;
        colorPen.setWidth(3);
        colorPen.setColor(m_color);
        painter.setPen(colorPen);
        painter.drawRoundedRect(QRect(5, 9, 17, 17), 7, 7);


        QPen borderPen;
        borderPen.setWidth(1);
        borderPen.setColor(QColor(0, 0, 0, 25));
        painter.setPen(borderPen);
        painter.drawRoundedRect(QRect(6, 10, 16, 16), 6, 6);
        painter.drawRoundedRect(QRect(4, 8, 20, 20), 8, 8);

        if (m_color == QColor(Qt::transparent) || m_color.alpha() == 0) {
            QPen linePen;
            linePen.setWidth(2);
            linePen.setColor(QColor("#ff804d"));
            painter.setPen(linePen);
            painter.drawLine(8, 21, 19, 13);
        }

        QPen textPen;
        if (CManageViewSigleton::GetInstance()->getThemeType() == 1) {
            textPen.setColor(QColor("#414D68"));
        } else {
            textPen.setColor(QColor("#C0C6D4"));
        }

        painter.setPen(textPen);
        QFont ft;
        ft.setPixelSize(14);
        painter.setFont(ft);

        painter.drawText(26, 6, 38, 22, 1, tr("Stroke"));
    } else {
        painter.setRenderHints(QPainter::Antialiasing
                               | QPainter::SmoothPixmapTransform);

        QPen pen;
        pen.setWidth(1);
        pen.setColor(QColor(0, 0, 0, 12));
        painter.setPen(pen);
        painter.drawRoundedRect(QRect(4, 8, 19, 19), 8, 8);

        QPen borderPen;
        borderPen.setWidth(1);
        borderPen.setColor(QColor(0, 0, 0, 12));
        painter.setPen(borderPen);
        painter.drawRoundedRect(QRect(6, 10, 15, 15), 6, 6);

        QPen textPen;
        if (CManageViewSigleton::GetInstance()->getThemeType() == 1) {
            textPen.setColor(QColor("#414D68"));
        } else {
            textPen.setColor(QColor("#C0C6D4"));
        }

        painter.setPen(textPen);
        QFont ft;
        ft.setPixelSize(14);
        painter.setFont(ft);
        painter.drawText(26, 6, 38, 22, 1, tr("Stroke"));
    }
}

void BorderColorButton::setColor(QColor color)
{
    m_isMultColorSame = true;
    m_color = color;
    update();
}

void BorderColorButton::setColorIndex(int index)
{
    m_isMultColorSame = true;
    m_color = colorIndexOf(index);
    update();
}

void BorderColorButton::resetChecked()
{
    m_isChecked = false;
    update();
}

void BorderColorButton::setIsMultColorSame(bool isMultColorSame)
{
    m_isMultColorSame = isMultColorSame;
}

void BorderColorButton::enterEvent(QEvent *)
{
    if (!m_isHover) {
        m_isHover = true;
        update();
    }
}

void BorderColorButton::leaveEvent(QEvent *)
{
    if (m_isHover) {
        m_isHover = false;
        update();
    }
}

void BorderColorButton::mousePressEvent(QMouseEvent * )
{
    m_isChecked = !m_isChecked;
    btnCheckStateChanged(m_isChecked);

    update();
}
