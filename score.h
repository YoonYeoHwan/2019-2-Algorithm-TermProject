class score {
public:
    void lifeDown();

    void pushUp();

    void stepUp();

    int getPush();

    int getStep();

    int getLife();

    score();

private:
    int lifeNum;
    int stepNum;
    int pushNum;
};