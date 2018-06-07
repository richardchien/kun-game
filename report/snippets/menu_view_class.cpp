class MenuView : public View {
protected:
    void draw() override { View::draw(); }

    void loop() override {
        Menu menu(*canvas_, menus(), [this](Menu &menu, const int index) { on_select(menu, index); });
        menu.show(get_inner_boundary().expanded(-2));
    }

    virtual std::vector<std::string> menus() = 0;
    virtual void on_select(Menu &menu, int index) = 0;
};
