#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private:
  Controller controller_;
  void transformDefault();

 private slots:
  void on_actionOpen_obj_triggered();

  void on_pushButton_bg_color_clicked();
  void on_pushButton_edge_color_clicked();
  void on_pushButton_vertex_color_clicked();

  void on_doubleSpinBox_l_x_valueChanged(double arg_new);
  void on_doubleSpinBox_l_y_valueChanged(double arg_new);
  void on_doubleSpinBox_l_z_valueChanged(double arg_new);

  void on_doubleSpinBox_r_x_valueChanged(double arg_new);
  void on_doubleSpinBox_r_y_valueChanged(double arg_new);
  void on_doubleSpinBox_r_z_valueChanged(double arg_new);

  void on_doubleSpinBox_s_z_valueChanged(double arg_new);

  void on_comboBox_edge_type_currentIndexChanged(int new_index);
  void on_doubleSpinBox_edge_size_valueChanged(double arg_new);
  void on_comboBox_vertecies_shape_currentIndexChanged(int new_index);
  void on_doubleSpinBox_vertex_size_valueChanged(double arg_new);

  void on_radioButton_central_clicked();
  void on_radioButton_parallel_clicked();

  void on_actionSave_triggered();
  void on_actionBPM_bmp_triggered();
  void on_actionJPEG_jpeg_triggered();
  void on_actionSave_gif_triggered();

 private:
  Ui::View *ui;
};

}  // namespace s21

#endif  // VIEW_H
