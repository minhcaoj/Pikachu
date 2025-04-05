#ifndef BULLET_H
#define BULLET_H

#include "CommonFunc.h"
#include "BaseObject.h"




class Bullet : public BaseObject {
public:


   
    Bullet();
    ~Bullet();

    void set_x_val(const int& xVal) { x_val = xVal; }
    void set_y_val(const int& yVal) { y_val = yVal; }
    void set_damage_val( const float& bDamage) { damage = bDamage; }
    int get_x_val() const { return x_val; }
    int get_y_val() const { return y_val; }
    float get_damage_val() const { return damage; }

    void set_is_move(const bool& isMove) { is_move = isMove; }
    bool get_is_move() const { return is_move; }

    void HandleMove();
    bool LoadImg(std::string path, SDL_Renderer* render, float scaleFactor);
private:
    int x_val;
    int y_val;
    bool is_move;
    float damage;

};

#endif