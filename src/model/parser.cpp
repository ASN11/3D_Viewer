#include "parser.h"

#include <QFile>
#include <QTextStream>

namespace s21 {

void Parser::parseFile(const QString &fileName) {
  coord_.clear();
  parsing_indexes_.clear();
  v_count_ = 0;

  QFile file(fileName);
  if (!file.exists()) return;

  file.open(QIODevice::ReadOnly);
  QTextStream input(&file);

  while (!input.atEnd()) {
    QString str = input.readLine();
    str = str.simplified();
    QStringList list = str.split(" ");

    if (list[0] == "v") {
      coord_.append(
          QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
      v_count_++;
      continue;
    } else if (list[0] == "f") {
      parsing_indexes_.append(list[1].section('/', 0, 0).toUInt() - 1);

      for (int i = 2; i < list.size(); i++) {
        parsing_indexes_.append(list[i].section('/', 0, 0).toUInt() - 1);
        parsing_indexes_.append(list[i].section('/', 0, 0).toUInt() - 1);
      }
      parsing_indexes_.append(list[1].section('/', 0, 0).toUInt() - 1);
    }
  }
  auto min_y = std::min_element(
      coord_.begin(), coord_.end(),
      [](const QVector3D &a, const QVector3D &b) { return a.y() < b.y(); });
  down_y_ = min_y->y();

  auto max_y = std::max_element(
      coord_.begin(), coord_.end(),
      [](const QVector3D &a, const QVector3D &b) { return a.y() < b.y(); });
  top_y_ = max_y->y();

  auto min_x = std::min_element(
      coord_.begin(), coord_.end(),
      [](const QVector3D &a, const QVector3D &b) { return a.x() < b.x(); });
  left_x_ = min_x->x();

  auto max_x = std::max_element(
      coord_.begin(), coord_.end(),
      [](const QVector3D &a, const QVector3D &b) { return a.x() < b.x(); });
  right_x_ = max_x->x();
}

const QVector<QVector3D> &Parser::getCoord() const { return coord_; }

const QVector<GLuint> &Parser::getParsingIndexes() const {
  return parsing_indexes_;
}

float Parser::diffY() {
  float diff_y = (top_y_ + down_y_) / -2;
  return diff_y;
}

float Parser::diffX() {
  float diff_x = (right_x_ + left_x_) / -2;
  return diff_x;
}

float Parser::height() {
  float height = abs(left_x_) + abs(right_x_);
  return height;
}

float Parser::width() {
  float width = abs(down_y_) + abs(top_y_);
  return width;
}

double Parser::getVCount() { return v_count_; }

double Parser::getFCount() {
  f_count_ = parsing_indexes_.size() / 4;
  return f_count_;
}

float Parser::getDownY() const { return down_y_; }

float Parser::getTopY() const { return top_y_; }

float Parser::getLeftX() const { return left_x_; }

float Parser::getRightX() const { return right_x_; }

}  // namespace s21
