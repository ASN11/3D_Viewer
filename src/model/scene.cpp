#include "scene.h"

namespace s21 {

Scene::Scene(QWidget *parent) : QOpenGLWidget(parent) {
  m_z_ = 0.0f;  // отдаление объекта от камеры
  m_y_ = 0.0f;
  r_x_ = 0.0f;
  r_y_ = 0.0f;
  r_z_ = 0.0f;
  m_scale_ = 1.0f;
  proection_type_ = 0;
  background_color_ = "#000000";
  settings = new QSettings(QDir::homePath() + "/.viewer_settings.conf",
                           QSettings::IniFormat);
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, &Scene::makeShot);
  loadSettings();
}

Scene::~Scene() {
  delete timer_;
  delete settings;
}

void Scene::initializeGL() {
  glEnable(GL_DEPTH_TEST);  // включение буффера глубины
  glEnable(GL_CULL_FACE);  // устанавливаем режим, когда строятся только внешние
                           // поверхности

  initShaders();
}

void Scene::resizeGL(int width, int height) {
  float aspect = width / (float)height;
  float my_aspect = my_parser_.height() / my_parser_.width();
  m_projection_matrix_.setToIdentity();
  if (proection_type_ == 0)
    m_projection_matrix_.perspective(
        45, aspect, 0.01f,
        1000000.0f);  // формируем необходимую матрицу для отображения
  else if (proection_type_ == 1)
    m_projection_matrix_.ortho(
        (my_parser_.getLeftX() + my_parser_.diffX()) * 1.2 * aspect,
        (my_parser_.getRightX() + my_parser_.diffX()) * 1.2 * aspect,
        (my_parser_.getDownY() + my_parser_.diffY()) * 1.2 * my_aspect,
        (my_parser_.getTopY() + my_parser_.diffY()) * 1.2 * my_aspect, 0.1f,
        1000.0f);
}

void Scene::paintGL() {
  QColor hColor(background_color_);  // устанавливает цвет окна
  glClearColor(hColor.redF(), hColor.greenF(), hColor.blueF(), 1.0f);

  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);  // очистка буфера изображения и глубины

  QMatrix4x4 viewMatrix;
  viewMatrix.setToIdentity();
  viewMatrix.translate(m_x_, m_y_,
                       m_z_);  // Умножает эту матрицу на другую, которая
                               // переводит координаты на компоненты x, y и z .
  viewMatrix.rotate(m_rotation_);  // поворот матрицы
  viewMatrix.scale(m_scale_);

  m_program_.bind();
  m_program_.setUniformValue("u_projectionMatrix", m_projection_matrix_);
  m_program_.setUniformValue("u_viewMatrix", viewMatrix);

  m_objects_.draw(&m_program_);
  saveSettings();
}

void Scene::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton)
    m_mouse_position_ = QVector2D(event->position());
  event->accept();
}

void Scene::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() != Qt::LeftButton) return;

  QVector2D diff = QVector2D(event->position()) - m_mouse_position_;
  m_mouse_position_ = QVector2D(event->position());

  float angle = diff.length() / 2.0;

  QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

  m_rotation_ = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation_;

  update();
}

void Scene::wheelEvent(QWheelEvent *event) {
  if (event->pixelDelta().y() > 0)
    m_scale_ *= 1.1f;
  else if (event->pixelDelta().y() < 0)
    m_scale_ *= 0.909f;

  update();
}

void Scene::initShaders() {
  if (!m_program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          ":/vshader.vsh"))
    close();

  if (!m_program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          ":/fshader.fsh"))
    close();

  if (!m_program_.link()) close();
}

void Scene::initFigure() {
  my_parser_.parseFile(path_);
  QVector<QVector3D> vert = my_parser_.getCoord();
  QVector<VertexData> vertexes;
  for (int i = 0; i < vert.size(); i++) {
    vertexes.append(VertexData(vert[i]));
  }

  QVector<GLuint> indexes = my_parser_.getParsingIndexes();

  //    выставляем положение камеры
  m_z_ = start_z_ = (sqrt(my_parser_.height() * my_parser_.height() +
                          my_parser_.width() * my_parser_.width())) *
                    -2;
  m_y_ = start_y_ = my_parser_.diffY();
  m_x_ = start_x_ = my_parser_.diffX();
  m_rotation_ = QQuaternion();
  m_scale_ = 1.0f;

  m_objects_.init(vertexes, indexes);
}

void Scene::setBackgroundColor(const QString &new_background_color) {
  background_color_ = new_background_color;
  update();
}

void Scene::setThicknessLine(int new_thickness_line) {
  m_objects_.setThicknessLine(new_thickness_line);
  update();
}

void Scene::setThicknessPoint(int new_thickness_point) {
  m_objects_.setThicknessPoint(new_thickness_point);
  update();
}

