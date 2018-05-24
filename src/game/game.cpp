#include "./game.h"

#include "engine/engine.h"

#include "./views/loading_view.h"

using namespace std;

namespace kun {
    using namespace engine;

    void start() {
        Screen screen(GetStdHandle(STD_OUTPUT_HANDLE));
        screen.set_size({23, 35});

        views::LoadingView view;
        view.display_on(screen);
    }
} // namespace kun
