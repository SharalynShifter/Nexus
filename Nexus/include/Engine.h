class Engine {
public:
    enum GameStatus {
        STARTUP,
        IDLE,
        NEW_TURN,
        VICTORY,
        DEFEAT
    } gameStatus;
    TCOD_key_t lastKey;
    TCOD_mouse_t mouse;
    TCODList<Actor*> actors;
    Actor* player;
    Actor* stairs;
    Map* map;
    int fovRadius;
    int screenWidth;
    int screenHeight;
    Gui* gui;
    int level;
    void nextLevel();

    Engine(int screenWidth, int screenHeight);
    ~Engine();
    void update();
    void render();
    void sendToBack(Actor* actor);
    Actor* getActor(int x, int y) const;
    Actor* getClosestMonster(int x, int y, float range) const;
    bool pickATile(int* x, int* y, float maxRange = 0.0f);
    void init();
    void term();
    void load(bool pause = false);
    void save();
};

extern Engine engine;
