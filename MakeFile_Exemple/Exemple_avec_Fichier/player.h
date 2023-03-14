#if !defined(_PLAYER_H_)

    #define _PLAYER_H_
    typedef struct Player{
        char name[20];
        int level;
    }Player;
    //typedef struct Player Player;

    Player create(void);
    void say (Player p , char *message);
#endif