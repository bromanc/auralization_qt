#include <glwidget.h>

GlWidget::GlWidget(QWidget *parent) : QOpenGLWidget(parent) {
  m_observerDistance = 30;
  m_gridSpace = 0.2;
  m_focusAngle = 0.5;
  m_gridElements = 40;
  m_horizontalViewerAngle = 19 * M_PI / 60;
  m_verticalViewerAngle = 13 * M_PI / 60;
  viewMode = 1;
}

GlWidget::~GlWidget() {}

int GlWidget::getViewMode(){
    return this->viewMode;
}

void GlWidget::setViewMode(int mode){
    this->viewMode = mode;
}

static void qNormalizeAngle(int &angle) {
  while (angle < 0)
    angle += 360 * 16;
  while (angle > 360 * 16)
    angle -= 360 * 16;
}

void GlWidget::drawGrid() {
  int counter = 0;
  double l;
  glColor3f(0.55, 0.55, 0.55);
  glBegin(GL_LINES);
  for (l = m_gridSpace; l < m_gridElements * m_gridSpace - m_gridSpace / 2;
       l += m_gridSpace) {
    glVertex3f(l, 0, -m_gridElements * m_gridSpace);
    glVertex3f(l, 0, m_gridElements * m_gridSpace);
    glVertex3f(-m_gridElements * m_gridSpace, 0, l);
    glVertex3f(m_gridElements * m_gridSpace, 0, l);
    counter++;
  }
  for (l = -m_gridSpace; l > -m_gridElements * m_gridSpace + m_gridSpace / 2;
       l -= m_gridSpace) {
    glVertex3f(l, 0, -m_gridElements * m_gridSpace);
    glVertex3f(l, 0, m_gridElements * m_gridSpace);
    glVertex3f(-m_gridElements * m_gridSpace, 0, l);
    glVertex3f(m_gridElements * m_gridSpace, 0, l);
    counter++;
  }
  glEnd();
  glColor3f(0.4, 0.4, 0.4);
  glBegin(GL_LINE_LOOP);
  glVertex3f(m_gridElements * m_gridSpace, 0, m_gridElements * m_gridSpace);
  glVertex3f(m_gridElements * m_gridSpace, 0, -m_gridElements * m_gridSpace);
  glVertex3f(-m_gridElements * m_gridSpace, 0, -m_gridElements * m_gridSpace);
  glVertex3f(-m_gridElements * m_gridSpace, 0, m_gridElements * m_gridSpace);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(-m_gridElements * m_gridSpace, 0, 0);
  glVertex3f(m_gridElements * m_gridSpace, 0, 0);
  glVertex3f(0, 0, -m_gridElements * m_gridSpace);
  glVertex3f(0, 0, m_gridElements * m_gridSpace);
  glVertex3f(0, -m_gridElements * m_gridSpace, 0);
  glVertex3f(0, m_gridElements * m_gridSpace, 0);
  glEnd();
}

void GlWidget::drawAxis() {
  glLineWidth(2);
  glColor3f(1, 0.65, 0.65);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0.1 * m_gridElements * m_gridSpace, 0, 0);
  glEnd();
  glColor3f(0.65, 1, 0.65);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0.1 * m_gridElements * m_gridSpace, 0);
  glEnd();
  glColor3f(0.65, 0.65, 1);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 0.1 * m_gridElements * m_gridSpace);
  glEnd();
  glLineWidth(1);
}

void GlWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.6, 0.6, 0.6, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1.0);
  glLineWidth(1);
  glPointSize(4);
}

void GlWidget::paintGL() {
  double frontPlaneDistance, backPlaneDistance;

  backPlaneDistance =
      qSqrt(3 * m_gridElements * m_gridSpace * m_gridElements * m_gridSpace +
            2 * m_gridElements * m_gridSpace *
                (qAbs(m_centerPoint.x()) + qAbs(m_centerPoint.y()) +
                 qAbs(m_centerPoint.z())) +
            m_centerPoint.x() * m_centerPoint.x() +
            m_centerPoint.y() * m_centerPoint.y() +
            m_centerPoint.z() * m_centerPoint.z());
  if (m_observerDistance > backPlaneDistance)
    frontPlaneDistance = backPlaneDistance;
  else
    frontPlaneDistance = 0.99 * m_observerDistance;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  QMatrix4x4 perspective;
  perspective.setToIdentity();
  perspective.perspective(180 * m_focusAngle / M_PI,
                          this->width() / this->height(),
                          m_observerDistance - frontPlaneDistance,
                          m_observerDistance + backPlaneDistance);
  glMultMatrixf(perspective.data());

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  m_observerPoint.setX(m_observerDistance * qCos(m_verticalViewerAngle) *
                           qCos(m_horizontalViewerAngle) +
                       m_centerPoint.x());
  m_observerPoint.setY(m_observerDistance * qSin(m_verticalViewerAngle) +
                       m_centerPoint.y());
  m_observerPoint.setZ(m_observerDistance * qCos(m_verticalViewerAngle) *
                           qSin(m_horizontalViewerAngle) +
                       m_centerPoint.z());
  m_up.setX(0);
  m_up.setY(1);
  m_up.setZ(0);

  QMatrix4x4 look;
  look.setToIdentity();
  look.lookAt(m_observerPoint, m_centerPoint, m_up);
  glMultMatrixf(look.data());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  drawGrid();
  glDisable(GL_DEPTH_TEST);
  drawAxis();
  glEnable(GL_DEPTH_TEST);
}

void GlWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void GlWidget::mousePressEvent(QMouseEvent *event) { m_lastPos = event->pos(); }

void GlWidget::mouseMoveEvent(QMouseEvent *event) {
  double v = 1;
  int dx = event->x() - m_lastPos.x();
  int dy = event->y() - m_lastPos.y();

  switch (this->getViewMode()) {
  case 1:
      this->orbitMode(dx, dy, v);
      break;
  case 2:
      this->translateMode(dx, dy, v);
      break;
  case 3:
      this->zoomMode(dy, v);
      break;
  case 4:
      this->perspectiveMode(dy, v);
      break;
  default:
      break;
  }

  update();

  m_lastPos = event->pos();
}

void GlWidget::wheelEvent(QWheelEvent *event) {
  double v = 1;
  int numDegrees = event->delta() / 8;
  if (numDegrees < 0) {
    if (m_observerDistance < 100 * v * 2 * m_gridSpace)
      m_observerDistance += v * 2 * m_gridSpace * qTan(0.5 / (v * 2)) /
                            qTan(m_focusAngle / (v * 2));
  } else {
    if (m_observerDistance > v * 2 * m_gridSpace)
      m_observerDistance -= v * 2 * m_gridSpace * qTan(0.5 / (v * 2)) /
                            qTan(m_focusAngle / (v * 2));
  }
  update();
}

void GlWidget::orbitMode(int dx, int dy, double v){

    if (dx < 0)
      m_horizontalViewerAngle += v * M_PI / 60;
    if (dx > 0)
      m_horizontalViewerAngle -= v * M_PI / 60;
    if (dy > 0) {
      m_verticalViewerAngle += v * M_PI / 60;
      if (m_verticalViewerAngle < -M_PI / 2)
        m_verticalViewerAngle = -M_PI / 2;
    }
    if (dy < 0) {
      m_verticalViewerAngle -= v * M_PI / 60;
      if (m_verticalViewerAngle > M_PI / 2)
        m_verticalViewerAngle = M_PI / 2;
    }

}

void GlWidget::translateMode(int dx, int dy, double v){

    QVector3D *up = new QVector3D (0.0f, 0.0f, 1.0f);
    QVector3D base0 = QVector3D::normal(*up, this->m_observerPoint.operator-=(this->m_centerPoint));
    QVector3D base1 = QVector3D::normal(this->m_observerPoint.operator-=(this->m_centerPoint), base0);

    if(dx < 0){
        this->m_centerPoint.operator+=(base0.operator*=((v * m_gridSpace)));
        this->m_observerPoint.operator+=(base0.operator*=((v * m_gridSpace)));
    }

    if(dx > 0){
        this->m_centerPoint.operator+=(base0.operator*=((v * -m_gridSpace)));
        this->m_observerPoint.operator+=(base0.operator*=((v * -m_gridSpace)));
    }

    if(dy > 0){
        this->m_centerPoint.operator+=(base1.operator*=((v * m_gridSpace)));
        this->m_observerPoint.operator+=(base1.operator*=((v * m_gridSpace)));
    }

    if(dy < 0){
        this->m_centerPoint.operator+=(base1.operator*=((v * -m_gridSpace)));
        this->m_observerPoint.operator+=(base1.operator*=((v * -m_gridSpace)));
    }

}

void GlWidget::zoomMode(int dy, double v){

    if(dy < 0){
        if(m_observerDistance > (m_gridSpace * 2 * v)){
            m_observerDistance -= v * 2 * m_gridSpace * (qTan(0.5/(v * 2))/qTan(m_focusAngle/(v * 2)));
        }
    }

    if(dy > 0){
        if(m_observerDistance < (m_gridSpace * 2 * v * 100)){
            m_observerDistance += v * 2 * m_gridSpace * (qTan(0.5/(v * 2))/qTan(m_focusAngle/(v * 2)));
        }
    }

}

void GlWidget::perspectiveMode(int dy, double v){

    if(dy < 0){
        if(m_focusAngle < (M_PI - (v * 0.06))){
            m_focusAngle += v * 0.05;
            m_observerDistance = m_observerDistance * (qTan((m_focusAngle - (v * 0.05))/ 2)/qTan(m_focusAngle / 2));
        }
    }
    if(dy > 0){
        if(m_focusAngle > v * 0.06){
            m_focusAngle -= v * 0.05;
            m_observerDistance = m_observerDistance * (qTan((m_focusAngle + (v * 0.05))/ 2)/qTan(m_focusAngle / 2));
        }
    }
}
