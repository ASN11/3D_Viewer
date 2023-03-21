#ifndef SCENE_H
#define SCENE_H

#include <QCoreApplication>
#include <QDir>
#include <QFileDialog>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>

#include "parser.h"
#include "qgifimage.h"
#include "simpleobject3d.h"

class SimpleObject3D;

namespace s21 {

class Scene : public QOpenGLWidget {
  Q_OBJECT
 public:
  Scene(QWidget *parent = nullptr);
  ~Scene();

  void setProectionType(int new_proection_type);
  void setPath(const QString new_path);
  void setZ(float new_z);  // перемещаем по осям
  void setY(float new_y);
  void setX(float new_z);
  void rotationX(float x);  // оборот вокруг осей в градусах
  void rotationY(float y);
  void rotationZ(float z);
  void setScale(float new_scale);
  void setLineType(int new_line_type);
  void setColorLine(const QString &new_line_color);
  void setPointColor(const QString &new_point_color);
  void setBackgroundColor(const QString &new_background_color);
  void setThicknessLine(int new_thickness_line);    // толщина линии
  void setThicknessPoint(int new_thickness_point);  // толщина точек
  void setPointFlag(int new_point_flag);  // точки. 0 - отсутствует (default), 1
                                          // - круг, 2 - квадрат
  void setNeedSaveSettings(bool checkeble);
  bool getNeedSaveSettings();
  int getProectionType();
  QString getBackgroundColor();
  SimpleObject3D getObject3D();
  void saveImage(QString path);

  void makeGif();

  double getVCount();  // количество вершин
  double getFCount();  // количество линий

 protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

  void initShaders();
  void initFigure();

 private:
  QMatrix4x4 m_projection_matrix_;
  QOpenGLShaderProgram m_program_;
  QVector2D m_mouse_position_;
  QQuaternion m_rotation_;
  SimpleObject3D m_objects_;
  Parser my_parser_;

  float m_x_, m_y_, m_z_;  // отдаленность объекта от камеры
  float r_x_, r_y_, r_z_;
  float start_x_, start_y_, start_z_;
  int proection_type_;  // тип проекции. 0 - perspective (default), 1 - ortho
  QString path_;  // путь к файлу
  float m_scale_;
  QString background_color_;  // цвет фона

  QSettings *settings;
  bool needSaveSettings;
  void transformDefault();
  void saveSettings();
  void loadSettings();

  QGifImage *gif_;
  QTimer *timer_;
  int shots_;

 private slots:
  void makeShot();
  void saveGif();
};

}  // namespace s21

#endif  // SCENE_H
