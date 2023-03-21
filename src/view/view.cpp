#include "view.h"

#include <QColorDialog>
#include <QFileDialog>

#include "ui_view.h"

namespace s21 {

View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  controller_.setScene(ui->widget);
  s21::SimpleObject3D data = controller_.getMObject();
  ui->actionSave->setChecked(controller_.getNeedSaveSettings());
  if (controller_.getProectionType())
    ui->radioButton_parallel->setChecked(true);
  ui->comboBox_edge_type->setCurrentIndex(data.getLineType());
  ui->doubleSpinBox_edge_size->setValue(data.getThicknessLine());
  ui->pushButton_edge_color->setText(data.getLineColor());
  ui->comboBox_vertecies_shape->setCurrentIndex(data.getPointFlag());
  ui->doubleSpinBox_vertex_size->setValue(data.getThicknessPoint());
  ui->pushButton_vertex_color->setText(data.getPointColor());
  ui->pushButton_bg_color->setText(controller_.getBackgroundColor());
}

View::~View() { delete ui; }

void View::transformDefault() {
  ui->doubleSpinBox_l_x->setValue(0.0);
  ui->doubleSpinBox_l_y->setValue(0.0);
  ui->doubleSpinBox_l_z->setValue(0.0);
  ui->doubleSpinBox_r_x->setValue(0.0);
  ui->doubleSpinBox_r_y->setValue(0.0);
  ui->doubleSpinBox_r_z->setValue(0.0);
  ui->doubleSpinBox_s_z->setValue(1.0);
}

void View::on_actionOpen_obj_triggered() {
  QString path = nullptr;
  path = QFileDialog::getOpenFileName(this, "Выбрать файл", "/", "*.obj");
  if (!path.isNull()) {
    controller_.setPath(path);
    QFileInfo file_name(path);
    ui->label_file_name->setText(file_name.fileName());
    ui->label_vertecies->setText(QString::number(controller_.getVCount()) +
                                 " vertecies");
    ui->label_faces->setText(QString::number(controller_.getFCount()) +
                             " faces");
    transformDefault();
  }
}

void View::on_pushButton_bg_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this);
  ui->pushButton_bg_color->setText(color.name());
  controller_.setBackgroundColor(color.name());
}

void View::on_pushButton_edge_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this);
  ui->pushButton_edge_color->setText(color.name());
  controller_.setColorLine(color.name());
}

void View::on_pushButton_vertex_color_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this);
  ui->pushButton_vertex_color->setText(color.name());
  controller_.setPointColor(color.name());
}

void View::on_doubleSpinBox_l_x_valueChanged(double arg_new) {
  controller_.setX(arg_new);
}

void View::on_doubleSpinBox_l_y_valueChanged(double arg_new) {
  controller_.setY(arg_new);
}

void View::on_doubleSpinBox_l_z_valueChanged(double arg_new) {
  controller_.setZ(arg_new);
}

void View::on_doubleSpinBox_r_x_valueChanged(double arg_new) {
  controller_.rotationX(arg_new);
}

void View::on_doubleSpinBox_r_y_valueChanged(double arg_new) {
  controller_.rotationY(arg_new);
}

void View::on_doubleSpinBox_r_z_valueChanged(double arg_new) {
  controller_.rotationZ(arg_new);
}

void View::on_doubleSpinBox_s_z_valueChanged(double arg_new) {
  controller_.setScale(arg_new);
}

void View::on_comboBox_edge_type_currentIndexChanged(int new_index) {
  controller_.setLineType(new_index);
}

void View::on_doubleSpinBox_edge_size_valueChanged(double arg_new) {
  controller_.setThicknessLine(arg_new);
}

void View::on_comboBox_vertecies_shape_currentIndexChanged(int new_index) {
  if (!new_index) {
    ui->doubleSpinBox_vertex_size->setValue(0.00);
    ui->doubleSpinBox_vertex_size->setReadOnly(true);
  } else {
    ui->doubleSpinBox_vertex_size->setReadOnly(false);
  }
  controller_.setPointFlag(new_index);
}

void View::on_doubleSpinBox_vertex_size_valueChanged(double arg_new) {
  controller_.setThicknessPoint(arg_new);
}

void View::on_actionSave_triggered() {
  controller_.saveSettingsState(ui->actionSave->isChecked() ? true : false);
}

void View::on_radioButton_central_clicked() { controller_.setProectionType(0); }

void View::on_radioButton_parallel_clicked() {
  controller_.setProectionType(1);
}

void View::on_actionBPM_bmp_triggered() {
  QString path = QFileDialog::getSaveFileName(
      this, tr("Save as..."), "untitled.bmp", tr("Images (*.bmp)"));
  if (path.isEmpty() || path.isNull()) return;
  controller_.saveImage(path);
}

void View::on_actionJPEG_jpeg_triggered() {
  QString path = QFileDialog::getSaveFileName(
      this, tr("Save as..."), "untitled.jpeg", tr("Images (*.jpeg)"));
  if (path.isEmpty() || path.isNull()) return;
  controller_.saveImage(path);
}

void View::on_actionSave_gif_triggered() { controller_.saveGif(); }

}  // namespace s21
