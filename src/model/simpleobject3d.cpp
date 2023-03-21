#include "simpleobject3d.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

namespace s21 {

SimpleObject3D::SimpleObject3D() : m_index_buffer_(QOpenGLBuffer::IndexBuffer) {
  line_color_ = "#FFFFFF";
  point_color_ = line_color_;
  thickness_line_ = 2;
  thickness_point_ = 5;
  point_flag_ = 0;
  line_type_ = 0;
}

SimpleObject3D::~SimpleObject3D() {
  if (m_vertex_nuffer_.isCreated()) m_vertex_nuffer_.destroy();
  if (m_index_buffer_.isCreated()) m_index_buffer_.destroy();
}

void SimpleObject3D::init(const QVector<VertexData> &vert_data,
                          const QVector<GLuint> &indexes) {
  if (m_vertex_nuffer_.isCreated()) m_vertex_nuffer_.destroy();
  if (m_index_buffer_.isCreated()) m_index_buffer_.destroy();

  m_vertex_nuffer_.create();
  m_vertex_nuffer_.bind();
  m_vertex_nuffer_.allocate(vert_data.constData(),
                            vert_data.size() * sizeof(VertexData));
  m_vertex_nuffer_.release();

  m_index_buffer_.create();
  m_index_buffer_.bind();
  m_index_buffer_.allocate(indexes.constData(),
                           indexes.size() * sizeof(GLuint));
  m_index_buffer_.release();

  m_model_matrix_.setToIdentity();
}

void SimpleObject3D::draw(QOpenGLShaderProgram *program) {
  if (!m_vertex_nuffer_.isCreated() || !m_index_buffer_.isCreated()) return;

  QColor hColor(line_color_);
  program->setUniformValue("color", hColor.redF(), hColor.greenF(),
                           hColor.blueF(),
                           1.0);  // тут устанавливаем цвет линий RGB

  program->setUniformValue("u_modelMatrix", m_model_matrix_);

  m_vertex_nuffer_.bind();

  int offset = 0;

  int vertloc = program->attributeLocation("a_position");
  program->enableAttributeArray(vertloc);
  program->setAttributeBuffer(vertloc, GL_FLOAT, offset, 3, sizeof(VertexData));

  m_index_buffer_.bind();

  if (line_type_ == 1) {
    glLineStipple(5, 5);
    glEnable(GL_LINE_STIPPLE);
    program->setUniformValue("line_flag", 0);
  } else if (line_type_ == 2) {
    glDisable(GL_LINE_STIPPLE);
    program->setUniformValue(
        "line_flag",
        1);  // тут устанавливаем тип линии (0 - сплошная, 1 - пунктир)
  } else {
    glDisable(GL_LINE_STIPPLE);
    program->setUniformValue("line_flag", 0);
  }

  glLineWidth(thickness_line_);   // толщина линий
  glPointSize(thickness_point_);  // толщина точек

  glDrawElementsInstancedBaseVertex(GL_LINES, m_index_buffer_.size() / 4,
                                    GL_UNSIGNED_INT, 0, 10,
                                    0);  //сама отрисовка линий
  // GL_TRIANGLES / GL_LINES / GL_POINTS - меняем и получаем текстуры или линии
  // или точки

  QColor pColor(point_color_);
  program->setUniformValue("color", pColor.red(), pColor.greenF(),
                           pColor.blueF(),
                           1.0);  // тут устанавливаем цвет точек RGB

  if (point_flag_ == 1) {
    glEnable(GL_POINT_SMOOTH);  // квадрат \ круг
    glDrawElementsInstancedBaseVertex(GL_POINTS, m_index_buffer_.size() / 4,
                                      GL_UNSIGNED_INT, 0, 10,
                                      0);  //сама отрисовка точек
  } else if (point_flag_ == 2) {
    glDisable(GL_POINT_SMOOTH);
    glDrawElementsInstancedBaseVertex(GL_POINTS, m_index_buffer_.size() / 4,
                                      GL_UNSIGNED_INT, 0, 10,
                                      0);  //сама отрисовка точек
  }

  m_vertex_nuffer_.release();
  m_index_buffer_.release();
}

void SimpleObject3D::setLineColor(const QString &new_line_color) {
  line_color_ = new_line_color;
}

void SimpleObject3D::setThicknessLine(int new_thickness_line) {
  thickness_line_ = new_thickness_line;
}

void SimpleObject3D::setThicknessPoint(int new_thickness_point) {
  thickness_point_ = new_thickness_point;
}

void SimpleObject3D::setPointFlag(int new_point_flag) {
  point_flag_ = new_point_flag;
}

void SimpleObject3D::setLineType(int new_line_type) {
  line_type_ = new_line_type;
}

void SimpleObject3D::setPointColor(const QString &new_point_color) {
  point_color_ = new_point_color;
}

QString SimpleObject3D::getLineColor() { return line_color_; }

int SimpleObject3D::getThicknessLine() { return thickness_line_; }

int SimpleObject3D::getThicknessPoint() { return thickness_point_; }

int SimpleObject3D::getPointFlag() { return point_flag_; }

int SimpleObject3D::getLineType() { return line_type_; }

QString SimpleObject3D::getPointColor() { return point_color_; }

}  // namespace s21
