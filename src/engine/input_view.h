#pragma once

#include <iostream>
#include <string>

#include "./view.h"

namespace kun::engine {
    class InputView : public View {
    protected:
        void draw() override {
            View::draw();
            const auto boundary = get_inner_boundary().expanded(-2);
            canvas_->draw_text(prompt(), boundary);
            const Rect input_rect(boundary.left(), boundary.bottom_out() - 3, boundary.right(), boundary.bottom());
            canvas_->fill_and_set_background_color(Colors::BLACK | Colors::INTENSITY, input_rect);
            canvas_->get_screen().set_cursor_position({input_rect.left() + 1, input_rect.center().y});
            canvas_->set_foreground_color(Colors::WHITE);
        }

        void loop() override {
            std::string input;
            std::getline(std::cin, input);
            on_input(input);
        }

        virtual std::string prompt() = 0;
        virtual void on_input(const std::string &input) {}
    };
} // namespace kun::engine
