#include "controller.h"

namespace s21 {

void Controller::setScene(s21::Scene *new_scene) { scene_ = new_scene; }

void Controller::setPath(QString path) {
  scene_->setPath(path);  // путь к файлу
}

void Controller::setProectionType(int type) {
  scene_->setProectionType(
      type);  // тип проекции. 0 - perspective (default), 1 - ortho
}

void Controller::setX(float move) { scene_->setX(move); }

void Controller::setY(float move) { scene_->setY(move); }

void Controller::setZ(float move) { scene_->setZ(move); }

void Controller::rotationX(float spin) {
  scene_->rotationX(spin);  // повороты модели в градусах
}

void Controller::rotationY(float spin) { scene_->rotationY(spin); }

void Controller::rotationZ(float spin) { scene_->rotationZ(spin); }

void Controller::setScale(float sc) {
  scene_->setScale(sc);  // масштабирование модели
}

void Controller::setColorLine(QString color) {
  scene_->setColorLine(color);  // цвет линий
}

void Controller::setBackgroundColor(QString color) {
  scene_->setBackgroundColor(color);  // цвет фона
}

double Controller::getVCount() {
  return scene_->getVCount();  // количество вершин
}

double Controller::getFCount() {
  return scene_->getFCount();  // количество полигонов
}

s21::SimpleObject3D Controller::getMObject() { return scene_->getObject3D(); }

int Controller::getProectionType() { return scene_->getProectionType(); }

bool Controller::getNeedSaveSettings() { return scene_->getNeedSaveSettings(); }

QString Controller::getBackgroundColor() {
  return scene_->getBackgroundColor();
}

void Controller::setThicknessLine(int size) {
  scene_->setThicknessLine(size);  // толщина линий
}

void Controller::setThicknessPoint(int size) {
  scene_->setThicknessPoint(size);  // толщина точек
}

void Controller::setPointFlag(int type) {
  scene_->setPointFlag(
      type);  // точки. 0 - отсутствует (default), 1 - круг, 2 - квадрат
}

void Controller::setLineType(int type) {
  scene_->setLineType(type);  // тип линии. 0 - сплошная (default), 1 -
                              // пунктирная, 2 - пунктир на шейдере (тест)
}

void Controller::setPointColor(QString color) {
  scene_->setPointColor(color);  // цвет точек
}

void Controller::saveSettingsState(bool checkeble) {
  scene_->setNeedSaveSettings(checkeble);
  scene_->update();
}

void Controller::saveImage(QString path) { scene_->saveImage(path); }

void Controller::saveGif() { scene_->makeGif(); }

}  // namespace s21
