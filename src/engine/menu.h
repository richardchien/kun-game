#pragma once

#include <functional>
#include <string>
#include <vector>

#include "./canvas.h"
#include "./types.h"
#include "./view.h"

namespace kun::engine {
    // ������˵��࣬�����ڸ�����ͼ�в���˵�����Ӧ�û���ѡ��
    class Menu {
    public:
        Color item_color = Colors::combine(Colors::WHITE, Colors::BLACK);
        Color item_active_color = Colors::combine(Colors::BLACK | Colors::INTENSITY, Colors::WHITE);

        Menu(Canvas &canvas, const std::vector<std::string> &menu_vec,
             const std::function<void(Menu &, int)> &on_select = nullptr)
            : canvas_(canvas), menu_vec_(menu_vec), on_select_(on_select) {}

        // �ڸ��� Canvas ��ָ����Χ�ھ�����ʾ�˵����ȴ��û�ѡ��
        void show(const Rect &boundary_rect = Rect(-1, -1, -1, -1),
                  const Canvas::Aligning aligning = Canvas::Alignings::VERTICAL_CENTER) {
            if (boundary_rect == Rect(-1, -1, -1, -1)) {
                boundary_rect_ = canvas_.get_screen().get_boundary();
            } else {
                boundary_rect_ = boundary_rect;
            }
            menu_rect_ = calc_menu_rect(boundary_rect_, aligning);

            auto should_reprint_menu = true;
            while (!should_break_loop_) {
                if (should_reprint_menu) {
                    print_menu_items();
                    update_active_menu_item(current_index_);
                    should_reprint_menu = false;
                }

                // �ȴ��û�����
                const auto key = View::wait_for_keypress();
                switch (key) {
                case 'W':
                case 'w':
                case 72 /* �� */:
                    update_active_menu_item(current_index_ > 0 ? current_index_ - 1 : menu_vec_.size() - 1);
                    break;
                case 'S':
                case 's':
                case 80 /* �� */:
                    update_active_menu_item((current_index_ + 1) % menu_vec_.size());
                    break;
                case ' ' /* �ո�� */:
                case '\r' /* �س��� */:
                    if (on_select_) {
                        on_select_(*this, current_index_);
                        should_reprint_menu = true; // �Ѿ�������ѡ������п��ܴ��µ�ҳ�淵�أ���Ҫ���»��Ʋ˵�
                    }
                    break;
                default:
                    break;
                }
            }
        }

        void break_loop() { should_break_loop_ = true; }

    private:
        Canvas &canvas_;
        std::vector<std::string> menu_vec_; // �˵����ַ���
        std::function<void(Menu &menu, int index)> on_select_; // ѡ���¼��Ļص�����

        Rect boundary_rect_; // �˵��ı߽緶Χ
        Rect menu_rect_; // �˵���ʵ��ռ�÷�Χ
        int current_index_ = 0; // ��ǰ��������

        bool should_break_loop_ = false;

        // �����ڸ�������������˵�ʵ��ռ�õľ��η�Χ
        Rect calc_menu_rect(const Rect &boundary_rect, const Canvas::Aligning aligning) const {
            Int width = 0;
            for (const auto &m : menu_vec_) {
                const Int w = (m.size() % 2 == 0 ? m.size() : m.size() + 1) / 2;
                if (w / 2 > width) width = w;
            }
            const Int height = menu_vec_.size() * 2 - 1;

            if (aligning == Canvas::Alignings::TOP) {
                return Rect(boundary_rect.top_left(), Size(boundary_rect.width(), height)).resized({width, height});
            }
            if (aligning == Canvas::Alignings::BOTTOM) {
                return Rect(Point(boundary_rect.left(), boundary_rect.bottom_out() - height),
                            Size(boundary_rect.width(), height))
                    .resized({width, height});
            }
            return boundary_rect.resized({width, height});
        }

        // ����˵�
        void print_menu_items() {
            const auto old_color = canvas_.get_color();
            canvas_.set_color(item_color);
            for (size_t i = 0; i < menu_vec_.size(); i++) {
                canvas_.draw_text(menu_vec_[i],
                                  Canvas::Attribute()
                                      .set_margin_top(menu_rect_.top() + i * 2)
                                      .set_margin_left(menu_rect_.left())
                                      .set_margin_right(canvas_.get_rect().right() - menu_rect_.right())
                                      .set_margin_bottom(canvas_.get_rect().bottom() - menu_rect_.bottom())
                                      .add_aligning(Canvas::Alignings::TOP)
                                      .add_aligning(Canvas::Alignings::HORIZONTAL_CENTER));
            }
            canvas_.set_color(old_color);
        }

        // ���µ�ǰ�����Ĳ˵���
        void update_active_menu_item(const int index) {
            current_index_ = index;

            canvas_.fill_color(item_color, boundary_rect_);
            const Rect item_boundary(boundary_rect_.left(),
                                     menu_rect_.top() + index * 2,
                                     boundary_rect_.right(),
                                     menu_rect_.top() + index * 2);
            canvas_.fill_color(item_active_color, item_boundary);
        }
    };
} // namespace kun::engine