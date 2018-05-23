#include "./game.h"

#include "engine/engine.h"

using namespace std;

namespace kun {
    using namespace engine;

    class LoadingView : public View {
    public:
        using Attribute = Canvas::Attribute;
        using Alignings = Canvas::Alignings;

        void draw(Canvas &canvas) override {
            canvas.fill_background_with_color(Colors::CYAN)
                .print_text("≤‚ ‘¿≤¿≤¿≤",
                            Attribute()
                                .add_aligning(Alignings::VERTICAL_CENTER)
                                .add_aligning(Alignings::LEFT)
                                .set_margin_left(3));
        }
    };

    void start() {
        Screen screen(GetStdHandle(STD_OUTPUT_HANDLE));
        screen.set_size({31, 31});

        LoadingView view;
        view.display_on(screen);
    }
} // namespace kun
