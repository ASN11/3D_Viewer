#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#define GL_SILENCE_DEPRECATION
#include <QMatrix4x4>
#include <QOpenGLBuffer>

class QOpenGLShaderProgram;

namespace s21 {

struct VertexData {
  VertexData() {}

  VertexData(QVector3D p) : position(p) {}

  QVector3D position;
};

class SimpleObject3D {
 public:
  SimpleObject3D();
  ~SimpleObject3D();
  void init(const QVector<VertexData> &vert_data,
            const QVector<GLuint> &indexes);
  void draw(QOpenGLShaderProgram *program);
  void setLineColor(const QString &new_line_color);
  void setThicknessLine(int new_thickness_line);
  void setThicknessPoint(int new_thickness_point);
  void setPointFlag(int new_point_flag);
  void setLineType(int new_line_type);
  void setPointColor(const QString &new_point_color);
  QString getLineColor();
  int getThicknessLine();
  int getThicknessPoint();
  int getPointFlag();
  int getLineType();
  QString getPointColor();

 private:
  QOpenGLBuffer m_vertex_nuffer_;
  QOpenGLBuffer m_index_buffer_;
  QMatrix4x4 m_model_matrix_;
  QString line_color_;
  QString point_color_;
  int thickness_line_;   // толщина линий
  int thickness_point_;  // толщина точек
  int point_flag_;  // точки. 0 - отсутствует (default), 1 - круг, 2 - квадрат
  int line_type_;  // тип линии. 0 - сплошная (default), 1 - пунктирная, 2 -
                   // пунктир на шейдере (тест)
};

}  // namespace s21

#endif  // SIMPLEOBJECT3D_H
