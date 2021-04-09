#include "Event.h"
#include "Sprites.h"
#include "Gimmick.h"
#include <string>

void Event::DrawNumber(int max, float x, float y, int _string)
{
    string str = to_string(_string);

    for (int i = 0; i < (max - str.size()); i++) {

        CSprites::GetInstance()->Get(SPRITE_ID_ZERO)->Draw(x, y);
        x += BLANK_BETWEEN_NUMBER;
    }

    for (int i = 0; i < str.size(); i++){

        CSprites::GetInstance()->Get(SPRITE_ID_ZERO + ConvertToInt(str[i]))->Draw(x, y);
        x += BLANK_BETWEEN_NUMBER;
    }
}

void Event::DrawItem(float x, float y, int type)
{
    CSprites* sprites = CSprites::GetInstance();

    if (type == 1) {
        sprites->Get(SPRITE_ID_MEDICINE)->Draw(x, y);
    }
    else if (type == 2) {
        sprites->Get(SPRITE_ID_BOMB_ITEM)->Draw(x, y);
    }
    else if (type == 3) {
        sprites->Get(SPRITE_ID_FIREBALL)->Draw(x, y);
    }
}

void Event::DrawEnergy(float x, float y, int m)
{
    for (int i = 0; i < m; i++) {

        if (i != MAX_HEALTH - 1) {
            CSprites::GetInstance()->Get(SPRITE_ENERGY_PINK_ON + i)->Draw(x, y);
            x += BLANK_BETWEEN_ENERGRY;
        }
        else if (i == MAX_HEALTH - 1) {
            CSprites::GetInstance()->Get(SPRITE_ENERGY_GREEN_ON)->Draw(x, y);
            return;
        }
    }

    for (int i = m; i < MAX_HEALTH ; i++) {

        if (i != MAX_HEALTH - 1) {
            CSprites::GetInstance()->Get(SPRITE_ENERGY_PINK_OFF + i)->Draw(x, y);
            x += BLANK_BETWEEN_ENERGRY;
        }
        else if (i == MAX_HEALTH - 1) {
            return;
        }
    }
}

int Event::ConvertToInt(char C)
{
    return C - '0';
}
