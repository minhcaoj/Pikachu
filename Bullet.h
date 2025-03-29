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
    int get_x_val() const { return x_val; }
    int get_y_val() const { return y_val; }

    void set_is_move(const bool& isMove) { is_move = isMove; }
    bool get_is_move() const { return is_move; }

    void HandleMove(const int& border_x, const int& border_y);
    bool LoadImg(std::string path, SDL_Renderer* render);
private:
    int x_val;
    int y_val;
    bool is_move;

};

#endif