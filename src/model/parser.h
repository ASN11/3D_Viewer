#ifndef PARSER_H
#define PARSER_H

#include <QVector3D>
#include <QVector>

#include "OpenGL/gltypes.h"

namespace s21 {

class Parser {
 public:
  Parser() : v_count_(0), f_count_(0){};
  void parseFile(const QString &fileName);

  const QVector<QVector3D> &getCoord() const;
  const QVector<GLuint> &getParsingIndexes() const;

  float diffY();
  float diffX();
  float height();
  float width();

  double getVCount();  // количество вершин
  double getFCount();  // количество линий

  float getDownY() const;
  float getTopY() const;
  float getLeftX() const;
  float getRightX() const;

 private:
  QVector<QVector3D> coord_;
  QVector<GLuint> parsing_indexes_;
  double v_count_;
  double f_count_;
  float down_y_;
  float top_y_;
  float left_x_;
  float right_x_;
};

}  // namespace s21

#endif  // PARSER_H
