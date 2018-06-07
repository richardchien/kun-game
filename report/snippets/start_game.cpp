void start() {
    Screen screen(GetStdHandle(STD_OUTPUT_HANDLE));
    screen.set_size({25, 42});
    SetConsoleTitleA("鲲宠大乐斗");

    views::LoadingView view;
    view.display_on(screen);
}
