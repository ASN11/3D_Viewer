#include <QApplication>
#include <QtTest>

#include "../model/parser.h"

class parserTest : public QObject {
  Q_OBJECT

 public:
  parserTest() {}
  ~parserTest() {}

 private slots:
  void test_case1_F_and_V();
  void test_case2_diff_height_width();
  void test_case3_Down_Top_Left_Right();
  void test_case4_getCoord();
  void test_case5_getParsingIndexes();
  void initTestCase();

 private:
  s21::Parser parser;
};

void parserTest::test_case1_F_and_V() {
  QVERIFY(parser.getFCount() == 12);
  QVERIFY(parser.getVCount() == 8);
}

void parserTest::test_case2_diff_height_width() {
  QVERIFY(parser.diffX() == 0);
  QVERIFY(parser.diffY() == 0);
  QVERIFY(parser.height() == 2);
  QVERIFY(parser.width() == 2);
}

void parserTest::test_case3_Down_Top_Left_Right() {
  QVERIFY(parser.getDownY() == -1);
  QVERIFY(parser.getTopY() == 1);
  QVERIFY(parser.getLeftX() == -1);
  QVERIFY(parser.getRightX() == 1);
}

void parserTest::test_case4_getCoord() {
  QVector<QVector3D> coord = parser.getCoord();
  QVector<QVector3D> test = {{1, 1, -1}, {1, -1, -1}, {1, 1, 1},
                             {1, -1, 1}, {-1, 1, -1}, {-1, -1, -1},
                             {-1, 1, 1}, {-1, -1, 1}};
  QVERIFY(coord.size() == test.size());

  for (int i = 0; i < coord.size(); i++) {
    QVERIFY(coord[i].x() == test[i].x());
    QVERIFY(coord[i].y() == test[i].y());
    QVERIFY(coord[i].z() == test[i].z());
  }
}

void parserTest::test_case5_getParsingIndexes() {
  QVector<GLuint> indexes = parser.getParsingIndexes();
  QVector<GLuint> test = {0, 4, 4, 6, 6, 2, 2, 0, 3, 2, 2, 6, 6, 7, 7, 3,
                          7, 6, 6, 4, 4, 5, 5, 7, 5, 1, 1, 3, 3, 7, 7, 5,
                          1, 0, 0, 2, 2, 3, 3, 1, 5, 4, 4, 0, 0, 1, 1, 5};
  for (int i = 0; i < indexes.size(); i++) {
    QVERIFY(indexes[i] == test[i]);
  }
}

void parserTest::initTestCase() {
  parser.parseFile(QDir::homePath() +
                   "/CPP4_3DViewer_v2.0-0/src/TestViewer/cube.obj");
}

QTEST_APPLESS_MAIN(parserTest)

#include "tst_parsertest.moc"
