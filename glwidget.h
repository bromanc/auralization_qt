#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glu.h>
#include <QColor>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QWheelEvent>
#include <QtDebug>
#include <QtMath>
#include <iostream>

class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions_2_0 {
  Q_OBJECT

public:
  GlWidget(QWidget *parent = 0);
  ~GlWidget();

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

private:
  int m_xRot;
  int m_yRot;

  QPoint m_lastPos;
  QVector3D m_centerPoint;
  QVector3D m_observerPoint;
  QVector3D m_up;
  double m_observerDistance;
  double m_gridSpace;
  double m_focusAngle;
  double m_gridElements;
  double m_verticalViewerAngle;
  double m_horizontalViewerAngle;

  void drawGrid();
  void drawAxis();
};

#endif // GLWIDGET_H
