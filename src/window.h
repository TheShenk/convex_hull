//
// Created by shenk on 23.12.23.
//

#ifndef CONVEX_HULL_WINDOW_H
#define CONVEX_HULL_WINDOW_H

#include <QPushButton>
#include <QPainter>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <iostream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QOpenGLWidget>
#include <QFileDialog>
#include <fstream>
#include "convex_hull.h"

class Drawer: public QOpenGLWidget
{
    Q_OBJECT
public:

    Drawer() = default;
    Drawer(const std::vector<Point> &points, const std::vector<Point> &ch_points) {
        for (const auto point: points) {
            m_points.push_back(QPointF(point.x, point.y));
        }

        for (const auto point: ch_points) {
            m_ch_points.push_back(QPointF(point.x, point.y));
        }
    }

    void paintGL() override {
        QPainter painter(this);
        painter.fillRect(painter.window(), QColorConstants::White);
        painter.scale(painter.window().width()/100.0, painter.window().height()/100.0);

        painter.setPen(QColorConstants::Black);
        painter.drawPoints(m_points);

        painter.setPen(QColorConstants::Red);
        painter.drawConvexPolygon(m_ch_points);
    }

private:
    QVector<QPointF> m_points;
    QVector<QPointF> m_ch_points;

};

class Window: public QMainWindow
{
    Q_OBJECT
public:
    Window(): QMainWindow() {
        resize(600, 600);

        widget = new Drawer;
        setCentralWidget(widget);

        openAction = new QAction(tr("&Open"), this);
        openAction->setShortcuts(QKeySequence::Open);
        openAction->setStatusTip(tr("Open file"));
        connect(openAction, &QAction::triggered, this, &Window::open);
        menuBar()->addAction(openAction);
    }

private slots:
    void open() {
        auto fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open File"));

        std::vector<Point> points;
        std::ifstream input_file(fileName.toStdString());

        double position_x = 0.0;
        double position_y = 0.0;

        while (!input_file.eof()) {
            input_file >> position_x >> position_y;
            points.emplace_back(Point{position_x, position_y});
        }

        widget = new Drawer(points, convex_hull(points));
        setCentralWidget(widget);

    };

private:

    QOpenGLWidget *widget;
    QAction *openAction;
};

#endif //CONVEX_HULL_WINDOW_H