void Scene::setPointFlag(int new_point_flag) {
  m_objects_.setPointFlag(new_point_flag);
  update();
}

double Scene::getVCount() { return my_parser_.getVCount(); }

double Scene::getFCount() { return my_parser_.getFCount(); }

void Scene::setLineType(int new_line_type) {
  m_objects_.setLineType(new_line_type);
  update();
}

void Scene::setColorLine(const QString &new_line_color) {
  m_objects_.setLineColor(new_line_color);
  update();
}

void Scene::setPointColor(const QString &new_point_color) {
  m_objects_.setPointColor(new_point_color);
  update();
}

void Scene::setScale(float new_scale) {
  m_scale_ = new_scale;
  update();
}

void Scene::setX(float new_x) {
  m_x_ = start_x_ + new_x;
  update();
}

void Scene::setY(float new_y) {
  m_y_ = start_y_ + new_y;
  update();
}

void Scene::setZ(float new_z) {
  m_z_ = start_z_ + new_z;
  update();
}

void Scene::setPath(const QString new_path) {
  path_ = new_path;
  initFigure();
  resizeGL(width(), height());
  update();
}

void Scene::setProectionType(int new_proection_type) {
  proection_type_ = new_proection_type;
  resizeGL(width(), height());
  update();
}

void Scene::rotationX(float x) {
  float diff_x = x - r_x_;
  r_x_ = x;

  double angle = QVector3D(diff_x, 0, 0).length();
  QVector3D axis = QVector3D(diff_x, 0, 0);
  m_rotation_ = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation_;
  update();
}

void Scene::rotationY(float y) {
  float diff_y = y - r_y_;
  r_y_ = y;

  double angle = QVector3D(0, diff_y, 0).length();
  QVector3D axis = QVector3D(0, diff_y, 0);
  m_rotation_ = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation_;
  update();
}

void Scene::rotationZ(float z) {
  float diff_z = z - r_z_;
  r_z_ = z;

  double angle = QVector3D(0, 0, diff_z).length();
  QVector3D axis = QVector3D(0, 0, diff_z);
  m_rotation_ = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation_;
  update();
}

void Scene::setNeedSaveSettings(bool checkeble) {
  needSaveSettings = checkeble;
}

bool Scene::getNeedSaveSettings() { return needSaveSettings; }

int Scene::getProectionType() { return proection_type_; }

QString Scene::getBackgroundColor() { return background_color_; }

SimpleObject3D Scene::getObject3D() { return m_objects_; }

void Scene::saveSettings() {
  settings->beginGroup("settings");
  settings->setValue("needSave", needSaveSettings);

  settings->setValue("BackgroundColor", background_color_);
  settings->setValue("LineColor", m_objects_.getLineColor());
  settings->setValue("PointColor", m_objects_.getPointColor());

  settings->setValue("proectionType", proection_type_);

  settings->setValue("LineType", m_objects_.getLineType());
  settings->setValue("PointFlag", m_objects_.getPointFlag());
  settings->setValue("ThicknessLine", m_objects_.getThicknessLine());
  settings->setValue("ThicknessPoint", m_objects_.getThicknessPoint());

  settings->endGroup();
}

void Scene::loadSettings() {
  settings->beginGroup("settings");
  needSaveSettings = settings->value("needSave").toBool();
  if (needSaveSettings) {
    background_color_ = settings->value("BackgroundColor").toString();
    m_objects_.setLineColor(settings->value("LineColor").toString());
    m_objects_.setPointColor(settings->value("PointColor").toString());

    proection_type_ = settings->value("proectionType").toInt();

    m_objects_.setLineType(settings->value("LineType").toDouble());
    m_objects_.setPointFlag(settings->value("PointFlag").toDouble());
    m_objects_.setThicknessLine(settings->value("ThicknessLine").toInt());
    m_objects_.setThicknessPoint(settings->value("ThicknessPoint").toInt());
  }
  settings->endGroup();
}

void Scene::saveImage(QString path) { grab().save(path); }

void Scene::saveGif() {
  QString path = QFileDialog::getSaveFileName(
      this, tr("Choose dir..."), "untitled.gif", tr("Images (*.gif)"));
  if (path.isEmpty() || path.isNull()) return;
  gif_->save(path);
  delete gif_;
}

void Scene::makeGif() {
  gif_ = new QGifImage();
  gif_->setDefaultDelay(100);
  timer_->start(100);
}

void Scene::makeShot() {
  if (shots_ < 50) {
    gif_->addFrame(grab().toImage());
    shots_ += 1;
  } else if (shots_ == 50) {
    timer_->stop();
    saveGif();
    shots_ = 0;
  }
}

}  // namespace s21
