#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/scene.h"

namespace s21 {

class Controller {
 private:
  s21::Scene *scene_;

 public:
  Controller(){};

  void setPath(QString path);
  void setProectionType(int type);
  void setX(float move);
  void setY(float move);
  void setZ(float move);
  void rotationX(float spin);
  void rotationY(float spin);
  void rotationZ(float spin);
  void setScale(float sc);
  void setColorLine(QString color);
  void setBackgroundColor(QString color);
  double getVCount();
  double getFCount();
  int getProectionType();
  bool getNeedSaveSettings();
  QString getBackgroundColor();
  s21::SimpleObject3D getMObject();
  void setThicknessLine(int size);
  void setThicknessPoint(int size);
  void setPointFlag(int type);
  void setLineType(int type);
  void setPointColor(QString color);
  void setScene(s21::Scene *new_scene);
  void saveSettingsState(bool checkable);
  void saveImage(QString path);
  void saveGif();
};

}  // namespace s21

#endif  // CONTROLLER_H
